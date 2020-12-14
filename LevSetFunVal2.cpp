#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>
#include <omp.h>
using namespace std;
void LevSetFunVal2(vector< vector<double> >& gcoord, double PlaneProperty[4], vector<double>& phi, double Cycle, double Magnitude, int ni, double CrossSectExp, double p, double q)
{
	omp_set_num_threads(8);
	double b = 0.5 * Cycle;
	double pi = 3.1415927;
	double* CenterLineY = new double[gcoord.size()]();
	//vector<double> CenterLineY(gcoord.size(), 0);
#pragma omp parallel for
	for (int i = 0; i < gcoord.size(); i++)
	{
		CenterLineY[i] = gcoord[i][1];
	}
	double CenterLineX = PlaneProperty[0];
	double* CenterLineZ = new double[gcoord.size()]();
	//vector<double> CenterLineZ(gcoord.size(), 0);
	if (ni == 0)
	{
#pragma omp parallel for
		for (int j = 0; j < gcoord.size(); j++)
		{
			CenterLineZ[j] = PlaneProperty[2] + Magnitude * sin((CenterLineY[j] + b * 0.5) * pi / b) + Magnitude;
		}
	}
	else if (ni == 1)
	{
#pragma omp parallel for
		for (int j = 0; j < gcoord.size(); j++)
		{
			CenterLineZ[j] = PlaneProperty[2] + Magnitude * sin((CenterLineY[j] + b * 1.5) * pi / b) - Magnitude;
		}
	}
	else if (ni == 2)
	{
#pragma omp parallel for
		for (int j = 0; j < gcoord.size(); j++)
		{
			CenterLineZ[j] = PlaneProperty[2] + Magnitude * sin((CenterLineY[j] + b * 0.5) * pi / b) + Magnitude;
		}
	}
	double Radius = PlaneProperty[3];
	//double* phi = new double[Nx * Ny * Nz]();
#pragma omp parallel for
	for (int i = 0; i < gcoord.size(); i++)
	{
		//phi[i] = (gcoord[i][2] - CenterLineZ[i]) * (gcoord[i][2] - CenterLineZ[i]) + (gcoord[i][0] - CenterLineX) * (gcoord[i][0] - CenterLineX) - Radius * Radius;
		phi[i] = pow(abs((gcoord[i][2] - CenterLineZ[i]) / p), CrossSectExp) + pow(abs((gcoord[i][0] - CenterLineX) / q), CrossSectExp) - Radius * Radius;
	}
	double Smax = gcoord[0][0];
	double Smin = gcoord[0][0];
	for (int i = 0; i < gcoord.size(); i++)
	{
		if (Smax < gcoord[i][0])
		{
			Smax = gcoord[i][0];
		}
		if (Smin > gcoord[i][0])
		{
			Smin = gcoord[i][0];
		}
	}
	double Scale = fabs(Smax - Smin);
	for (int i = 0; i < gcoord.size(); i++)
	{
		if (fabs(phi[i]) <= (Scale * 0.01))
		{
			phi[i] = 0;
		}
	}
	delete[]CenterLineY;     //ɾ��CenterLineX����
	delete[]CenterLineZ;     //ɾ��CenterLineZ����
}
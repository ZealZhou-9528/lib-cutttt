#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>
#include <omp.h>
using namespace std;
void LevSetFunVal(vector< vector<double> >&gcoord,double PlaneProperty[4], vector<double>&phi,double Cycle,double Magnitude,int ni, double CrossSectExp, double p, double q)
{
	omp_set_num_threads(8);
	double b = 0.5 * Cycle;
	double pi = 3.141592653589793115997963468544185161590576171875;
	double* CenterLineX = new double[gcoord.size()]();
	//vector<double> CenterLineX(gcoord.size(),0);
#pragma omp parallel for
	for (int i = 0; i < gcoord.size(); i++)
	{
		CenterLineX[i] = gcoord[i][0];
	}
	double CenterLineY = PlaneProperty[1];
	double* CenterLineZ = new double[gcoord.size()]();
	//vector<double> CenterLineZ(gcoord.size(), 0);
	if (ni == 0)
	{
#pragma omp parallel for
		for (int j = 0; j < gcoord.size(); j++)
		{
			CenterLineZ[j] = PlaneProperty[2] + Magnitude * sin((CenterLineX[j] + b * 1.5) * pi / b) - Magnitude;
		}
	}
	else if (ni == 1)
	{
#pragma omp parallel for
		for (int j = 0; j < gcoord.size(); j++)
		{
			CenterLineZ[j] = PlaneProperty[2] + Magnitude * sin((CenterLineX[j] + b * 0.5) * pi / b) + Magnitude;
		}
	}
	else if (ni == 2)
	{
#pragma omp parallel for
		for (int j = 0; j < gcoord.size(); j++)
		{
			CenterLineZ[j] = PlaneProperty[2] + Magnitude * sin((CenterLineX[j] + b * 1.5) * pi / b) - Magnitude;
		}
	}
	double Radius = PlaneProperty[3];
	//double* phi = new double[Nx * Ny * Nz]();
#pragma omp parallel for
	for (int i = 0; i < gcoord.size(); i++)
	{
		phi[i] = pow(abs((gcoord[i][2] - CenterLineZ[i])/p), CrossSectExp)+ pow(abs((gcoord[i][1] - CenterLineY)/q), CrossSectExp) - Radius * Radius;
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
	delete[]CenterLineX;     //删除CenterLineX数组
	delete[]CenterLineZ;     //删除CenterLineZ数组
}
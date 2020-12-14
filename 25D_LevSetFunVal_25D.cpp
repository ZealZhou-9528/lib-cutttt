#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>
using namespace std;
void LevSetFunVal_25D(vector< vector<double> >& gcoord, double PlaneProperty[4], vector<double>& phi, double Cycle, double Magnitude, int ni, double CrossSectExp, double p, double q)
{
	p = 0.225;
	q = 0.45;
	double b = 0.5 * Cycle;
	double pi = 3.141592653589793115997963468544185161590576171875;
	//double* CenterLineX = new double[gcoord.size()]();
	vector<double> CenterLineX(gcoord.size(), 0);
	for (int i = 0; i < gcoord.size(); i++)
	{
		CenterLineX[i] = gcoord[i][0];
	}
	double CenterLineY = PlaneProperty[1];
	//double* CenterLineZ = new double[gcoord.size()]();
	vector<double> CenterLineZ(gcoord.size(), 0);
	ni = ni + 1;
	int nimod = ni % 2;
	if (nimod == 0)
	{
		for (int j = 0; j < gcoord.size(); j++)
		{
			CenterLineZ[j] = PlaneProperty[2] + Magnitude * sin((CenterLineX[j] + b * 0.5) * pi / b) + Magnitude;
		}
	}
	else 
	{
		for (int j = 0; j < gcoord.size(); j++)
		{
			CenterLineZ[j] = PlaneProperty[2] + Magnitude * sin((CenterLineX[j] + b * 1.5) * pi / b) - Magnitude;
		}
	}
	
	double Radius = PlaneProperty[3];
	//double* phi = new double[Nx * Ny * Nz]();
	for (int i = 0; i < gcoord.size(); i++)
	{
		phi[i] = pow(abs((gcoord[i][2] - CenterLineZ[i]) / p), CrossSectExp) + pow(abs((gcoord[i][1] - CenterLineY) / q), CrossSectExp) - 1;// Radius* Radius;
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
		if (fabs(phi[i]) <= (Scale * 0.001))
		{
			phi[i] = 0;
		}
	}

}
#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>
using namespace std;
void LevSetFunVal_3D(vector< vector<double> >& gcoord, double PlaneProperty[4], vector<double>& phi, double Cycle, double Magnitude, int ni, double CrossSectExp, double p, double q)
{
	ni = ni + 1;
	double b = 0.5 * Cycle;
	double pi = 3.141592653589793115997963468544185161590576171875;
	double c = sqrt(7);
	vector<double> CenterLineZ(gcoord.size(), 0);
	for (int i = 0; i < gcoord.size(); i++)
	{
		CenterLineZ[i] = gcoord[i][2];
	}
	vector<double> CenterLineX(gcoord.size(), 0);
	vector<double> CenterLineY(gcoord.size(), 0);
	int nimod = ni%8;
	switch (nimod)
	{
	 case(1):
		 for (int i = 0; i < gcoord.size(); i++)
		 {
			 CenterLineX[i] = PlaneProperty[0] + c * cos((CenterLineZ[i] + b * 0.5) * pi / b);
			 CenterLineY[i] = PlaneProperty[1] + 0.5 * c * sin((CenterLineZ[i] + b * 0.5) * pi / b);
		 }
		break;
	 case(2):
		 for (int i = 0; i < gcoord.size(); i++)
		 {
			 CenterLineX[i] = PlaneProperty[0] + c * cos((CenterLineZ[i] + b * 0.5) * pi / b + pi / 2);
			 CenterLineY[i] = PlaneProperty[1] + 0.5 * c * sin((CenterLineZ[i] + b * 0.5) * pi / b + pi / 2);
		 }
		 break;
	 case(3):
		 for (int i = 0; i < gcoord.size(); i++)
		 {
			 CenterLineX[i] = PlaneProperty[0] + c * cos((CenterLineZ[i] + b * 0.5) * pi / b + pi);
			 CenterLineY[i] = PlaneProperty[1] + 0.5 * c * sin((CenterLineZ[i] + b * 0.5) * pi / b + pi);
		 }
		 break;
	 case(4):
		 for (int i = 0; i < gcoord.size(); i++)
		 {
			 CenterLineX[i] = PlaneProperty[0] + c * cos((CenterLineZ[i] + b * 0.5) * pi / b + 3 * pi / 2);
			 CenterLineY[i] = PlaneProperty[1] + 0.5 * c * sin((CenterLineZ[i] + b * 0.5) * pi / b + 3*pi/2);
		 }
		 break;
	 case(5):
		 for (int i = 0; i < gcoord.size(); i++)
		 {
			 CenterLineX[i] = PlaneProperty[0] + 0.5 * c * cos((CenterLineZ[i] + b * 0.5) * pi / b);
			 CenterLineY[i] = PlaneProperty[1] + c * sin((CenterLineZ[i] + b * 0.5) * pi / b);
		 }
		 break;
	 case(6):
		 for (int i = 0; i < gcoord.size(); i++)
		 {
			 CenterLineX[i] = PlaneProperty[0] + 0.5 * c * cos((CenterLineZ[i] + b * 0.5) * pi / b + pi / 2);
			 CenterLineY[i] = PlaneProperty[1] + c * sin((CenterLineZ[i] + b * 0.5) * pi / b + pi / 2);
		 }
		 break;
	 case(7):
		 for (int i = 0; i < gcoord.size(); i++)
		 {
			 CenterLineX[i] = PlaneProperty[0] + 0.5 * c * cos((CenterLineZ[i] + b * 0.5) * pi / b + pi);
			 CenterLineY[i] = PlaneProperty[1] + c * sin((CenterLineZ[i] + b * 0.5) * pi / b + pi);
		 }
		 break;
	 case(0):
		 for (int i = 0; i < gcoord.size(); i++)
		 {
			 CenterLineX[i] = PlaneProperty[0] + 0.5 * c * cos((CenterLineZ[i] + b * 0.5) * pi / b + 3 * pi / 2);
			 CenterLineY[i] = PlaneProperty[1] + c * sin((CenterLineZ[i] + b * 0.5) * pi / b + 3 * pi / 2);
		 }
		 break;
	}
	double Radius = PlaneProperty[3];
	for (int i = 0; i < gcoord.size(); i++)
	{
		phi[i] = pow(abs((gcoord[i][0] - CenterLineX[i]) / p), CrossSectExp) + pow(abs((gcoord[i][1] - CenterLineY[i]) / q), CrossSectExp) - Radius * Radius;
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
		if (fabs(phi[i]) <= (Scale * 0.00001))
		{
			phi[i] = 0;
		}
	}
	//delete[]CenterLineX;     //删除CenterLineX数组
	//delete[]CenterLineZ;     //删除CenterLineZ数组
}
#include <iostream>
#include <vector>
using namespace std;
void PlaneFunction2_25D(double& f1, double x, double y, double z, double CircleProperty[4], double Cycle, double Magnitude, int ni);
void gAdd2_25D(vector<double>& coordnew, vector< vector<double> >& gcoord, int LineNode[2], double CircleProperty[4], double Cycle, double Magnitude, int ni)
{
	double x1 = 0, x2 = 0, x3 = 0, y1 = 0, y2 = 0, y3 = 0, z1 = 0, z2 = 0, z3 = 0;
	x1 = gcoord[(LineNode[0])][0];
	x2 = gcoord[(LineNode[1])][0];
	y1 = gcoord[(LineNode[0])][1];
	y2 = gcoord[(LineNode[1])][1];
	z1 = gcoord[(LineNode[0])][2];
	z2 = gcoord[(LineNode[1])][2];
	double f1 = 0, f3 = 0;
	double newx = 0, newy = 0, newz = 0;
	PlaneFunction2_25D(f1, x1, y1, z1, CircleProperty, Cycle, Magnitude, ni);//f1=PlaneFunction(x1,y1,z1,PlanePropery,Cycle,Magnitude,n);  
	double CovgCrit = 0.0000001 * sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1));
	double Distance = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2));
	while (Distance > CovgCrit)
	{
		x3 = (x2 + x1) / 2; y3 = (y2 + y1) / 2; z3 = (z2 + z1) / 2;
		PlaneFunction2_25D(f3, x3, y3, z3, CircleProperty, Cycle, Magnitude, ni);//f3=PlaneFunction(x3,y3,z3,PlanePropery,Cycle,Magnitude,n);
		if (f3 * f1 > 0)
		{
			x1 = x3; y1 = y3; z1 = z3;
		}
		else
		{
			x2 = x3; y2 = y3; z2 = z3;
		}
		PlaneFunction2_25D(f1, x1, y1, z1, CircleProperty, Cycle, Magnitude, ni);// f1=PlaneFunction(x1,y1,z1,PlanePropery,Cycle,Magnitude,n);  
		Distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1));
	}
	newx = (x1 + x2) / 2;
	newy = (y1 + y2) / 2;
	newz = (z1 + z2) / 2;
	coordnew[0] = newx;
	coordnew[1] = newy;
	coordnew[2] = newz;
}
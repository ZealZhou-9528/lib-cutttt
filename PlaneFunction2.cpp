#include <iostream>
using namespace std;
void PlaneFunction2(double& f1, double x, double y, double z, double CircleProperty[4], double Cycle, double Magnitude, int ni)
{
	double b = Cycle * 0.5;
	double pi = 3.1415927;
	double CenterLineX = CircleProperty[0];
	double CenterLineY = y;
	double CenterLineZ = 0;
	if (ni == 0)
	{
		CenterLineZ = CircleProperty[2] + Magnitude * sin((CenterLineY + b * 0.5) * pi / b) + Magnitude;
	}
	else if (ni == 1)
	{
		CenterLineZ = CircleProperty[2] + Magnitude * sin((CenterLineY + b * 1.5) * pi / b) - Magnitude;
	}
	else if (ni == 2)
	{
		CenterLineZ = CircleProperty[2] + Magnitude * sin((CenterLineY + b * 0.5) * pi / b) + Magnitude;
	}
	double Radius = CircleProperty[3];
	f1 = (z - CenterLineZ) * (z - CenterLineZ) + (x - CenterLineX) * (x - CenterLineX) - Radius * Radius;
}
#include <iostream>
using namespace std;
void PlaneFunction(double &f1, double x, double y, double z, double CircleProperty[4], double Cycle, double Magnitude, int ni)
{
	double b = Cycle * 0.5;
	double pi = 3.14159265358979323846;
	double CenterLineX = x;
	double CenterLineY = CircleProperty[1];
	double CenterLineZ = 0;
	if (ni == 0)
	{
			CenterLineZ = CircleProperty[2] + Magnitude * sin((CenterLineX + b * 1.5) * pi / b) - Magnitude;
	}
	else if (ni == 1)
	{
			CenterLineZ = CircleProperty[2] + Magnitude * sin((CenterLineX + b * 0.5) * pi / b) + Magnitude;
	}
	else if (ni == 2)
	{
			CenterLineZ = CircleProperty[2] + Magnitude * sin((CenterLineX + b * 1.5) * pi / b) - Magnitude;
	}
	double Radius = CircleProperty[3];
	f1 = (z- CenterLineZ) * (z - CenterLineZ) + (y - CenterLineY) * (y - CenterLineY) - Radius * Radius;
}
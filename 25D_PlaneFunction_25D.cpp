#include <iostream>
using namespace std;
void PlaneFunction_25D(double& f1, double x, double y, double z, double CircleProperty[4], double Cycle, double Magnitude, int ni)
{
	double b = Cycle * 0.5;
	//double c = sqrt(7);
	double pi = 3.14159265358979323846;
	double CenterLineX = x;
	double CenterLineY = CircleProperty[1];
	double CenterLineZ;
	ni = ni + 1;
	int nimod = ni % 2;
	if (nimod == 0)
	{
		CenterLineZ = CircleProperty[2] + Magnitude * sin((CenterLineX + b * 0.5) * pi / b) + Magnitude;
	}
	else
	{
		CenterLineZ = CircleProperty[2] + Magnitude * sin((CenterLineX + b * 1.5) * pi / b) - Magnitude;
	}
	double Radius = CircleProperty[3];
	f1 = pow(abs((z - CenterLineZ) / 0.225), 2) + pow(abs((y - CenterLineY) / 0.45), 2) - 1;// Radius* Radius;
}
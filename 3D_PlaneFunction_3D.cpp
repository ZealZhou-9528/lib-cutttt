#include <iostream>
using namespace std;
void PlaneFunction_3D(double& f1, double x, double y, double z, double CircleProperty[4], double Cycle, double Magnitude, int ni)
{
	double b = Cycle * 0.5;
	double c = sqrt(7);
	double pi = 3.14159265358979323846;
	double CenterLineX;
	double CenterLineY;
	double CenterLineZ = z;
	ni = ni + 1;
	int nimod = ni % 8;
	switch (nimod)
	{
	case(1):
		CenterLineX = CircleProperty[0] + c * cos((CenterLineZ + b * 0.5) * pi / b);
		CenterLineY = CircleProperty[1] + 0.5 * c * sin((CenterLineZ + b * 0.5) * pi / b);
		break;
	case(2):
		CenterLineX = CircleProperty[0] + c * cos((CenterLineZ + b * 0.5) * pi / b + pi / 2);
		CenterLineY = CircleProperty[1] + 0.5 * c * sin((CenterLineZ + b * 0.5) * pi / b + pi / 2);
		break;
	case(3):
		CenterLineX = CircleProperty[0] + c * cos((CenterLineZ + b * 0.5) * pi / b + pi);
		CenterLineY = CircleProperty[1] + 0.5 * c * sin((CenterLineZ + b * 0.5) * pi / b + pi);
		break;
	case(4):
		CenterLineX = CircleProperty[0] + c * cos((CenterLineZ + b * 0.5) * pi / b + 3 * pi / 2);
		CenterLineY = CircleProperty[1] + 0.5 * c * sin((CenterLineZ + b * 0.5) * pi / b + 3 * pi / 2);
		break;
	case(5):
		CenterLineX = CircleProperty[0] + 0.5 * c * cos((CenterLineZ + b * 0.5) * pi / b);
		CenterLineY = CircleProperty[1] + c * sin((CenterLineZ + b * 0.5) * pi / b);
		break;
	case(6):
		CenterLineX = CircleProperty[0] + 0.5 * c * cos((CenterLineZ + b * 0.5) * pi / b + pi / 2);
		CenterLineY = CircleProperty[1] + c * sin((CenterLineZ + b * 0.5) * pi / b + pi / 2);
		break;
	case(7):
		CenterLineX = CircleProperty[0] + 0.5 * c * cos((CenterLineZ + b * 0.5) * pi / b + pi);
		CenterLineY = CircleProperty[1] + c * sin((CenterLineZ + b * 0.5) * pi / b + pi);
		break;
	case(0):
		CenterLineX = CircleProperty[0] + 0.5 * c * cos((CenterLineZ + b * 0.5) * pi / b + 3 * pi / 2);
		CenterLineY = CircleProperty[1] + c * sin((CenterLineZ + b * 0.5) * pi / b + 3 * pi / 2);
		break;
	}
	double Radius = CircleProperty[3];
	f1 = (x - CenterLineX) * (x - CenterLineX) + (y - CenterLineY) * (y - CenterLineY) - Radius * Radius;
}
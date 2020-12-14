#include <iostream>
using namespace std;
void PlaneFunction2_25D(double& f1, double x, double y, double z, double CircleProperty[4], double Cycle, double Magnitude, int ni)
{
	double b = Cycle * 0.5;
	double pi = 3.14159265358979323846;
	double CenterLineX = CircleProperty[0];
	double CenterLineY = CircleProperty[1];
	double CenterLineZ = CircleProperty[2];
	double Radius = CircleProperty[3];
	f1 = pow(abs((z - CenterLineZ) / 0.225), 2) + pow(abs((x - CenterLineX) / 0.45), 2) - 1;// Radius* Radius;
}
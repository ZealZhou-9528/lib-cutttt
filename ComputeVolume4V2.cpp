#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
double vector_det(vector< vector<double> > matrix);
double ComputeVolume4V2(vector<double> xcoord, vector<double> ycoord, vector<double> zcoord)
{
	double x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4;
	x1 = xcoord[0];
	x2 = xcoord[1];
	x3 = xcoord[2];
	x4 = xcoord[3];
	y1 = ycoord[0];
	y2 = ycoord[1];
	y3 = ycoord[2];
	y4 = ycoord[3];
	z1 = zcoord[0];
	z2 = zcoord[1];
	z3 = zcoord[2];
	z4 = zcoord[3];

	vector<vector<double>> A(4,vector<double>(4,0));
	A[0][0] = 1; A[0][1] = x1; A[0][2] = y1; A[0][3] = z1;
	A[1][0] = 1; A[1][1] = x2; A[1][2] = y2; A[1][3] = z2;
	A[2][0] = 1; A[2][1] = x3; A[2][2] = y3; A[2][3] = z3;
	A[3][0] = 1; A[3][1] = x4; A[3][2] = y4; A[3][3] = z4;
	double V;
	V = abs(vector_det(A) / 6);
	return V;
}
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void Boundarymatrix(vector<vector<double>>& matix_e, double TotalVolume, vector<double>& Tot_Bond_value, vector< vector<double> >& gcoord, int iopt)
{
	int nnode = gcoord.size();
	double Xmax = gcoord[0][0], Xmin = gcoord[0][0];
	double Ymax = gcoord[0][1], Ymin = gcoord[0][1];
	double Zmax = gcoord[0][2], Zmin = gcoord[0][2];
	for (size_t i = 1; i < gcoord.size(); i++)
	{
		if (Xmax < gcoord[i][0]) Xmax = gcoord[i][0];
		if (Xmin > gcoord[i][0]) Xmin = gcoord[i][0];
		if (Ymax < gcoord[i][1]) Ymax = gcoord[i][1];
		if (Ymin > gcoord[i][1]) Ymin = gcoord[i][1];
		if (Zmax < gcoord[i][2]) Zmax = gcoord[i][2];
		if (Zmin > gcoord[i][2]) Zmin = gcoord[i][2];

	}
	Tot_Bond_value[0] = Xmin;
	Tot_Bond_value[1] = Xmax;
	Tot_Bond_value[2] = Ymin;
	Tot_Bond_value[3] = Ymax;
	TotalVolume = (Zmax - Zmin) * (Ymax - Ymin) * (Xmax - Xmin);
	if (iopt == 1)
	{
		matix_e[0][0] = 0.01; matix_e[0][1] = 0; matix_e[0][2] = 0;
		matix_e[1][0] = 0; matix_e[1][1] = 0; matix_e[1][2] = 0;
		matix_e[2][0] = 0; matix_e[2][1] = 0; matix_e[2][2] = 0;
	}
	else if (iopt == 2)
	{
		matix_e[0][0] = 0; matix_e[0][1] = 0; matix_e[0][2] = 0;
		matix_e[1][0] = 0; matix_e[1][1] = 0.01; matix_e[1][2] = 0;
		matix_e[2][0] = 0; matix_e[2][1] = 0; matix_e[2][2] = 0;
	}
	else if (iopt == 3)
	{
		matix_e[0][0] = 0; matix_e[0][1] = 0; matix_e[0][2] = 0;
		matix_e[1][0] = 0; matix_e[1][1] = 0; matix_e[1][2] = 0;
		matix_e[2][0] = 0; matix_e[2][1] = 0; matix_e[2][2] = 0.01;
	}
	else if (iopt == 4)
	{
		matix_e[0][0] = 0; matix_e[0][1] = 0.01; matix_e[0][2] = 0;
		matix_e[1][0] = 0.01; matix_e[1][1] = 0; matix_e[1][2] = 0;
		matix_e[2][0] = 0; matix_e[2][1] = 0; matix_e[2][2] = 0;
	}
	else if (iopt == 5)
	{
		matix_e[0][0] = 0; matix_e[0][1] = 0; matix_e[0][2] = 0.01;
		matix_e[1][0] = 0; matix_e[1][1] = 0; matix_e[1][2] = 0;
		matix_e[2][0] = 0.01; matix_e[2][1] = 0; matix_e[2][2] = 0;
	}
	else if (iopt == 6)
	{
		matix_e[0][0] = 0; matix_e[0][1] = 0; matix_e[0][2] = 0;
		matix_e[1][0] = 0; matix_e[1][1] = 0; matix_e[1][2] = 0.01;
		matix_e[2][0] = 0; matix_e[2][1] = 0.01; matix_e[2][2] = 0;
	}
}
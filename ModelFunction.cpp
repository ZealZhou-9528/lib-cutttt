#include <iostream>
#include <vector>
using namespace std;
void ModelFunction(vector<vector<double>> CenterPoints, double CircumR, vector<vector<double>> &CirclesProperty)
{
	int cpn = CenterPoints.size();
	vector<double> CenterPointx(cpn,0);
	for (int i = 0; i < cpn; i++)
	{
		CenterPointx[i] = CenterPoints[i][0];
	}
	vector<double> CenterPointy(cpn, 0);
	for (int i = 0; i < cpn; i++)
	{
		CenterPointy[i] = CenterPoints[i][1];
	}
	vector<double> CenterPointz(cpn, 0);
	for (int i = 0; i < cpn; i++)
	{
		CenterPointz[i] = CenterPoints[i][2];
	}

	for (int i = 0; i < cpn; i++)
	{
		CirclesProperty[i][0] = CenterPointx[i];
	}
	for (int i = 0; i < cpn; i++)
	{
		CirclesProperty[i][1] = CenterPointy[i];
	}
	for (int i = 0; i < cpn; i++)
	{
		CirclesProperty[i][2] = CenterPointz[i];
	}
	for (int i = 0; i < cpn; i++)
	{
		CirclesProperty[i][3] = CircumR;
	}
}
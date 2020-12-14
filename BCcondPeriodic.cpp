#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void SelectionPeriodNodes(vector<vector<double>>& dofFace, vector<vector<double>>& dofVaule, vector<vector<double>>& h0, vector<int> Fxh, vector<int> Fx0, vector<int> Fyh, vector<int> Fy0, vector<int> Fzh, vector<int> Fz0, vector< vector<double> >& gcoord, double tole);
void BCcondPeriodic(vector<vector<double>>& Tab_dep,vector< vector<double> >& gcoord, vector<vector<double>>& matix_e, int Mode)
{
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
	vector<int> x0;
	for (size_t i = 0; i < gcoord.size(); i++)
	{
		if (gcoord[i][0] == Xmin) x0.push_back(i);
	}
	vector<int> y0;
	for (size_t i = 0; i < gcoord.size(); i++)
	{
		if (gcoord[i][1] == Ymin) y0.push_back(i);
	}
	vector<int> z0;
	for (size_t i = 0; i < gcoord.size(); i++)
	{
		if (gcoord[i][2] == Zmin) z0.push_back(i);
	}
	vector<int> xh;
	for (size_t i = 0; i < gcoord.size(); i++)
	{
		if (gcoord[i][0] == Xmax) xh.push_back(i);
	}
	vector<int> yh;
	for (size_t i = 0; i < gcoord.size(); i++)
	{
		if (gcoord[i][1] == Ymax) yh.push_back(i);
	}
	vector<int> zh;
	for (size_t i = 0; i < gcoord.size(); i++)
	{
		if (gcoord[i][2] == Zmax) zh.push_back(i);
	}
	//////////////////////////////////////////////
	vector<int> Fx0, Fxh, Fy0, Fyh, Fz0, Fzh;
	Fy0 = y0; Fyh = yh;
	Fx0 = x0; Fxh = xh;
	Fz0 = z0; Fzh = zh;
	///////////////////
	vector<vector<double>> h0;// (3, vector<double>(3, 0));
	h0 = matix_e;
	double tole = (Xmax - Xmin) / 40000;
	vector<vector<double>> dofFace;
	vector<vector<double>> dofVaule;
	vector<double> Tab_deprow;
	SelectionPeriodNodes(dofFace, dofVaule, matix_e, Fxh, Fx0, Fyh, Fy0, Fzh, Fz0, gcoord, tole);
	for (size_t i = 0; i < dofFace.size(); i++)
	{
		Tab_deprow.push_back(dofFace[i][0]);
		Tab_deprow.push_back(dofFace[i][1]);
		Tab_deprow.push_back(dofVaule[i][0]);
		Tab_deprow.push_back(dofVaule[i][1]);
		Tab_deprow.push_back(dofVaule[i][2]);
		Tab_dep.push_back(Tab_deprow);
		Tab_deprow.clear();
	}
	int adc = 0;
}
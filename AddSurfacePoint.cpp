#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void AddSurfacePoint(vector< vector<double> >& gcoord,vector<int>& SinglePointXmin, vector<int>& SinglePointXmax, vector<int>& SinglePointYmin, vector<int>& SinglePointYmax, vector<int>& SinglePointZmin, vector<int>& SinglePointZmax, vector<vector<double>>& Newcoord)
{
	double X2 = gcoord[0][0], X1 = gcoord[0][0];
	double Y2 = gcoord[0][1], Y1 = gcoord[0][1];
	double Z2 = gcoord[0][2], Z1 = gcoord[0][2];
	for (size_t i = 1; i < gcoord.size(); i++)
	{
		if (X2 < gcoord[i][0]) X2 = gcoord[i][0];
		if (X1 > gcoord[i][0]) X1 = gcoord[i][0];
		if (Y2 < gcoord[i][1]) Y2 = gcoord[i][1];
		if (Y1 > gcoord[i][1]) Y1 = gcoord[i][1];
		if (Z2 < gcoord[i][2]) Z2 = gcoord[i][2];
		if (Z1 > gcoord[i][2]) Z1 = gcoord[i][2];
	}
	vector<double> NewcoordXmin, NewcoordXmax, NewcoordYmin, NewcoordYmax, NewcoordZmin, NewcoordZmax;
	vector<double> AA;
	//////////////////////////////
	if (SinglePointXmin.size()!=0)
	{
		for (size_t i = 0; i < SinglePointXmin.size(); i++)
		{
			AA.push_back(gcoord[SinglePointXmin[i]][0]);
			AA.push_back(gcoord[SinglePointXmin[i]][1]);
			AA.push_back(gcoord[SinglePointXmin[i]][2]);
			AA[0] = X2;
			for (size_t i2 = 0; i2 < AA.size(); i2++)
			{
				NewcoordXmax.push_back(AA[i2]);
			}
			AA.clear();
		}
	}
	////////////////////////////////
	if (SinglePointXmax.size() != 0)
	{
		for (size_t i = 0; i < SinglePointXmax.size(); i++)
		{
			AA.push_back(gcoord[SinglePointXmax[i]][0]);
			AA.push_back(gcoord[SinglePointXmax[i]][1]);
			AA.push_back(gcoord[SinglePointXmax[i]][2]);
			AA[0] = X1;
			for (size_t i2 = 0; i2 < AA.size(); i2++)
			{
				NewcoordXmin.push_back(AA[i2]);
			}
			AA.clear();
		}
	}
	////////////////////////////////
	if (SinglePointYmin.size() != 0)
	{
		for (size_t i = 0; i < SinglePointYmin.size(); i++)
		{
			AA.push_back(gcoord[SinglePointYmin[i]][0]);
			AA.push_back(gcoord[SinglePointYmin[i]][1]);
			AA.push_back(gcoord[SinglePointYmin[i]][2]);
			AA[1] = Y2;
			for (size_t i2 = 0; i2 < AA.size(); i2++)
			{
				NewcoordYmax.push_back(AA[i2]);
			}
			AA.clear();
		}
	}
	////////////////////////////////
	if (SinglePointYmax.size() != 0)
	{
		for (size_t i = 0; i < SinglePointYmax.size(); i++)
		{
			AA.push_back(gcoord[SinglePointYmax[i]][0]);
			AA.push_back(gcoord[SinglePointYmax[i]][1]);
			AA.push_back(gcoord[SinglePointYmax[i]][2]);
			AA[1] = Y1;
			for (size_t i2 = 0; i2 < AA.size(); i2++)
			{
				NewcoordYmin.push_back(AA[i2]);
			}
			AA.clear();
		}
	}
	////////////////////////////////
	if (SinglePointZmin.size() != 0)
	{
		for (size_t i = 0; i < SinglePointZmin.size(); i++)
		{
			AA.push_back(gcoord[SinglePointZmin[i]][0]);
			AA.push_back(gcoord[SinglePointZmin[i]][1]);
			AA.push_back(gcoord[SinglePointZmin[i]][2]);
			AA[2] = Z2;
			for (size_t i2 = 0; i2 < AA.size(); i2++)
			{
				NewcoordZmax.push_back(AA[i2]);
			}
			AA.clear();
		}
	}
	////////////////////////////////
	if (SinglePointZmax.size() != 0)
	{
		for (size_t i = 0; i < SinglePointZmax.size(); i++)
		{
			AA.push_back(gcoord[SinglePointZmax[i]][0]);
			AA.push_back(gcoord[SinglePointZmax[i]][1]);
			AA.push_back(gcoord[SinglePointZmax[i]][2]);
			AA[2] = Z1;
			for (size_t i2 = 0; i2 < AA.size(); i2++)
			{
				NewcoordZmin.push_back(AA[i2]);
			}
			AA.clear();
		}
	}

		Newcoord.push_back(NewcoordXmin);
		Newcoord.push_back(NewcoordXmax);
		Newcoord.push_back(NewcoordYmin);
		Newcoord.push_back(NewcoordYmax);
		Newcoord.push_back(NewcoordZmin);
		Newcoord.push_back(NewcoordZmax);
	int Break = 0;
}
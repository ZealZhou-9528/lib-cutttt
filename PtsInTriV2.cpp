#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int PtsInTriV2(vector<double> Pts, vector<vector<double>> Tri,double Offset)
{
	for (size_t i = 0; i < Tri.size(); i++)
	{
		for (size_t i1 = 0; i1 < Tri[i].size(); i1++)
		{
			Tri[i][i1] = Tri[i][i1] + Offset;
		}
	}
	for (size_t i = 0; i < Pts.size(); i++)
	{
		Pts[i]= Pts[i]+ Offset;
	}
	vector<vector<double>> T(2,vector<double>(2,0));
	T[0][0] = Tri[0][0] - Tri[0][2];
	T[1][0] = Tri[1][0] - Tri[1][2];
	T[0][1] = Tri[0][1] - Tri[0][2];
	T[1][1] = Tri[1][1] - Tri[1][2];
	vector<double> lambda(3,0);
	vector<double> b(2,0);
	b[0] = Pts[0] - Tri[0][2];
	b[1] = Pts[2] - Tri[1][2];
	//////////
	//lambda(1:2) = T\b;
	//lambda(3) = 1 - sum(lambda(1:2));
	return 0;
}
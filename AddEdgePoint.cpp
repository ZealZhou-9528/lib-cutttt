#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<double> vectors_setdiff(vector<double> v1, vector<double> v2);
void AddEdgePoint(vector<vector<vector<int> > >& Edge, vector< vector<double> >& gcoord, vector< vector<int> >& nodes, vector<vector<vector<vector<double> > >>& NewEdgePoint)
{
	vector<int> Xedge, Yedge, Zedge;
	vector<int> XL1, XL2, XL3, XL4;
	vector<int> YL1, YL2, YL3, YL4;
	vector<int> ZL1, ZL2, ZL3, ZL4;
	//////////////////////////////////////////////
	for (size_t i = 0; i < Edge[0][0].size(); i++)
	{
		Xedge.push_back(Edge[0][0][i]);
	}
	for (size_t i = 0; i < Edge[0][1].size(); i++)
	{
		Yedge.push_back(Edge[0][1][i]);
	}
	for (size_t i = 0; i < Edge[0][2].size(); i++)
	{
		Zedge.push_back(Edge[0][2][i]);
	}
	//////////////////////////////////////////////
	for (size_t i = 0; i < Edge[1][0].size(); i++)
	{
		XL1.push_back(Edge[1][0][i]);
	}
	for (size_t i = 0; i < Edge[1][1].size(); i++)
	{
		XL2.push_back(Edge[1][1][i]);
	}
	for (size_t i = 0; i < Edge[1][2].size(); i++)
	{
		XL3.push_back(Edge[1][2][i]);
	}
	for (size_t i = 0; i < Edge[1][3].size(); i++)
	{
		XL4.push_back(Edge[1][3][i]);
	}
	//////////////////////////////////////////////
	for (size_t i = 0; i < Edge[2][0].size(); i++)
	{
		YL1.push_back(Edge[2][0][i]);
	}
	for (size_t i = 0; i < Edge[2][1].size(); i++)
	{
		YL2.push_back(Edge[2][1][i]);
	}
	for (size_t i = 0; i < Edge[2][2].size(); i++)
	{
		YL3.push_back(Edge[2][2][i]);
	}
	for (size_t i = 0; i < Edge[2][3].size(); i++)
	{
		YL4.push_back(Edge[2][3][i]);
	}
	////////////////////////////////////////////////
	for (size_t i = 0; i < Edge[3][0].size(); i++)
	{
		ZL1.push_back(Edge[3][0][i]);
	}
	for (size_t i = 0; i < Edge[3][1].size(); i++)
	{
		ZL2.push_back(Edge[3][1][i]);
	}
	for (size_t i = 0; i < Edge[3][2].size(); i++)
	{
		ZL3.push_back(Edge[3][2][i]);
	}
	for (size_t i = 0; i < Edge[3][3].size(); i++)
	{
		ZL4.push_back(Edge[3][3][i]);
	}
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	vector<double> Xcoordinate;
	for (size_t i = 0; i < Xedge.size(); i++)
	{
		Xcoordinate.push_back(gcoord[Xedge[i]][0]);
	}
	sort(Xcoordinate.begin(), Xcoordinate.end());
	Xcoordinate.erase(unique(Xcoordinate.begin(), Xcoordinate.end()), Xcoordinate.end());
	////NewXL1////
	vector<double> gcoordXL1;
	for (size_t i = 0; i < XL1.size(); i++)
	{
		gcoordXL1.push_back(gcoord[XL1[i]][0]);
	}
	vector<double> NewXL1 = vectors_setdiff(Xcoordinate, gcoordXL1);
	vector< vector<double> > NewPointXL1(NewXL1.size());
	double g1max, g1min, g2max, g2min, g3max, g3min;
	g1max = gcoord[0][0], g1min = gcoord[0][0];  //gcoord.size()
	g2max = gcoord[0][1], g2min = gcoord[0][1];
	g3max = gcoord[0][2], g3min = gcoord[0][2];
	for (int i = 1; i < gcoord.size(); i++)        //ÕÒ³ög1max, g1min
	{
		if (g1max < gcoord[i][0]) g1max = gcoord[i][0];
		if (g1min > gcoord[i][0]) g1min = gcoord[i][0];
		if (g2max < gcoord[i][1]) g2max = gcoord[i][1];
		if (g2min > gcoord[i][1]) g2min = gcoord[i][1];
		if (g3max < gcoord[i][2]) g3max = gcoord[i][2];
		if (g3min > gcoord[i][2]) g3min = gcoord[i][2];
	}

	//for (int i = 1; i < gcoord.size(); i++)         //ÕÒ³ög2max, g2min
	//{
	//	if (g2max < gcoord[i][1])
	//	{
	//		g2max = gcoord[i][1];
	//	}
	//	if (g2min > gcoord[i][1])
	//	{
	//		g2min = gcoord[i][1];
	//	}
	//}

	//for (int i = 1; i < gcoord.size(); i++)         //ÕÒ³ög3max, g3min
	//{
	//	if (g3max < gcoord[i][2])
	//	{
	//		g3max = gcoord[i][2];
	//	}
	//	if (g3min > gcoord[i][2])
	//	{
	//		g3min = gcoord[i][2];
	//	}
	//}

	for (size_t i = 0; i < NewXL1.size(); i++)
	{
		NewPointXL1[i].push_back(NewXL1[i]);
		NewPointXL1[i].push_back(g2min);
		NewPointXL1[i].push_back(g3min);
	}
	////NewXL2////
	vector<double> gcoordXL2;
	for (size_t i = 0; i < XL2.size(); i++)
	{
		gcoordXL2.push_back(gcoord[XL2[i]][0]);
	}
	vector<double> NewXL2 = vectors_setdiff(Xcoordinate, gcoordXL2);
	vector< vector<double> > NewPointXL2(NewXL2.size());
	for (size_t i = 0; i < NewXL2.size(); i++)
	{
		NewPointXL2[i].push_back(NewXL2[i]);
		NewPointXL2[i].push_back(g2max);
		NewPointXL2[i].push_back(g3min);
	}
	////NewXL3////
	vector<double> gcoordXL3;
	for (size_t i = 0; i < XL3.size(); i++)
	{
		gcoordXL3.push_back(gcoord[XL3[i]][0]);
	}
	vector<double> NewXL3 = vectors_setdiff(Xcoordinate, gcoordXL3);
	vector< vector<double> > NewPointXL3(NewXL3.size());
	for (size_t i = 0; i < NewXL3.size(); i++)
	{
		NewPointXL3[i].push_back(NewXL3[i]);
		NewPointXL3[i].push_back(g2min);
		NewPointXL3[i].push_back(g3max);
	}
	////NewXL4////
	vector<double> gcoordXL4;
	for (size_t i = 0; i < XL4.size(); i++)
	{
		gcoordXL4.push_back(gcoord[XL4[i]][0]);
	}
	vector<double> NewXL4 = vectors_setdiff(Xcoordinate, gcoordXL4);
	vector< vector<double> > NewPointXL4(NewXL4.size());
	for (size_t i = 0; i < NewXL4.size(); i++)
	{
		NewPointXL4[i].push_back(NewXL4[i]);
		NewPointXL4[i].push_back(g2min);
		NewPointXL4[i].push_back(g3max);
	}
	///////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////
	vector<double> Ycoordinate;
	for (size_t i = 0; i < Yedge.size(); i++)
	{
		Ycoordinate.push_back(gcoord[Yedge[i]][1]);
	}
	sort(Ycoordinate.begin(), Ycoordinate.end());
	Ycoordinate.erase(unique(Ycoordinate.begin(), Ycoordinate.end()), Ycoordinate.end());
	////NewYL1////
	vector<double> gcoordYL1;
	for (size_t i = 0; i < YL1.size(); i++)
	{
		gcoordYL1.push_back(gcoord[YL1[i]][1]);
	}
	vector<double> NewYL1 = vectors_setdiff(Ycoordinate, gcoordYL1);
	vector< vector<double> > NewPointYL1(NewYL1.size());
	for (size_t i = 0; i < NewYL1.size(); i++)
	{
		NewPointYL1[i].push_back(g1min);
		NewPointYL1[i].push_back(NewYL1[i]);
		NewPointYL1[i].push_back(g3min);
	}
	////NewYL2////
	vector<double> gcoordYL2;
	for (size_t i = 0; i < YL2.size(); i++)
	{
		gcoordYL2.push_back(gcoord[YL2[i]][1]);
	}
	vector<double> NewYL2 = vectors_setdiff(Ycoordinate, gcoordYL2);
	vector< vector<double> > NewPointYL2(NewYL2.size());
	for (size_t i = 0; i < NewYL2.size(); i++)
	{
		NewPointYL2[i].push_back(g1max);
		NewPointYL2[i].push_back(NewYL2[i]);
		NewPointYL2[i].push_back(g3min);
	}
	////NewYL3////
	vector<double> gcoordYL3;
	for (size_t i = 0; i < YL3.size(); i++)
	{
		gcoordYL3.push_back(gcoord[YL3[i]][1]);
	}
	vector<double> NewYL3 = vectors_setdiff(Ycoordinate, gcoordYL3);
	vector< vector<double> > NewPointYL3(NewYL3.size());
	for (size_t i = 0; i < NewYL3.size(); i++)
	{
		NewPointYL3[i].push_back(g1min);
		NewPointYL3[i].push_back(NewYL3[i]);
		NewPointYL3[i].push_back(g3max);
	}
	////NewYL4////
	vector<double> gcoordYL4;
	for (size_t i = 0; i < YL4.size(); i++)
	{
		gcoordYL4.push_back(gcoord[YL4[i]][1]);
	}
	vector<double> NewYL4 = vectors_setdiff(Ycoordinate, gcoordYL4);
	vector< vector<double> > NewPointYL4(NewYL4.size());
	for (size_t i = 0; i < NewYL4.size(); i++)
	{
		NewPointYL4[i].push_back(g1max);
		NewPointYL4[i].push_back(NewYL4[i]);
		NewPointYL4[i].push_back(g3max);
	}
	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////
	vector<double> Zcoordinate;
	for (size_t i = 0; i < Zedge.size(); i++)
	{
		Zcoordinate.push_back(gcoord[Zedge[i]][2]);
	}
	sort(Zcoordinate.begin(), Zcoordinate.end());
	Zcoordinate.erase(unique(Zcoordinate.begin(), Zcoordinate.end()), Zcoordinate.end());
	////NewZL1////
	vector<double> gcoordZL1;
	for (size_t i = 0; i < ZL1.size(); i++)
	{
		gcoordZL1.push_back(gcoord[ZL1[i]][2]);
	}
	vector<double> NewZL1 = vectors_setdiff(Zcoordinate, gcoordZL1);
	vector< vector<double> > NewPointZL1(NewZL1.size());
	for (size_t i = 0; i < NewZL1.size(); i++)
	{
		NewPointZL1[i].push_back(g1min);
		NewPointZL1[i].push_back(g2min);
		NewPointZL1[i].push_back(NewZL1[i]);
	}
	////NewZL2////
	vector<double> gcoordZL2;
	for (size_t i = 0; i < ZL2.size(); i++)
	{
		gcoordZL2.push_back(gcoord[ZL2[i]][2]);
	}
	vector<double> NewZL2 = vectors_setdiff(Zcoordinate, gcoordZL2);
	vector< vector<double> > NewPointZL2(NewZL2.size());
	for (size_t i = 0; i < NewZL2.size(); i++)
	{
		NewPointZL2[i].push_back(g1max);
		NewPointZL2[i].push_back(g2min);
		NewPointZL2[i].push_back(NewZL2[i]);
	}
	////NewZL3////
	vector<double> gcoordZL3;
	for (size_t i = 0; i < ZL3.size(); i++)
	{
		gcoordZL3.push_back(gcoord[ZL3[i]][2]);
	}
	vector<double> NewZL3 = vectors_setdiff(Zcoordinate, gcoordZL3);
	vector< vector<double> > NewPointZL3(NewZL3.size());
	for (size_t i = 0; i < NewZL3.size(); i++)
	{
		NewPointZL3[i].push_back(g1min);
		NewPointZL3[i].push_back(g2max);
		NewPointZL3[i].push_back(NewZL3[i]);
	}
	////NewZL4////
	vector<double> gcoordZL4;
	for (size_t i = 0; i < ZL4.size(); i++)
	{
		gcoordZL4.push_back(gcoord[ZL4[i]][2]);
	}
	vector<double> NewZL4 = vectors_setdiff(Zcoordinate, gcoordZL4);
	vector< vector<double> > NewPointZL4(NewZL4.size());
	for (size_t i = 0; i < NewZL4.size(); i++)
	{
		NewPointZL4[i].push_back(g1max);
		NewPointZL4[i].push_back(g2max);
		NewPointZL4[i].push_back(NewZL4[i]);
	}
	///////NewEdgePoint/////////
	///////NewEdgePoint/////////
	NewEdgePoint[0].push_back(NewPointXL1);
	NewEdgePoint[0].push_back(NewPointXL2);
	NewEdgePoint[0].push_back(NewPointXL3);
	NewEdgePoint[0].push_back(NewPointXL4);
	//////////////////////////////////////
	NewEdgePoint[1].push_back(NewPointYL1);
	NewEdgePoint[1].push_back(NewPointYL2);
	NewEdgePoint[1].push_back(NewPointYL3);
	NewEdgePoint[1].push_back(NewPointYL4);
	//////////////////////////////////////
	NewEdgePoint[2].push_back(NewPointZL1);
	NewEdgePoint[2].push_back(NewPointZL2);
	NewEdgePoint[2].push_back(NewPointZL3);
	NewEdgePoint[2].push_back(NewPointZL4);
}

vector<double> vectors_setdiff(vector<double> v1, vector<double> v2)
{
	vector<double> v;
	int outpd = 0;
	for (int i = 0; i < v1.size(); i++)
	{
		for (int i1 = 0; i1 < v2.size(); i1++)
		{
			if (v1[i] != v2[i1])
			{
				outpd = outpd + 1;
			}
		}
		if (outpd == v2.size())
		{
			v.push_back(v1[i]);
		}
		outpd = 0;
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	return v;
}
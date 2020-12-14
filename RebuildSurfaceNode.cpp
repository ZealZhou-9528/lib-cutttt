#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> vectors_intersection(vector<int> v1, vector<int> v2);
void RebuildSurfaceNode(vector< vector<float> >& gcoord, vector< vector<int> >& nodes, vector<vector<float>>& Newcoord, vector<vector<int>>& SurfacePoint, vector<vector<vector<int> > >& Edge)
{
	vector<float> NewcoordXmin, NewcoordXmax, NewcoordYmin, NewcoordYmax, NewcoordZmin, NewcoordZmax;
	for (size_t i = 0; i < Newcoord[0].size(); i++)
	{
		NewcoordXmin.push_back(Newcoord[0][i]);
	}
	for (size_t i = 0; i < Newcoord[1].size(); i++)
	{
		NewcoordXmax.push_back(Newcoord[1][i]);
	}
	for (size_t i = 0; i < Newcoord[2].size(); i++)
	{
		NewcoordYmin.push_back(Newcoord[2][i]);
	}
	for (size_t i = 0; i < Newcoord[3].size(); i++)
	{
		NewcoordYmax.push_back(Newcoord[3][i]);
	}
	for (size_t i = 0; i < Newcoord[4].size(); i++)
	{
		NewcoordZmin.push_back(Newcoord[4][i]);
	}
	for (size_t i = 0; i < Newcoord[5].size(); i++)
	{
		NewcoordZmax.push_back(Newcoord[5][i]);
	}
	//Gcoord=[Gcoord;NewcoordXmin;NewcoordXmax;NewcoordYmin;NewcoordYmax;NewcoordZmin;NewcoordZmax];
	vector<vector<float>> Gcoord;
	Gcoord.push_back(NewcoordXmin);
	Gcoord.push_back(NewcoordXmax);
	Gcoord.push_back(NewcoordYmin);
	Gcoord.push_back(NewcoordYmax);
	Gcoord.push_back(NewcoordZmin);
	Gcoord.push_back(NewcoordZmax);
	/////////////////////////////////
	vector<int> Xmin, Ymin, Zmin, Xmax, Ymax, Zmax;
	Xmin = SurfacePoint[0];
	Ymin = SurfacePoint[1];
	Zmin = SurfacePoint[2];
	Xmax = SurfacePoint[3];
	Ymax = SurfacePoint[4];
	Zmax = SurfacePoint[5];
	////////////////////////////////
	vector<int> XminEdge, YminEdge, ZminEdge, XmaxEdge, YmaxEdge, ZmaxEdge;
	////XminEdge////
	for (size_t i = 0; i < Edge[2][0].size(); i++)
	{
		XminEdge.push_back(Edge[2][0][i]);
	}
	for (size_t i = 0; i < Edge[2][2].size(); i++)
	{
		XminEdge.push_back(Edge[2][2][i]);
	}
	for (size_t i = 0; i < Edge[3][0].size(); i++)
	{
		XminEdge.push_back(Edge[3][0][i]);
	}
	for (size_t i = 0; i < Edge[3][2].size(); i++)
	{
		XminEdge.push_back(Edge[3][2][i]);
	}
	////XmaxEdge////
	for (size_t i = 0; i < Edge[2][1].size(); i++)
	{
		XmaxEdge.push_back(Edge[2][1][i]);
	}
	for (size_t i = 0; i < Edge[2][3].size(); i++)
	{
		XmaxEdge.push_back(Edge[2][3][i]);
	}
	for (size_t i = 0; i < Edge[3][1].size(); i++)
	{
		XmaxEdge.push_back(Edge[3][1][i]);
	}
	for (size_t i = 0; i < Edge[3][3].size(); i++)
	{
		XmaxEdge.push_back(Edge[3][3][i]);
	}
	////YminEdge////
	for (size_t i = 0; i < Edge[1][0].size(); i++)
	{
		YminEdge.push_back(Edge[1][0][i]);
	}
	for (size_t i = 0; i < Edge[1][2].size(); i++)
	{
		YminEdge.push_back(Edge[1][2][i]);
	}
	for (size_t i = 0; i < Edge[3][0].size(); i++)
	{
		YminEdge.push_back(Edge[3][0][i]);
	}
	for (size_t i = 0; i < Edge[3][1].size(); i++)
	{
		YminEdge.push_back(Edge[3][1][i]);
	}
	////YmaxEdge////
	for (size_t i = 0; i < Edge[1][1].size(); i++)
	{
		YmaxEdge.push_back(Edge[1][1][i]);
	}
	for (size_t i = 0; i < Edge[1][3].size(); i++)
	{
		YmaxEdge.push_back(Edge[1][3][i]);
	}
	for (size_t i = 0; i < Edge[3][2].size(); i++)
	{
		YmaxEdge.push_back(Edge[3][2][i]);
	}
	for (size_t i = 0; i < Edge[3][3].size(); i++)
	{
		YmaxEdge.push_back(Edge[3][3][i]);
	}
	////ZminEdge////
	for (size_t i = 0; i < Edge[1][0].size(); i++)
	{
		ZminEdge.push_back(Edge[1][0][i]);
	}
	for (size_t i = 0; i < Edge[1][1].size(); i++)
	{
		ZminEdge.push_back(Edge[1][1][i]);
	}
	for (size_t i = 0; i < Edge[2][0].size(); i++)
	{
		ZminEdge.push_back(Edge[2][0][i]);
	}
	for (size_t i = 0; i < Edge[2][1].size(); i++)
	{
		ZminEdge.push_back(Edge[2][1][i]);
	}
	////ZmaxEdge////
	for (size_t i = 0; i < Edge[1][2].size(); i++)
	{
		ZmaxEdge.push_back(Edge[1][2][i]);
	}
	for (size_t i = 0; i < Edge[1][3].size(); i++)
	{
		ZmaxEdge.push_back(Edge[1][3][i]);
	}
	for (size_t i = 0; i < Edge[2][2].size(); i++)
	{
		ZmaxEdge.push_back(Edge[2][2][i]);
	}
	for (size_t i = 0; i < Edge[2][3].size(); i++)
	{
		ZmaxEdge.push_back(Edge[2][3][i]);
	}
	//////////////////////////////////////////////////
	for (size_t i = 0; i < XminEdge.size(); i++)
	{
		Xmin.push_back(XminEdge[i]);
	}
	for (size_t i = 0; i < YminEdge.size(); i++)
	{
		Ymin.push_back(YminEdge[i]);
	}
	for (size_t i = 0; i < ZminEdge.size(); i++)
	{
		Zmin.push_back(ZminEdge[i]);
	}
	for (size_t i = 0; i < XmaxEdge.size(); i++)
	{
		Xmax.push_back(XmaxEdge[i]);
	}
	for (size_t i = 0; i < YmaxEdge.size(); i++)
	{
		Ymax.push_back(YmaxEdge[i]);
	}
	for (size_t i = 0; i < ZmaxEdge.size(); i++)
	{
		Zmax.push_back(ZmaxEdge[i]);
	}
	////////////////////////////////////////
	float maxG1 = Gcoord[0][0];
	float minG2 = Gcoord[0][1];
	for (size_t i = 1; i < Gcoord.size(); i++)
	{
		if (maxG1 < Gcoord[i][0]) maxG1 = Gcoord[i][0];
		if (minG2 > Gcoord[i][1]) minG2 = Gcoord[i][0];
	}
	float Offset = 0.5 * maxG1 - minG2 + 1;
	//b=sum(a,dim); 
	//a表示矩阵；
	//dim等于1或者2，1表示每一列进行求和，2表示每一行进行求和；
	//b表示求得的行向量。

	//ismember(a,b)是看矩阵a中的数是不是矩阵b中的成员，是的话结果返回1，不是返回0；
	vector<vector<int>> C(nodes.size(), vector<int>(4, 0));
	vector<vector<int>> D(nodes.size(), vector<int>(4, 0));
	vector<int> E(nodes.size(),0);
	vector<vector<int>> nodeXmin1, nodeXmin2, nodeXmin3;
	vector<float> Pts(2,0);
	vector<int> zc(2, 0);
	vector<int> inter;
	int X = 0, Y = 0;
	vector<vector<float>> Tri(2, vector<float>(3, 0));
	for (size_t i = 0; i < NewcoordXmin.size(); i++)
	{
		Pts[0] = NewcoordXmin[i * 3 + 2];
		Pts[1] = NewcoordXmin[i * 3 + 3];
		//[C,D]=ismember(nodes,Xmin);
		for (size_t i1 = 0; i1 < nodes.size(); i1++)
		{
			for (size_t i2 = 0; i2 < 4; i2++)
			{
				for (size_t i3 = 0; i3 < Xmin.size(); i3++)
				{
					if (nodes[i1][i2] == Xmin[i3])
					{
						C[i1][i2] = 1;
						D[i1][i2] = i3;
						break;
					}
				}
			}
		}
		//E=sum(C,2);
		for (size_t i1 = 0; i1 < C.size(); i1++)
		{
			E[i1] = C[i1][0] + C[i1][1] + C[i1][2] + C[i1][3];
		}
		for (size_t i1 = 0; i1 < E.size(); i1++)
		{
			if (E[i1] == 3)
			{
				zc[0] = i1, zc[1] = 0;
				nodeXmin3.push_back(zc);
			}
			if (E[i1] == 2)
			{
				zc[0] = i1, zc[1] = 0;
				nodeXmin2.push_back(zc);
			}
			if (E[i1] == 1)
			{
				zc[0] = i1, zc[1] = 0;
				nodeXmin1.push_back(zc);
			}
		}
		for (size_t N3 = 0; N3 < nodeXmin3.size(); N3++)
		{
			inter = vectors_intersection(nodes[nodeXmin3[N3][0]], Xmin);
			nodeXmin3[N3][1] = inter[0];
		}
		for (size_t N2 = 0; N2 < nodeXmin2.size(); N2++)
		{
			inter = vectors_intersection(nodes[nodeXmin2[N2][0]], Xmin);
			nodeXmin3[N2][1] = inter[0];
		}
		for (size_t N1 = 0; N1 < nodeXmin1.size(); N1++)
		{
			inter = vectors_intersection(nodes[nodeXmin1[N1][0]], Xmin);
			nodeXmin3[N1][1] = inter[0];
		}
		X = 0, Y = 0;
		for (size_t j = 0; j < nodeXmin3.size(); j++)
		{
			Tri[0][0] = Gcoord[nodeXmin3[j][1]][1];
			Tri[0][1] = Gcoord[nodeXmin3[j][2]][1];
			Tri[0][2] = Gcoord[nodeXmin3[j][3]][1];
			Tri[1][0] = Gcoord[nodeXmin3[j][1]][2];
			Tri[1][1] = Gcoord[nodeXmin3[j][2]][2];
			Tri[1][2] = Gcoord[nodeXmin3[j][3]][2];
		}


	}
}

vector<int> vectors_intersection(vector<int> v1, vector<int> v2)
{
	vector<int> v;
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v));//求交集 
	return v;
}
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void ModelFunction(vector<vector<double>> CenterPoints, double CircumR, vector<vector<double>>& CirclesProperty);
void CutElement2(vector< vector<int> >& ElementStatus, vector<vector<double>> CirclesProperty, vector< vector<double> >& gcoord, vector< vector<int> >& nodes, double Cycle, double Magnitude, double CrossSectExp, double p, double q);
void CutEleWithFun2(vector< vector<double> >& gcoord, vector< vector<int> >& nodes, vector<int> CrossElement, double CircleProperty[4], double Cycle, double Magnitude, int ni, double CrossSectExp, double p, double q);
void FindSinglePoint(vector< vector<double> >& gcoord, vector< vector<int> >& nodes, vector<int>& SinglePointXmin, vector<int>& SinglePointXmax, vector<int>& SinglePointYmin, vector<int>& SinglePointYmax, vector<int>& SinglePointZmin, vector<int>& SinglePointZmax, vector<vector<vector<int> > >& Edge,  vector<vector<int>>& SurfacePoint);
void AddEdgePoint(vector<vector<vector<int> > >& Edge, vector< vector<double> >& gcoord, vector< vector<int> >& nodes, vector<vector<vector<vector<double> > >>& NewEdgePoint);
void AddSurfacePoint(vector< vector<double> >& gcoord, vector<int>& SinglePointXmin, vector<int>& SinglePointXmax, vector<int>& SinglePointYmin, vector<int>& SinglePointYmax, vector<int>& SinglePointZmin, vector<int>& SinglePointZmax, vector<vector<double>>& Newcoord);
//void RebuildSurfaceNode(vector< vector<double> >& gcoord, vector< vector<int> >& nodes, vector<vector<double>>& Newcoord, vector<vector<int>>& SurfacePoint, vector<vector<vector<int> > >& Edge);
void CutModel2st(vector< vector<double> >& gcoord, vector< vector<int> >& nodes, vector< vector<int> >& InnerElementsmain, vector<int>& OuterElementsmain, double CircumR, double CircumRint, double Magnitude, double CrossSectExp, double p, double q)
{
	//模型基本属性
	double Xmax, Xmin, Ymax, Ymin, Zmax, Zmin;
	Xmax = gcoord[0][0], Xmin = gcoord[0][0];  //gcoord.size()
	Ymax = gcoord[0][1], Ymin = gcoord[0][1];
	Zmax = gcoord[0][2], Zmin = gcoord[0][2];
	for (int i = 1; i < gcoord.size(); i++)        //找出Xmax, Xmin
	{
		if (Xmax < gcoord[i][0])
		{
			Xmax = gcoord[i][0];
		}
		if (Xmin > gcoord[i][0])
		{
			Xmin = gcoord[i][0];
		}
	}

	for (int i = 1; i < gcoord.size(); i++)         //找出Ymax, Ymin
	{
		if (Ymax < gcoord[i][1])
		{
			Ymax = gcoord[i][1];
		}
		if (Ymin > gcoord[i][1])
		{
			Ymin = gcoord[i][1];
		}
	}

	for (int i = 1; i < gcoord.size(); i++)         //找出Zmax, Zmin
	{
		if (Zmax < gcoord[i][2])
		{
			Zmax = gcoord[i][2];
		}
		if (Zmin > gcoord[i][2])
		{
			Zmin = gcoord[i][2];
		}
	}
	vector<vector<double>> CenterPoints2(3, vector<double>(3, 0));
	CenterPoints2= { {Xmax,Ymax,-Magnitude} ,{0,Ymax,Magnitude},{Xmin,Ymax,-Magnitude} };
	vector<vector<double>> CirclesProperty2(3, vector<double>(4, 0));
	ModelFunction(CenterPoints2, CircumR, CirclesProperty2);

	//筛选出需要被切割的单元
	vector< vector<int> >ElementStatus(nodes.size(), vector<int>(3, 0));
	CutElement2(ElementStatus, CirclesProperty2, gcoord, nodes, CircumRint, Magnitude, CrossSectExp, p, q);

	//int iei[3] = { 0 }, oei[3] = { 0 }, cei[3] = { 0 };    //分别为InnerEle，OuterEle，CrossEle数组容量
	//int ieix = 0, oeix = 0, ceix = 0;    //分别为InnerEle，OuterEle，CrossEle数组顺序
	vector<int> iei(CenterPoints2.size(), 0);
	vector<int> oei(CenterPoints2.size(), 0);
	vector<int> cei(CenterPoints2.size(), 0);
	for (int i = 0; i < CenterPoints2.size(); i++)  //此循环为了确定InnerEle，OuterEle，CrossEle三次的大小
	{
		for (int j = 0; j < nodes.size(); j++)
		{
			switch (ElementStatus[j][i])
			{
			case 1:iei[i] = iei[i] + 1;
				break;
			case 2:oei[i] = oei[i] + 1;
				break;
			case 3:cei[i] = cei[i] + 1;
				break;
			}
		}
	}
	//int ceit = cei[0] + cei[1] + cei[2];  //CrossElement数组的容量
	//int* CrossElement2st = new int[(cei[0] + cei[1] + cei[2])];
	vector<int> CrossElement2st;
	vector<int> InnerEle;
	vector<int> OuterEle;
	vector<int> CrossEle2st;
	for (int i = 0; i < CenterPoints2.size(); i++)
	{
		//int* InnerEle = new int[iei[i]]();
		//int* OuterEle = new int[oei[i]]();
		//int* CrossEle2st = new int[cei[i]]();
		for (int j = 0; j < nodes.size(); j++)
		{
			switch (ElementStatus[j][i])
			{
			case 1:
				InnerEle.push_back(j);
				break;
			case 2:
				OuterEle.push_back(j);
				break;
			case 3:
				CrossEle2st.push_back(j);
				break;
			}
		}
		/*switch (i)
		{
		case 0:
			for (int k1 = 0; k1 < cei[0]; k1++)
			{
				CrossElement2st[k1] = CrossEle2st[k1];
			}
			break;
		case 1:
			for (int k2 = 0; k2 < cei[1]; k2++)
			{
				CrossElement2st[(cei[0] + k2)] = CrossEle2st[k2];
			}
			break;
		case 2:
			for (int k3 = 0; k3 < cei[2]; k3++)
			{
				CrossElement2st[(cei[0] + cei[1] + k3)] = CrossEle2st[k3];
			}
			break;
		}*/
	for (size_t k1 = 0; k1 < cei[i]; k1++)
	{
		CrossElement2st.push_back(CrossEle2st[k1]);
	}

	InnerEle.clear();
	OuterEle.clear();
	CrossEle2st.clear();
	}

	//切割单元
	double CircleProperty[4] = { 0 };
	for (int i = 0; i < CenterPoints2.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			CircleProperty[j] = CirclesProperty2[i][j];
		}
		//CutEleWithFun(Gcoord, Nodes, CrossElement, CircleProperty, Cycle, Magnitude, i);
		CutEleWithFun2(gcoord, nodes, CrossElement2st, CircleProperty, CircumRint, Magnitude, i, CrossSectExp, p, q);
	}
	vector<int> SinglePointXmin, SinglePointXmax, SinglePointYmin, SinglePointYmax, SinglePointZmin, SinglePointZmax;
	vector<vector<vector<int> > > Edge(4);
	//for (int n = 0; n < 4; n++)
	//{
	//	Edge[n].resize(4);
	//}
	vector<vector<int>> SurfacePoint;
	SurfacePoint.resize(6);
	FindSinglePoint(gcoord,nodes, SinglePointXmin, SinglePointXmax, SinglePointYmin, SinglePointYmax, SinglePointZmin, SinglePointZmax, Edge, SurfacePoint);
	vector<vector<vector<vector<double> > >> NewEdgePoint(3);
	AddEdgePoint(Edge, gcoord, nodes, NewEdgePoint);
	vector<vector<double>> Newcoord;
	//Newcoord.resize(6);
	AddSurfacePoint(gcoord, SinglePointXmin, SinglePointXmax, SinglePointYmin, SinglePointYmax, SinglePointZmin, SinglePointZmax, Newcoord);

	//判断筛选之后单元所在位置
	vector<int> InnerElements;// , OuterElements, CrossElements;
	for (int i = 0; i < CenterPoints2.size(); i++)  // for i = 1:size(CirclesProperty,1)
	{
		//int** CrossElesStatu = new int* [nodes.size()];             //nodes行数为行数，CirclesProperty行数为列数
		//for (int i3 = 0; i3 < nodes.size(); i3++)
		//	CrossElesStatu[i3] = new int[3]();
		vector< vector<int> >CrossElesStatu(nodes.size(), vector<int>(3, 0));
		CutElement2(CrossElesStatu, CirclesProperty2, gcoord, nodes, CircumRint, Magnitude, CrossSectExp, p, q);
		vector<int> InnerEles, CrossEles;
		for (int i1 = 0; i1 < nodes.size(); i1++)
		{
			if (CrossElesStatu[i1][i] == 1)
			{
				InnerEles.push_back(i1);
			}
			if (CrossElesStatu[i1][i] == 3)
			{
				CrossEles.push_back(i1);
			}
		}
		int a, aa, b, bb;
		a = InnerEles.size();
		aa = InnerElements.size();
		b = CrossEles.size();
		//bb = 0;
		for (int i2 = 0; i2 < a; i2++)
		{
			InnerElements.push_back(InnerEles[i2]);
			InnerElementsmain[i].push_back(InnerEles[i2]);
		}
	}
	vector<int> AllEles3D(nodes.size(), 0);
	int outpd = 0;
	//OuterElements = setdiff(AllEles3D,InnerElements); 
	//对于向量A,向量B，C=setdiff(A,B)函数返回在向量A中却不在向量B中的元素，并且C中不包含重复元素，并且从小到大排序。
	for (int i = 0; i < nodes.size(); i++)
	{
		AllEles3D[i] = i;
	}
	//for (int i = 0; i < nodes.size(); i++)
	//{
	//	for (int i1 = 0; i1 < InnerElements.size(); i1++)
	//	{
	//		if (AllEles3D[i] != InnerElements[i1])
	//		{
	//			outpd = outpd + 1;
	//		}
	//	}
	//	if (outpd == InnerElements.size())
	//	{
	//		OuterElementsmain.push_back(AllEles3D[i]);
	//	}
	//	outpd = 0;
	//}
	vector<int>::iterator Ifind;
	for (int i = 0; i < AllEles3D.size(); i++)
	{
		//Afind = find(AllEles3D.begin(), AllEles3D.end(), i);
		Ifind = find(InnerElements.begin(), InnerElements.end(), AllEles3D[i]);
		if (Ifind == InnerElements.end())
		{
			OuterElementsmain.push_back(AllEles3D[i]);
		}
	}
	sort(OuterElementsmain.begin(), OuterElementsmain.end());
	OuterElementsmain.erase(unique(OuterElementsmain.begin(), OuterElementsmain.end()), OuterElementsmain.end());
	//a=0
	int a = 0;
}


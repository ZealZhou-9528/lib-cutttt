#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
#include <numeric>
using namespace std;
void ModelFunction(vector<vector<double>> CenterPoints, double CircumR, vector<vector<double>>& CirclesProperty);
void CutElement2_25D(vector< vector<int> >& ElementStatus, vector <vector<double>> CirclesProperty, vector< vector<double> >& gcoord, vector< vector<int> >& nodes, double Cycle, double Magnitude, double CrossSectExp, double p, double q);
//void CutElement(vector< vector<int> >& ElementStatus, vector<vector<double>> CirclesProperty, vector< vector<double> >& gcoord, vector< vector<int> >& nodes, double Cycle, double Magnitude, double CrossSectExp, double p, double q);
void CutEleWithFun2_25D(vector< vector<double> >& gcoord, vector< vector<int> >& nodes, vector<int> CrossElement, double CircleProperty[4], double Cycle, double Magnitude, int ni, double CrossSectExp, double p, double q);
void CutModel2st_25D(vector< vector<double> >& gcoord, vector< vector<int> >& nodes, vector< vector<int> >& InnerElementsmain, vector<int>& OuterElementsmain, double CircumR, double CircumRint, double Magnitude, double CrossSectExp, double p, double q)
{
	omp_set_num_threads(8);
	//模型基本属性
	double Xmax, Xmin, Ymax, Ymin, Zmax, Zmin;
	Xmax = gcoord[0][0], Xmin = gcoord[0][0];  //gcoord.size()
	Ymax = gcoord[0][1], Ymin = gcoord[0][1];
	Zmax = gcoord[0][2], Zmin = gcoord[0][2];
#pragma omp parallel for
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
#pragma omp parallel for
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
#pragma omp parallel for
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
	vector<vector<double>> CenterPoints2(12, vector<double>(3, 0));
	CenterPoints2 = { {Xmax, Ymax, Zmax * 1.35f / 2.025f},{0, Ymax, Zmax * 1.35f / 2.025f},{Xmin, Ymax, Zmax * 1.35f / 2.025f},
	                 {Xmax, Ymax, Zmax * 0.45f / 2.025f},{0, Ymax, Zmax * 0.45f / 2.025f},{Xmin, Ymax, Zmax * 0.45f / 2.025f},
	                 {Xmax, Ymax, Zmin * 0.45f / 2.025f},{0, Ymax, Zmin * 0.45f / 2.025f},{Xmin, Ymax, Zmin * 0.45f / 2.025f} ,
	                 {Xmax, Ymax, Zmin * 1.35f / 2.025f},{0, Ymax, Zmin * 1.35f / 2.025f},{Xmin, Ymax, Zmin * 1.35f / 2.025f} };
	vector<vector<double>> CirclesProperty2(12, vector<double>(4, 0));
	ModelFunction(CenterPoints2, CircumR, CirclesProperty2);

	//筛选出需要被切割的单元
	vector< vector<int> >ElementStatus(nodes.size(), vector<int>(12, 0));
	CutElement2_25D(ElementStatus, CirclesProperty2, gcoord, nodes, CircumRint, Magnitude, CrossSectExp, p, q);

	//int iei[8] = { 0 }, oei[8] = { 0 }, cei[8] = { 0 };    //分别为InnerEle，OuterEle，CrossEle数组容量
	vector<int> iei(CirclesProperty2.size(), 0);
	vector<int> oei(CirclesProperty2.size(), 0);
	vector<int> cei(CirclesProperty2.size(), 0);
	//int ieix = 0, oeix = 0, ceix = 0;    //分别为InnerEle，OuterEle，CrossEle数组顺序
#pragma omp parallel for
	for (int i = 0; i < CirclesProperty2.size(); i++)  //此循环为了确定InnerEle，OuterEle，CrossEle三次的大小
	{
		//#pragma omp parallel for
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
	//int ccei = accumulate(cei.begin(), cei.end(), 0);
	vector<int> CrossElement2st;
	vector<int> InnerEle;
	vector<int> OuterEle;
	vector<int> CrossEle2st;

	for (int i = 0; i < CirclesProperty2.size(); i++)
	{
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
	for (int i = 0; i < CirclesProperty2.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			CircleProperty[j] = CirclesProperty2[i][j];
		}
		//CutEleWithFun(Gcoord, Nodes, CrossElement, CircleProperty, Cycle, Magnitude, i);
		CutEleWithFun2_25D(gcoord, nodes, CrossElement2st, CircleProperty, CircumRint, Magnitude, i, CrossSectExp, p, q);
	}

	//判断筛选之后单元所在位置
	vector<int> InnerElements;// , OuterElements, CrossElements;
//#pragma omp parallel for
	for (int i = 0; i < CirclesProperty2.size(); i++)  // for i = 1:size(CirclesProperty,1)
	{
		//int** CrossElesStatu = new int* [nodes.size()];             //nodes行数为行数，CirclesProperty行数为列数
		//for (int i3 = 0; i3 < nodes.size(); i3++)
		//	CrossElesStatu[i3] = new int[3]();
		vector< vector<int> >CrossElesStatu(nodes.size(), vector<int>(12, 0));
		CutElement2_25D(CrossElesStatu, CirclesProperty2, gcoord, nodes, CircumRint, Magnitude, CrossSectExp, p, q);
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
	//OuterElements = setdiff(AllEles3D,InnerElements); setdiff
	//对于向量A,向量B，C=setdiff(A,B)函数返回在向量A中却不在向量B中的元素，并且C中不包含重复元素，并且从小到大排序。
#pragma omp parallel for
	for (int i = 0; i < nodes.size(); i++)
	{
		AllEles3D[i] = i;
	}
	//vector<int>::iterator Afind;
	vector<int>::iterator Ifind;

	//#pragma omp parallel for
		/*for (int i = 0; i < nodes.size(); i++)
		{
			for (int i1 = 0; i1 < InnerElements.size(); i1++)
			{
				if (AllEles3D[i] != InnerElements[i1])
				{
					outpd = outpd + 1;
				}
			}
			if (outpd == InnerElements.size())
			{
				OuterElementsmain.push_back(AllEles3D[i]);
			}
			outpd = 0;
		}*/
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
	//int a = 0;
	//delete[]CrossElement;
}
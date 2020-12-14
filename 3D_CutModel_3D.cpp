#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
#include <numeric>
using namespace std;
void ModelFunction(vector<vector<double>> CenterPoints, double CircumR, vector<vector<double>> &CirclesProperty);
void CutElement_3D(vector< vector<int> >& ElementStatus, vector <vector<double>> CirclesProperty, vector< vector<double> >& gcoord, vector< vector<int> >& nodes, double Cycle, double Magnitude, double CrossSectExp, double p, double q);
//void CutElement(vector< vector<int> >& ElementStatus, vector<vector<double>> CirclesProperty, vector< vector<double> >& gcoord, vector< vector<int> >& nodes, double Cycle, double Magnitude, double CrossSectExp, double p, double q);
void CutEleWithFun2_3D(vector< vector<double> >& gcoord, vector< vector<int> >& nodes, vector<int> CrossElement, double CircleProperty[4], double Cycle, double Magnitude, int ni, double CrossSectExp, double p, double q);
void CutModel_3D(vector< vector<double> >& gcoord, vector< vector<int> >& nodes, vector< vector<int> >& InnerElementsmain, vector<int>& OuterElementsmain, double CircumR, double CircumRint, double Magnitude, double CrossSectExp, double p, double q)
{
	omp_set_num_threads(8);
	//ģ�ͻ�������
	double Xmax, Xmin, Ymax, Ymin, Zmax, Zmin;
	Xmax = gcoord[0][0], Xmin = gcoord[0][0];  //gcoord.size()
	Ymax = gcoord[0][1], Ymin = gcoord[0][1];
	Zmax = gcoord[0][2], Zmin = gcoord[0][2];
#pragma omp parallel for
	for (int i = 1; i < gcoord.size(); i++)        //�ҳ�Xmax, Xmin
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
	for (int i = 1; i < gcoord.size(); i++)         //�ҳ�Ymax, Ymin
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
	for (int i = 1; i < gcoord.size(); i++)         //�ҳ�Zmax, Zmin
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
	vector<vector<double>> CenterPoints(8, vector<double>(3, 0));
	CenterPoints = { {0,0,Zmax} ,{0,0,Zmax},{0,0,Zmax},{0,0,Zmax},{0,0,Zmax},{0,0,Zmax},{0,0,Zmax},{0,0,Zmax}};
	vector<vector<double>> CirclesProperty(8, vector<double>(4, 0));
	ModelFunction(CenterPoints, CircumR, CirclesProperty);

	//ɸѡ����Ҫ���и�ĵ�Ԫ
	//int** ElementStatus = new int* [nodes.size()];             //nodes����Ϊ������CirclesProperty����Ϊ����
	//for (int i3 = 0; i3 < nodes.size(); i3++)
	//	ElementStatus[i3] = new int[3]();
	vector< vector<int> >ElementStatus(nodes.size(), vector<int>(8, 0));
	CutElement_3D(ElementStatus, CirclesProperty, gcoord, nodes, CircumRint, Magnitude, CrossSectExp, p, q);

	//int iei[8] = { 0 }, oei[8] = { 0 }, cei[8] = { 0 };    //�ֱ�ΪInnerEle��OuterEle��CrossEle��������
	vector<int> iei(8, 0);
	vector<int> oei(8, 0);
	vector<int> cei(8, 0);
	int ieix = 0, oeix = 0, ceix = 0;    //�ֱ�ΪInnerEle��OuterEle��CrossEle����˳��
#pragma omp parallel for
	for (int i = 0; i < 8; i++)  //��ѭ��Ϊ��ȷ��InnerEle��OuterEle��CrossEle���εĴ�С
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
	int ccei = accumulate(cei.begin(), cei.end(),0);
	//int ceit = cei[0] + cei[1] + cei[2];  //CrossElement���������
	//int* CrossElement = new int[accumulate(cei.begin(),cei.end(),0)];
	vector<int> CrossElement;
	//#pragma omp parallel for
	for (int i = 0; i < 8; i++)
	{
		int* InnerEle = new int[iei[i]]();
		int* OuterEle = new int[oei[i]]();
		int* CrossEle = new int[cei[i]]();
		for (int j = 0; j < nodes.size(); j++)
		{
			switch (ElementStatus[j][i])
			{
			case 1:InnerEle[ieix] = j;
				ieix = ieix + 1;
				break;
			case 2:OuterEle[oeix] = j;
				oeix = oeix + 1;
				break;
			case 3:CrossEle[ceix] = j;
				ceix = ceix + 1;
				break;
			}
		}
		for (size_t k1 = 0; k1 < cei[i]; k1++)
		{
			CrossElement.push_back(CrossEle[k1]);
		}
		/*switch (i)
		{
		case 0:
			for (int k1 = 0; k1 < cei[0]; k1++)
			{
				CrossElement[k1] = CrossEle[k1];
			}
			break;
		case 1:
			for (int k2 = 0; k2 < cei[1]; k2++)
			{
				CrossElement[(cei[0] + k2)] = CrossEle[k2];
			}
			break;
		case 2:
			for (int k3 = 0; k3 < cei[2]; k3++)
			{
				CrossElement[(cei[0] + cei[1] + k3)] = CrossEle[k3];
			}
			break;
		case 3:
			for (int k4 = 0; k4 < cei[2]; k4++)
			{
				CrossElement[(cei[0] + cei[1] + k4)] = CrossEle[k4];
			}
			break;
		}*/

		ieix = 0, oeix = 0, ceix = 0;
		delete[]InnerEle;
		delete[]OuterEle;
		delete[]CrossEle;
	}

	//�иԪ
	double CircleProperty[4] = { 0 };
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			CircleProperty[j] = CirclesProperty[i][j];
		}
		//CutEleWithFun(Gcoord, Nodes, CrossElement, CircleProperty, Cycle, Magnitude, i);
		CutEleWithFun2_3D(gcoord, nodes, CrossElement, CircleProperty, CircumRint, Magnitude, i, CrossSectExp, p, q);
	}

	//�ж�ɸѡ֮��Ԫ����λ��
	vector<int> InnerElements;// , OuterElements, CrossElements;
//#pragma omp parallel for
	for (int i = 0; i < 8; i++)  // for i = 1:size(CirclesProperty,1)
	{
		//int** CrossElesStatu = new int* [nodes.size()];             //nodes����Ϊ������CirclesProperty����Ϊ����
		//for (int i3 = 0; i3 < nodes.size(); i3++)
		//	CrossElesStatu[i3] = new int[3]();
		vector< vector<int> >CrossElesStatu(nodes.size(), vector<int>(8, 0));
		CutElement_3D(CrossElesStatu, CirclesProperty, gcoord, nodes, CircumRint, Magnitude, CrossSectExp, p, q);
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
	//��������A,����B��C=setdiff(A,B)��������������A��ȴ��������B�е�Ԫ�أ�����C�в������ظ�Ԫ�أ����Ҵ�С��������
#pragma omp parallel for
	for (int i = 0; i < nodes.size(); i++)
	{
		AllEles3D[i] = i;
	}
//#pragma omp parallel for
//	for (int i = 0; i < nodes.size(); i++)
//	{
//		for (int i1 = 0; i1 < InnerElements.size(); i1++)
//		{
//			if (AllEles3D[i] != InnerElements[i1])
//			{
//				outpd = outpd + 1;
//			}
//		}
//		if (outpd == InnerElements.size())
//		{
//			OuterElementsmain.push_back(AllEles3D[i]);
//		}
//		outpd = 0;
//	}
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
	//int a = 0;
	//delete[]CrossElement;
}
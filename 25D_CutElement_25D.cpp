#include <iostream>
#include <vector>
using namespace std;
void LevSetFunVal_25D(vector< vector<double> >& gcoord, double PlaneProperty[4], vector<double>& phi, double Cycle, double Magnitude, int ni, double CrossSectExp, double p, double q);
void CutElement_25D(vector< vector<int> >& ElementStatus, vector <vector<double>> CirclesProperty, vector< vector<double> >& gcoord, vector< vector<int> >& nodes, double Cycle, double Magnitude, double CrossSectExp, double p, double q)
{
	int NumPlane = CirclesProperty.size();
	int nel = nodes.size();
	//int** ElementStatus = new int* [nel];             //nodes行数为行数，CirclesProperty行数为列数
	//for (int i3 = 0; i3 < nel; i3++)
	//	ElementStatus[i3] = new int[NumPlane]();

	double PlaneProperty[4] = { 0 };     //PlaneProperty为CirclesProperty第i行数据
	//double* phi = new double[gcoord.size()]();
	vector<double> phi(gcoord.size(), 0);
	//double** NodesPhi = new double* [nodes.size()];    //定义nodes
	//for (int i = 0; i < nodes.size(); i++)
	//	NodesPhi[i] = new double[4]();
	vector< vector<double> > NodesPhi(nodes.size(), vector<double>(4, 0));


	//int mab = 0;  //MaxInd数组容量大小
	//int mabx = 0; //MaxInd数组顺序
	//int mib = 0;  //MinInd数组容量大小
	//int mibx = 0;  //MinInd数组顺序
	//int* LocalStatus = new int[nodes.size()]();
	vector<int> LocalStatus(nodes.size(), 0);
	//double* NodeMax = new double[nodes.size()]();
	//double* NodeMin = new double[nodes.size()]();
	vector<double> NodeMax(nodes.size(), 0);
	vector<double> NodeMin(nodes.size(), 0);
	vector<int> MaxInd;    //MaxInd数组存储NodeMax数组小于等于0的项
	vector<int> MinInd;    //MinInd数组存储NodeMin数组大于等于0的项
	for (int i = 0; i < NumPlane; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			PlaneProperty[j] = CirclesProperty[i][j];
		}

		LevSetFunVal_25D(gcoord, PlaneProperty, phi, Cycle, Magnitude, i, CrossSectExp, p, q);

		//NodesPhi = phi(nodes)
		for (int k = 0; k < nodes.size(); k++)
		{
			NodesPhi[k][0] = phi[nodes[k][0]];
			NodesPhi[k][1] = phi[nodes[k][1]];
			NodesPhi[k][2] = phi[nodes[k][2]];
			NodesPhi[k][3] = phi[nodes[k][3]];
		}
		//int* LocalStatus = new int[(Nx - 1) * (Ny - 1) * (Nz - 1) * 5];
		for (int l = 0; l < nodes.size(); l++)
		{
			LocalStatus[l] = 3;
		}
		//double* NodeMax = new double[(Nx - 1) * (Ny - 1) * (Nz - 1) * 5];
		//double* NodeMin = new double[(Nx - 1) * (Ny - 1) * (Nz - 1) * 5];
		for (int i1 = 0; i1 < nodes.size(); i1++)
		{
			NodeMax[i1] = NodesPhi[i1][0];
			NodeMin[i1] = NodesPhi[i1][0];
			for (int i2 = 1; i2 < 4; i2++)
			{
				NodeMax[i1] = (NodeMax[i1] > NodesPhi[i1][i2] ? NodeMax[i1] : NodesPhi[i1][i2]);
				NodeMin[i1] = (NodeMin[i1] < NodesPhi[i1][i2] ? NodeMin[i1] : NodesPhi[i1][i2]);
			}
		}
		for (int i2 = 0; i2 < nodes.size(); i2++)
		{
			if (NodeMax[i2] <= 0) MaxInd.push_back(i2);  //确定MaxInd数组大小
			if (NodeMin[i2] >= 0) MinInd.push_back(i2);  //确定MinInd数组大小
		}
		//int* MaxInd = new int[mab];    //MaxInd数组存储NodeMax数组小于等于0的项
		//int* MinInd = new int[mib];    //MinInd数组存储NodeMin数组大于等于0的项
		//for (int i3 = 0; i3 < nodes.size(); i3++)
		//{
		//	if (NodeMax[i3] <= 0)
		//	{
		//		MaxInd[mabx] = i3;
		//		mabx = mabx + 1;
		//	}
		//	if (NodeMin[i3] >= 0)
		//	{
		//		MinInd[mibx] = i3;
		//		mibx = mibx + 1;
		//	}
		//}
		for (int i4 = 0; i4 < MaxInd.size(); i4++)
		{
			LocalStatus[MaxInd[i4]] = 1;      //erro
		}
		for (int i5 = 0; i5 < MinInd.size(); i5++)
		{
			LocalStatus[MinInd[i5]] = 2;
		}

		for (int i6 = 0; i6 < nodes.size(); i6++)
		{
			ElementStatus[i6][i] = LocalStatus[i6];
		}
		//mab = 0, mib = 0;
		//mabx = 0, mibx = 0;
		//delete[]MaxInd;
		//delete[]MinInd;
		MaxInd.clear();
		MinInd.clear();
	}

}
#include <iostream>
#include <vector>
using namespace std;
void LevSetFunVal_25D1st(vector< vector<float> >& gcoord, float PlaneProperty[4], vector<float>& phi, float Cycle, float Magnitude, int ni, float CrossSectExp, float p, float q);
void CutElement_25D1st(vector< vector<int> >& ElementStatus, float CirclesProperty[3][4], vector< vector<float> >& gcoord, vector< vector<int> >& nodes, float Cycle, float Magnitude, float CrossSectExp, float p, float q)
{
	int NumPlane = 3;
	int nel = nodes.size();
	//int** ElementStatus = new int* [nel];             //nodes行数为行数，CirclesProperty行数为列数
	//for (int i3 = 0; i3 < nel; i3++)
	//	ElementStatus[i3] = new int[NumPlane]();

	float PlaneProperty[4] = { 0 };     //PlaneProperty为CirclesProperty第i行数据
	//float* phi = new float[gcoord.size()]();
	vector<float> phi(gcoord.size(), 0);
	//float** NodesPhi = new float* [nodes.size()];    //定义nodes
	//for (int i = 0; i < nodes.size(); i++)
	//	NodesPhi[i] = new float[4]();
	vector< vector<float> > NodesPhi(nodes.size(), vector<float>(4, 0));


	int mab = 0;  //MaxInd数组容量大小
	int mabx = 0; //MaxInd数组顺序
	int mib = 0;  //MinInd数组容量大小
	int mibx = 0;  //MinInd数组顺序
	//int* LocalStatus = new int[nodes.size()]();
	vector<int> LocalStatus(nodes.size(), 0);
	//float* NodeMax = new float[nodes.size()]();
	//float* NodeMin = new float[nodes.size()]();
	vector<float> NodeMax(nodes.size(), 0);
	vector<float> NodeMin(nodes.size(), 0);
	for (int i = 0; i < NumPlane; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			PlaneProperty[j] = CirclesProperty[i][j];
		}
		LevSetFunVal_25D1st(gcoord, PlaneProperty, phi, Cycle, Magnitude, i, CrossSectExp, p, q);
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
		//float* NodeMax = new float[(Nx - 1) * (Ny - 1) * (Nz - 1) * 5];
		//float* NodeMin = new float[(Nx - 1) * (Ny - 1) * (Nz - 1) * 5];
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
			if (NodeMax[i2] <= 0) mab = mab + 1;  //确定MaxInd数组大小
			if (NodeMin[i2] >= 0) mib = mib + 1;  //确定MinInd数组大小
		}
		int* MaxInd = new int[mab];    //MaxInd数组存储NodeMax数组小于等于0的项
		int* MinInd = new int[mib];    //MinInd数组存储NodeMin数组大于等于0的项
		for (int i3 = 0; i3 < nodes.size(); i3++)
		{
			if (NodeMax[i3] <= 0)
			{
				MaxInd[mabx] = i3;
				mabx = mabx + 1;
			}
			if (NodeMin[i3] >= 0)
			{
				MinInd[mibx] = i3;
				mibx = mibx + 1;
			}
		}
		for (int i4 = 0; i4 < mab; i4++)
		{
			LocalStatus[MaxInd[i4]] = 1;      //erro
		}
		for (int i5 = 0; i5 < mib; i5++)
		{
			LocalStatus[MinInd[i5]] = 2;
		}

		for (int i6 = 0; i6 < nodes.size(); i6++)
		{
			ElementStatus[i6][i] = LocalStatus[i6];
		}
		mab = 0, mib = 0;
		mabx = 0, mibx = 0;
		delete[]MaxInd;
		delete[]MinInd;
	}

	//delete[]phi;          //删除phi数组
	//for (int i = 0; i < nodes.size(); i++)
	//	delete[]NodesPhi[i];
	//delete[]NodesPhi;     //删除NodesPhi数组
	//delete[]LocalStatus;  //删除LocalStatus数组
	//delete[]NodeMax;      //删除NodeMax数组
	//delete[]NodeMin;      //删除NodeMin数组
}
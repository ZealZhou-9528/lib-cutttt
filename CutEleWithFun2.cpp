#include <iostream>
#include <vector>
using namespace std;
void LevSetFunVal2(vector< vector<double> >& gcoord, double PlaneProperty[4], vector<double>& phi, double Cycle, double Magnitude, int ni, double CrossSectExp, double p, double q);
void ReSameRows(int** NewEleNode, vector< vector<int> >& CutEdgNodes, int Mode);
void gAdd2(vector<double>& coordnew, vector< vector<double> >& gcoord, int LineNode[2], double CircleProperty[4], double Cycle, double Magnitude, int ni);
void FindNodeOfEle2(int Num, int LinNode[2], vector< vector<int> >& nodes, vector< vector<double> >& gcoord);
void CutEleWithFun2(vector< vector<double> >& gcoord, vector< vector<int> >& nodes, vector<int> CrossElement, double CircleProperty[4], double Cycle, double Magnitude, int ni, double CrossSectExp, double p, double q)
{
	//double* phi = new double[Nx * Ny * Nz]();
	vector<double> phi(gcoord.size(), 0);
	LevSetFunVal2(gcoord, CircleProperty, phi, Cycle, Magnitude, ni, CrossSectExp, p, q);
	int LocalNode[6][2] = { 0,1,0,2,0,3,1,2,1,3,2,3 };
	int crl = 0;   //CroEleNodes行数
	crl = CrossElement.size();
	//int** CroEleNodes = new int* [crl];           //定义CroEleNodes  496*4
	//for (int i = 0; i < crl; i++)
	//	CroEleNodes[i] = new int[4]();
	//double** CroEleNodesFai = new double* [crl];    //定义CroEleNodes  496*4
	//for (int i = 0; i < crl; i++)
	//	CroEleNodesFai[i] = new double[4]();
	vector< vector<int> > CroEleNodes(crl, vector<int>(4, 0));
	vector< vector<double> > CroEleNodesFai(crl, vector<double>(4, 0));



	for (int i = 0; i < crl; i++)                 //为CroEleNodes赋值
	{
		for (int j = 0; j < 4; j++)
		{
			CroEleNodes[i][j] = nodes[CrossElement[i]][j];
		}
	}
	for (int i = 0; i < crl; i++)              //为CroEleNodesFai赋值
	{
		for (int j = 0; j < 4; j++)
		{
			CroEleNodesFai[i][j] = phi[CroEleNodes[i][j]];
		}
	}

	int LN[2] = { 0 };
	int** EdgeNodes = new int* [crl];       //定义EdgeNodes  496*2
	for (int i = 0; i < crl; i++)
		EdgeNodes[i] = new int[2]();
	double** NodesFai = new double* [crl];    //定义NodesFai   496*2
	for (int i = 0; i < crl; i++)
		NodesFai[i] = new double[2]();
	double* DotValues = new double[crl]();    //定义DotValues  496*1

	int*** AN3d = new int** [6];      //定义AllEdgNodes三维，共6层，每一层存储一个ln循环的数组
	for (int i = 0; i < 6; i++)
	{
		AN3d[i] = new int* [crl];
	}
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < crl; j++)
		{
			AN3d[i][j] = new int[2];
		}
	}

	int DVn[6] = { 0 };  //LocInd数组的大小，值为DotValues数组中小于0的个数
	int DVnx = 0; //LocInd数组的序列
	vector< vector<int> > AllEdgNodes2;
	for (int ln = 0; ln < 6; ln++)
	{
		LN[0] = LocalNode[ln][0];
		LN[1] = LocalNode[ln][1];

		for (int i1 = 0; i1 < crl; i1++)
		{
			EdgeNodes[i1][0] = CroEleNodes[i1][(LN[0])];
			EdgeNodes[i1][1] = CroEleNodes[i1][(LN[1])];

			NodesFai[i1][0] = CroEleNodesFai[i1][(LN[0])];
			NodesFai[i1][1] = CroEleNodesFai[i1][(LN[1])];
		}
		for (int i2 = 0; i2 < crl; i2++)
		{
			DotValues[i2] = NodesFai[i2][0] * NodesFai[i2][1];
		}
		for (int i3 = 0; i3 < crl; i3++)
		{
			if (DotValues[i3] < 0)
			{
				DVn[ln] = DVn[ln] + 1;
			}
		}
		int* LocInd = new int[(DVn[ln])]();    //定义LocInd  DVn*1
		//vector<int> LocInd(DVn[ln], 0);
		for (int i4 = 0; i4 < crl; i4++)
		{
			if (DotValues[i4] < 0)
			{
				LocInd[DVnx] = i4;
				DVnx = DVnx + 1;
			}
		}
		int** EdgNodes = new int* [(DVn[ln])];       //定义EdgNodes  DVn*2
		for (int i = 0; i < DVn[ln]; i++)
			EdgNodes[i] = new int[2]();

		for (int i5 = 0; i5 < DVn[ln]; i5++)
		{
			EdgNodes[i5][0] = EdgeNodes[(LocInd[i5])][0];
			EdgNodes[i5][1] = EdgeNodes[(LocInd[i5])][1];
		}
		for (int i6 = 0; i6 < DVn[ln]; i6++)
		{
			AN3d[ln][i6][0] = EdgNodes[i6][0];
			AN3d[ln][i6][1] = EdgNodes[i6][1];
		}

		delete[]LocInd;
		for (int i = 0; i < (DVn[ln]); i++)
			delete[]EdgNodes[i];
		delete[]EdgNodes;
		//DVn = 0;
		DVnx = 0;
	}
	int AENn = DVn[0] + DVn[1] + DVn[2] + DVn[3] + DVn[4] + DVn[5];
	//int** AllEdgNodes = new int* [AENn];       //定义AllEdgNodes  332*2
	//for (int i = 0; i < AENn; i++)
	//	AllEdgNodes[i] = new int[2]();
	vector< vector<int> > AllEdgNodes(AENn, vector<int>(2, 0));

	for (int i = 0; i < 6; i++)
	{
		switch (i)
		{
		case 0:
			for (int k1 = 0; k1 < DVn[0]; k1++)
			{
				AllEdgNodes[k1][0] = AN3d[i][k1][0];
				AllEdgNodes[k1][1] = AN3d[i][k1][1];
			}
			break;
		case 1:
			for (int k2 = 0; k2 < DVn[1]; k2++)
			{
				AllEdgNodes[(DVn[0] + k2)][0] = AN3d[i][k2][0];
				AllEdgNodes[(DVn[0] + k2)][1] = AN3d[i][k2][1];
			}
			break;
		case 2:
			for (int k3 = 0; k3 < DVn[2]; k3++)
			{
				AllEdgNodes[(DVn[0] + DVn[1] + k3)][0] = AN3d[i][k3][0];
				AllEdgNodes[(DVn[0] + DVn[1] + k3)][1] = AN3d[i][k3][1];
			}
			break;
		case 3:
			for (int k4 = 0; k4 < DVn[3]; k4++)
			{
				AllEdgNodes[(DVn[0] + DVn[1] + DVn[2] + k4)][0] = AN3d[i][k4][0];
				AllEdgNodes[(DVn[0] + DVn[1] + DVn[2] + k4)][1] = AN3d[i][k4][1];
			}
			break;
		case 4:
			for (int k5 = 0; k5 < DVn[4]; k5++)
			{
				AllEdgNodes[(DVn[0] + DVn[1] + DVn[2] + DVn[3] + k5)][0] = AN3d[i][k5][0];
				AllEdgNodes[(DVn[0] + DVn[1] + DVn[2] + DVn[3] + k5)][1] = AN3d[i][k5][1];
			}
			break;
		case 5:
			for (int k6 = 0; k6 < DVn[5]; k6++)
			{
				AllEdgNodes[(DVn[0] + DVn[1] + DVn[2] + DVn[3] + DVn[4] + k6)][0] = AN3d[i][k6][0];
				AllEdgNodes[(DVn[0] + DVn[1] + DVn[2] + DVn[3] + DVn[4] + k6)][1] = AN3d[i][k6][1];
			}
			break;
		}
	}
	//unique

	int AENw = AENn;   //新数组行数，每当有重复行，减一
	for (int i = 0; i < AENn; i++)
	{
		for (int j = i + 1; j < AENn; j++)
		{
			if (AllEdgNodes[i][0] == AllEdgNodes[j][0] && AllEdgNodes[i][1] == AllEdgNodes[j][1])
			{
				AllEdgNodes[j][0] = -1;// , AEN[j][1] = -1;
				if (AllEdgNodes[i][0] != -1)
				{
					AENw = AENw - 1;
				}
			}
		}
	}
	int** AENnew = new int* [AENw];       //定义AENnew  123*2
	for (int i = 0; i < AENw; i++)
		AENnew[i] = new int[2]();
	int AENwx = 0;
	for (int i = 0; i < AENn; i++)
	{
		if (AllEdgNodes[i][0] != -1)
		{
			AENnew[AENwx][0] = AllEdgNodes[i][0];
			AENnew[AENwx][1] = AllEdgNodes[i][1];
			AENwx = AENwx + 1;
		}
	}
	for (int i = 0; i < AENw - 1; ++i)               //对第一列排序
		for (int j = 0; j < AENw - 1 - i; ++j)
			if (AENnew[j][0] > AENnew[j + 1][0])
			{
				swap(AENnew[j][0], AENnew[j + 1][0]);
				swap(AENnew[j][1], AENnew[j + 1][1]);
			}
	for (int i = 0; i < AENw - 1; ++i)               //对第二列排序  
		for (int j = 0; j < AENw - 1 - i; ++j)
			if (AENnew[j][0] == AENnew[j + 1][0])
			{
				if (AENnew[j][1] > AENnew[j + 1][1])
				{
					swap(AENnew[j][0], AENnew[j + 1][0]);
					swap(AENnew[j][1], AENnew[j + 1][1]);
				}
			}
	//unique end
	//CutEdgNodes = ReSameRows(AllEdgNodes,2);   % 删除有重复的切割边
	int CENn = 0;   //用来记录CutEdgNodes经过ReSameRows函数之后的数值
	//int** CutEdgNodes = new int* [AENw];       //定义AENnew  123*2
	//for (int i = 0; i < AENw; i++)
	//	CutEdgNodes[i] = new int[2]();
	vector< vector<int> > CutEdgNodes;
	ReSameRows(AENnew, CutEdgNodes, 2);
	CENn = CutEdgNodes.size();
	int LineNode[2];
	//double coord[3];
	//int** gcoordnew = new int* [CENn+ Nx * Ny * Nz];       //定义AENnew  123*2
	//for (int i = 0; i < (CENn + Nx * Ny * Nz); i++)
	//	gcoordnew[i] = new int[3]();
	//for (int i = 0; i < Nx * Ny * Nz; i++)
	//{
	//	gcoordnew[i][0] = gcoord[i][0], gcoordnew[i][1] = gcoord[i][1], gcoordnew[i][2] = gcoord[i][2];
	//}
	//for aen = 1:size(CutEdgNodes,1)
	//vector<int> coordnew;
	vector<double> coordnew(3);
	for (int aen = 0; aen < CENn; aen++)
	{
		LineNode[0] = CutEdgNodes[aen][0];   //LineNode = CutEdgNodes(aen,:);
		LineNode[1] = CutEdgNodes[aen][1];
		gAdd2(coordnew, gcoord, LineNode, CircleProperty, Cycle, Magnitude, ni);
		//gcoord = [gcoord;coord]; 
		//gcoordnew[Nx * Ny * Nz + aen][0] = coord[0];
		//gcoordnew[Nx * Ny * Nz + aen][1] = coord[1];
		//gcoordnew[Nx * Ny * Nz + aen][2] = coord[2];
		gcoord.push_back(coordnew);
		int NodeNum = gcoord.size() - 1;
		FindNodeOfEle2(NodeNum, LineNode, nodes, gcoord);
	}

	for (int i = 0; i < AENw; i++)   //删除AENnew数组
		delete[]AENnew[i];
	delete[]AENnew;
	for (int x = 0; x < 6; x++)      //删除AN3d数组
	{
		for (int y = 0; y < crl; y++)
		{
			delete[] AN3d[x][y];
		}
	}
	for (int x = 0; x < 6; x++)
	{
		delete[] AN3d[x];
	}
	delete[] AN3d;
}
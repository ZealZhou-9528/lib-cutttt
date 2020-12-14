// m-2Dcut.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
using namespace std;
void ModelGenerationCUBE(double SideLength, int CutNum, int nn,int NLeng, int Nx,int Ny,int Nz, vector< vector<double> >&gcoord, vector< vector<int> >&nodes,int wmth);
//void ModelGenerationCUBE_da(double SideLength, int CutNum, int nn, int NLeng, int Nx, int Ny, int Nz, double** gcoord, double** nodes, int wmth);
void CutModel(vector< vector<double> >&gcoord, vector< vector<int> >&nodes, vector< vector<int> >&InnerElementsmain, vector<int>&OuterElementsmain,double CircumR, double CircumRint, double Magnitude, double CrossSectExp, double p, double q);
void CutModel2st(vector< vector<double> >& gcoord, vector< vector<int> >& nodes, vector< vector<int> >& InnerElementsmain, vector<int>& OuterElementsmain, double CircumR, double CircumRint, double Magnitude, double CrossSectExp, double p, double q);
void FEXMLoutput(double index_xyz, vector< vector<double> > gcoord, vector< vector<int> > nodes, vector<int> FiberElement, string Filename, int filenumber);
void MianModuli(vector< vector<double> >& gcoord, vector< vector<int> >& nodes, vector< vector<int> >& FiberEle, vector<int>& Interstitial, double Magnitude, int Curve);
void CutModel_3D(vector< vector<double> >& gcoord, vector< vector<int> >& nodes, vector< vector<int> >& InnerElementsmain, vector<int>& OuterElementsmain, double CircumR, double CircumRint, double Magnitude, double CrossSectExp, double p, double q);
void CutModel_25D(vector< vector<double> >& gcoord, vector< vector<int> >& nodes, vector< vector<int> >& InnerElementsmain, vector<int>& OuterElementsmain, double CircumR, double CircumRint, double Magnitude, double CrossSectExp, double p, double q);
void CutModel2st_25D(vector< vector<double> >& gcoord, vector< vector<int> >& nodes, vector< vector<int> >& InnerElementsmain, vector<int>& OuterElementsmain, double CircumR, double CircumRint, double Magnitude, double CrossSectExp, double p, double q);
int main_mcut()
{
	omp_set_num_threads(8);
	int CutNum, nn, NLeng, Nx, Ny, Nz;
	CutNum = 10;              //切割次数
	double Magnitude = 1;     //周期幅度
	double BasicR = 1;        //纤维半径
	double Cycle = 10;        //纤维周期长度
	int Curve = 1;
	int wmth = 0;             //编织方式   0为1D，1为2D，2为2.5D，3为3D
	nn = CutNum + 1;
	double SideLength = 10;
	//参数化部分//
	double CrossSectExp = 2;
	double p = 1;//0.03413
	double q = 1;//0.2
	///////////////////////////////
   ///设定xyz的比例（晶格大小）///
	double index_xyz = 1;// 0.1;
	///////////////////////////////
	NLeng = nn;
	Nx = NLeng;
	Ny = NLeng;
	Nz = NLeng;
	/*if (wmth == 1)
	{
		SideLength = 10;
	}*/
	if (wmth == 2)
	{
		SideLength = 10 * 0.672;
	}
	switch (wmth)
	{
	    case(0):
		    Nz = 0.5 * (NLeng - 1) + 1;
		break;
		case(1):
			Nz = 0.5 * (NLeng - 1) + 1;
			break;
		case(2):
			Magnitude = 0.9;     //周期幅度
			BasicR = 0.2;        //纤维半径
			Cycle = 6.72;        //纤维周期长度
			Ny = ceil(NLeng * (3.6 / 6.72)) + 1;
			Nz = ceil(NLeng * (4.05 / 6.72)) + 1;
		break;
		case(3):
			Nz = NLeng;
		break;
	}

	//Nz = 0.5 * (NLeng - 1) + 1;

	//int row = 6, col = 5;
	vector< vector<double> > gcoord((Nx * Ny * Nz), vector<double>(3, 0));
	//double ** da_gcoord = new double* [(Nx * Ny * Nz)];    //注意，int*[10]表示一个有10个元素的指针数组
	//for (int i = 0; i < (Nx * Ny * Nz); ++i)
	//{
	//	//double** da_gcoord = new double* [(Nx * Ny * Nz)];
	//	da_gcoord[i] = new double[3]();
	//}
	vector< vector<int> > nodes(((Nx - 1) * (Ny - 1) * (Nz - 1) * 5), vector<int>(4, 0));
	//double** da_nodes = new double* [((Nx - 1) * (Ny - 1) * (Nz - 1) * 5)];    //注意，int*[10]表示一个有10个元素的指针数组
	//for (int i = 0; i < ((Nx - 1) * (Ny - 1) * (Nz - 1) * 5); ++i)
	//{
	//	da_nodes[i] = new double[4]();
	//}

	ModelGenerationCUBE(SideLength, CutNum, nn, NLeng, Nx, Ny, Nz, gcoord, nodes, wmth);
	//ModelGenerationCUBE_da(SideLength, CutNum, nn, NLeng, Nx, Ny, Nz, da_gcoord, da_nodes, wmth);


	vector< vector<int> > InnerElementsmain;
	InnerElementsmain.resize(3);
	vector< vector<int> > InnerElementsmain2st;
	InnerElementsmain2st.resize(3);
	vector<int> OuterElementsmain;
	vector< vector<int> > FiberEle;
	FiberEle.resize(6);
	switch (wmth)
	{
	    case(0):
		    CutModel(gcoord, nodes, InnerElementsmain, OuterElementsmain, BasicR, Cycle, Magnitude, CrossSectExp, p, q);
		break;
	    case(1):   
			CutModel(gcoord, nodes, InnerElementsmain, OuterElementsmain, BasicR, Cycle, Magnitude, CrossSectExp, p, q);
			CutModel2st(gcoord, nodes, InnerElementsmain2st, OuterElementsmain, BasicR, Cycle, Magnitude, CrossSectExp, p, q);
		break;
		case(2):
			InnerElementsmain.resize(12);
			InnerElementsmain2st.resize(12);
			CutModel_25D(gcoord, nodes, InnerElementsmain, OuterElementsmain, BasicR, Cycle, Magnitude, CrossSectExp, p, q);
			CutModel2st_25D(gcoord, nodes, InnerElementsmain2st, OuterElementsmain, BasicR, Cycle, Magnitude, CrossSectExp, p, q);
			break;
		case(3):
			InnerElementsmain.resize(8);
			CutModel_3D(gcoord, nodes, InnerElementsmain, OuterElementsmain, BasicR, Cycle, Magnitude, CrossSectExp, p, q);
			break;
	}
	//CutModel(gcoord, nodes, InnerElementsmain, OuterElementsmain,BasicR, Cycle, Magnitude, CrossSectExp, p, q);
	//CutModel2st(gcoord, nodes, InnerElementsmain2st, OuterElementsmain, BasicR, Cycle, Magnitude, CrossSectExp, p, q);
	vector<int> AA;
	vector<int> FiberElement;
	if (wmth == 0)
	{
		vector<int> FiberElement1;
		//vector<int> AA;
		for (size_t i = 0; i < 3; i++)
		{
			//AA=cell2mat(InnerElements(1,i));
			for (size_t j = 0; j < InnerElementsmain[i].size(); j++)
			{
				AA.push_back(InnerElementsmain[i][j]);
			}
			for (size_t k = 0; k < AA.size(); k++)
			{
				FiberElement1.push_back(AA[k]);
			}
			AA.clear();
		}
		string FEFilename1 = "m-2D-data/1D-FEXML1-1D-";
		int FEfilenumber1 = 1;
		FEXMLoutput(index_xyz, gcoord, nodes, FiberElement1, FEFilename1, FEfilenumber1);
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < InnerElementsmain[i].size(); j++)
			{
				FiberEle[i].push_back(InnerElementsmain[i][j]);
			}
		}
		//vector<int> FiberElement;
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < FiberEle[i].size(); j++)
			{
				FiberElement.push_back(FiberEle[i][j]);
			}
		}
	}
	else if (wmth==1)
	{
		vector<int> FiberElement1;
		vector<int> FiberElement2;
		//vector<int> AA;
		for (size_t i = 0; i < 3; i++)
		{
			//AA=cell2mat(InnerElements(1,i));
			for (size_t j = 0; j < InnerElementsmain[i].size(); j++)
			{
				AA.push_back(InnerElementsmain[i][j]);
			}
			for (size_t k = 0; k < AA.size(); k++)
			{
				FiberElement1.push_back(AA[k]);
			}
			AA.clear();
		}

		for (size_t i = 0; i < 3; i++)
		{
			//AA=cell2mat(InnerElements2st(1,i));
			for (size_t j = 0; j < InnerElementsmain2st[i].size(); j++)
			{
				AA.push_back(InnerElementsmain2st[i][j]);
			}
			for (size_t k = 0; k < AA.size(); k++)
			{
				FiberElement2.push_back(AA[k]);
			}
			AA.clear();
		}
		string FEFilename1 = "m-2D-data/2D-FEXML1-2D-";
		int FEfilenumber1 = 1;
		FEXMLoutput(index_xyz, gcoord, nodes, FiberElement1, FEFilename1, FEfilenumber1);
		string FEFilename2 = "m-2D-data/2D-FEXML2-2D-";
		int FEfilenumber2 = 1;
		FEXMLoutput(index_xyz, gcoord, nodes, FiberElement2, FEFilename2, FEfilenumber2);
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < InnerElementsmain[i].size(); j++)
			{
				FiberEle[i].push_back(InnerElementsmain[i][j]);
			}
		}
		for (size_t i = 0; i < 3; i++)
		{
			for (int j = 0; j < InnerElementsmain2st[i].size(); j++)
			{
				FiberEle[i + 3].push_back(InnerElementsmain2st[i][j]);
			}
		}
		//vector<int> FiberElement;
		for (size_t i = 0; i < 6; i++)
		{
			for (size_t j = 0; j < FiberEle[i].size(); j++)
			{
				FiberElement.push_back(FiberEle[i][j]);
			}
		}
	}
	else if (wmth == 2)
	{
		FiberEle.resize(24);
		vector<int> FiberElement1;
		vector<int> FiberElement2;
		//vector<int> AA;
		for (size_t i = 0; i < 12; i++)
		{
			//AA=cell2mat(InnerElements(1,i));
			for (size_t j = 0; j < InnerElementsmain[i].size(); j++)
			{
				AA.push_back(InnerElementsmain[i][j]);
			}
			for (size_t k = 0; k < AA.size(); k++)
			{
				FiberElement1.push_back(AA[k]);
			}
			AA.clear();
		}

		for (size_t i = 0; i < 12; i++)
		{
			//AA=cell2mat(InnerElements2st(1,i));
			for (size_t j = 0; j < InnerElementsmain2st[i].size(); j++)
			{
				AA.push_back(InnerElementsmain2st[i][j]);
			}
			for (size_t k = 0; k < AA.size(); k++)
			{
				FiberElement2.push_back(AA[k]);
			}
			AA.clear();
		}
		string FEFilename1 = "m-2D-data/2.5D-FEXML1-2.5D-";
		int FEfilenumber1 = 1;
		FEXMLoutput(index_xyz, gcoord, nodes, FiberElement1, FEFilename1, FEfilenumber1);
		string FEFilename2 = "m-2D-data/2.5D-FEXML2-2.5D-";
		int FEfilenumber2 = 1;
		FEXMLoutput(index_xyz, gcoord, nodes, FiberElement2, FEFilename2, FEfilenumber2);
		for (size_t i = 0; i < 12; i++)
		{
			for (size_t j = 0; j < InnerElementsmain[i].size(); j++)
			{
				FiberEle[i].push_back(InnerElementsmain[i][j]);
			}
		}
		for (size_t i = 0; i < 12; i++)
		{
			for (int j = 0; j < InnerElementsmain2st[i].size(); j++)
			{
				FiberEle[i + 12].push_back(InnerElementsmain2st[i][j]);
			}
		}
		//vector<int> FiberElement;
		for (size_t i = 0; i < 24; i++)
		{
			for (size_t j = 0; j < FiberEle[i].size(); j++)
			{
				FiberElement.push_back(FiberEle[i][j]);
			}
		}
	}
	//vector<int> FiberElement1;
	//vector<int> FiberElement2;
	////vector<int> AA;
	//for (size_t i = 0; i < 3; i++)
	//{
	//	//AA=cell2mat(InnerElements(1,i));
	//	for (size_t j = 0; j < InnerElementsmain[i].size(); j++)
	//	{
	//		AA.push_back(InnerElementsmain[i][j]);
	//	}
	//	for (size_t k = 0; k < AA.size(); k++)
	//	{
	//		FiberElement1.push_back(AA[k]);
	//	}
	//	AA.clear();
	//}

	//for (size_t i = 0; i < 3; i++)
	//{
	//	//AA=cell2mat(InnerElements2st(1,i));
	//	for (size_t j = 0; j < InnerElementsmain2st[i].size(); j++)
	//	{
	//		AA.push_back(InnerElementsmain2st[i][j]);
	//	}
	//	for (size_t k = 0; k < AA.size(); k++)
	//	{
	//		FiberElement2.push_back(AA[k]);
	//	}
	//	AA.clear();
	//}

	//FiberEle = [InnerElements InnerElements2st];
	//if (wmth == 0)
	//{
	//	for (size_t i = 0; i < 3; i++)
	//	{
	//		for (size_t j = 0; j < InnerElementsmain[i].size(); j++)
	//		{
	//			FiberEle[i].push_back(InnerElementsmain[i][j]);
	//		}
	//	}
	//	for (size_t i = 0; i < 3; i++)
	//	{
	//		for (int j = 0; j < InnerElementsmain2st[i].size(); j++)
	//		{
	//			FiberEle[i + 3].push_back(InnerElementsmain2st[i][j]);
	//		}
	//	}
	//	//vector<int> FiberElement;
	//	for (size_t i = 0; i < 6; i++)
	//	{
	//		for (size_t j = 0; j < FiberEle[i].size(); j++)
	//		{
	//			FiberElement.push_back(FiberEle[i][j]);
	//		}
	//	}
	//}
	else if (wmth == 3)
	{
		FiberEle.resize(8);
		for (size_t i = 0; i < FiberEle.size(); i++)
		{
			for (size_t j = 0; j < InnerElementsmain[i].size(); j++)
			{
				FiberEle[i].push_back(InnerElementsmain[i][j]);
			}
		}
		for (size_t i = 0; i < FiberEle.size(); i++)
		{
			for (size_t j = 0; j < FiberEle[i].size(); j++)
			{
				FiberElement.push_back(FiberEle[i][j]);
			}
		}
	}
	

	vector<int> AllEles(nodes.size(),0);
	vector<int> Interstitial;
#pragma omp parallel for
	for (int i = 0; i < nodes.size(); i++)
	{
		AllEles[i] = i;
	}
	int outpd = 0;
	for (size_t i = 0; i < AllEles.size(); i++)
	{
		for (size_t i1 = 0; i1 < FiberElement.size(); i1++)
		{
			if (AllEles[i] != FiberElement[i1])
			{
				outpd = outpd + 1;
			}
		}
		if (outpd == FiberElement.size())
		{
			Interstitial.push_back(AllEles[i]);
		}
		outpd = 0;
	}
	sort(Interstitial.begin(), Interstitial.end());
	Interstitial.erase(unique(Interstitial.begin(), Interstitial.end()), Interstitial.end());
	vector<int> AllEles3D(nodes.size(),0);
	for (size_t i = 0; i < nodes.size(); i++)
	{
		AllEles3D[i] = i;
	}
	/////////////////////////////
////加入改变单元总数的函数///
	int total_x = 1;
	int total_y = 1;
	int total_z = 2;
	int remain_x = 0;
	int remain_y = 0;
	int remain_z = 0;
	int remain_zxy = 0;
	vector< vector<double> > total_gcoord((total_x * total_y * total_z * gcoord.size()), vector<double>(3, 0));
	vector< vector<int> > total_nodes((total_x * total_y * total_z * nodes.size()), vector<int>(4, 0));
	for (size_t i = 0,j=0; i < total_x * total_y * total_z; i++,j=j+ total_z)
	{
		remain_x = i % total_x;
		remain_y = i / total_x - (i / (total_x * total_y))*total_y;// *(1 + i / (total_x * total_y)));
		remain_z = i / (total_x * total_y);
		//remain_y = i / total_x - i / (total_x * total_y);
		remain_zxy = 0;
		if (wmth==0)
		{
			for (size_t it = 0; it < gcoord.size(); it++)
			{
				total_gcoord[it + i * gcoord.size()][0] = gcoord[it][0] + remain_x * SideLength;
				total_gcoord[it + i * gcoord.size()][1] = gcoord[it][1] + remain_y * SideLength;
				total_gcoord[it + i * gcoord.size()][2] = gcoord[it][2] + remain_z * 0.5 * SideLength;
			}
		}
		if (wmth == 1)
		{
			for (size_t it = 0; it < gcoord.size(); it++)
			{
				total_gcoord[it + i * gcoord.size()][0] = gcoord[it][0] + remain_x * SideLength;
				total_gcoord[it + i * gcoord.size()][1] = gcoord[it][1] + remain_y * SideLength;
				total_gcoord[it + i * gcoord.size()][2] = gcoord[it][2] + remain_z * 0.5 * SideLength;
			}
		}
		if (wmth == 2)
		{
			for (size_t it = 0; it < gcoord.size(); it++)
			{
				total_gcoord[it + i * gcoord.size()][0] = gcoord[it][0] + remain_x * SideLength;
				total_gcoord[it + i * gcoord.size()][1] = gcoord[it][1] + remain_y * SideLength;
				total_gcoord[it + i * gcoord.size()][2] = gcoord[it][2] + remain_z * SideLength;
			}
		}
		if (wmth == 3)
		{
			for (size_t it = 0; it < gcoord.size(); it++)
			{
				total_gcoord[it + i * gcoord.size()][0] = gcoord[it][0] + remain_x * SideLength;
				total_gcoord[it + i * gcoord.size()][1] = gcoord[it][1] + remain_y * SideLength;
				total_gcoord[it + i * gcoord.size()][2] = gcoord[it][2] + remain_z * SideLength;
			}
		}
		/*for (size_t it = 0; it < gcoord.size(); it++)
		{
			total_gcoord[it + i * gcoord.size()][0] = gcoord[it][0] + remain_x * SideLength;
			total_gcoord[it + i * gcoord.size()][1] = gcoord[it][1] + remain_y * SideLength;
			total_gcoord[it + i * gcoord.size()][2] = gcoord[it][2] + remain_z * 0.5 * SideLength;
		}*/
	/*	for (size_t it = 0; it < gcoord.size(); it++)
		{
			total_gcoord[it + i * gcoord.size()][1] = gcoord[it][1] + remain_y * SideLength;
		}
		int aaaa = 0;*/
	}
	/*for (size_t i = 1; i < total_z; i++)
	{
		for (size_t it = 0; it < total_x * total_y * gcoord.size(); it++)
		{
			total_gcoord[it + i * total_x * total_y * gcoord.size()][2] = total_gcoord[it][2] + i * 0.5 * SideLength;
		}
	}*/

	for (int i = 0; i < total_x * total_y * total_z; i++)
	{
		for (int jj = 0; jj < nodes.size(); jj++)
		{
			total_nodes[i * nodes.size() + jj][0] = nodes[jj][0] + i * gcoord.size();
			total_nodes[i * nodes.size() + jj][1] = nodes[jj][1] + i * gcoord.size();
			total_nodes[i * nodes.size() + jj][2] = nodes[jj][2] + i * gcoord.size();
			total_nodes[i * nodes.size() + jj][3] = nodes[jj][3] + i * gcoord.size();
		}

	}

	int size_inter = Interstitial.size() * total_x * total_y * total_z;
	vector<int> total_Interstitial(size_inter, 0);
	for (int i = 0; i < total_x * total_y * total_z; i++)
	{
		//for (int j = 0; j < total_y; j++)
		//{
		for (int jj = 0; jj < Interstitial.size(); jj++)
		{
			total_Interstitial[i * Interstitial.size() + jj] = Interstitial[jj] + i * nodes.size();
		}
		//}
	}
	//
	int size_FEL = FiberElement.size() * total_x * total_y * total_z;
	vector<int> total_FiberElement(size_FEL, 0);
	for (int i = 0; i < total_x * total_y * total_z; i++)
	{
		for (int jj = 0; jj < FiberElement.size(); jj++)
		{
			total_FiberElement[i * FiberElement.size() + jj] = FiberElement[jj] + i * nodes.size();
		}
	}
	/////////////////////////////
	//string FEFilename1 = "m-2D-data/FEXML1-";
	//int FEfilenumber1 = 1;
 //   FEXMLoutput(index_xyz, gcoord, nodes, FiberElement1, FEFilename1, FEfilenumber1);
	//string FEFilename2 = "m-2D-data/FEXML2-";
	//int FEfilenumber2 = 1;
	//FEXMLoutput(index_xyz, gcoord, nodes, FiberElement2, FEFilename2, FEfilenumber2);
	if (wmth == 0)//    1D
	{
		string FEFilename = "m-2D-data/1D-FEXML-1D-";
		int FEfilenumber = 1;
		FEXMLoutput(index_xyz, gcoord, nodes, FiberElement, FEFilename, FEfilenumber);

		string IEFilename = "m-2D-data/1D-IEXML-1D-";
		int IEfilenumber = 1;
		FEXMLoutput(index_xyz, gcoord, nodes, Interstitial, IEFilename, IEfilenumber);

		string XYZIIIFilename = "m-2D-data/1D-XYZIIIXML-1D-";
		int XYZIIIfilenumber = 1;
		FEXMLoutput(index_xyz, total_gcoord, total_nodes, total_FiberElement, XYZIIIFilename, XYZIIIfilenumber);

		string XYZFilename = "m-2D-data/1D-XYZXML-1D-";
		int XYZfilenumber = 1;
		FEXMLoutput(index_xyz, total_gcoord, total_nodes, total_Interstitial, XYZFilename, XYZfilenumber);
	}
	if (wmth == 1)//    2D
	{
		string FEFilename = "m-2D-data/2D-FEXML-2D-";
		int FEfilenumber = 1;
		FEXMLoutput(index_xyz, gcoord, nodes, FiberElement, FEFilename, FEfilenumber);

		string IEFilename = "m-2D-data/2D-IEXML-2D-";
		int IEfilenumber = 1;
		FEXMLoutput(index_xyz, gcoord, nodes, Interstitial, IEFilename, IEfilenumber);

		string XYZIIIFilename = "m-2D-data/2D-XYZIIIXML-2D-";
		int XYZIIIfilenumber = 1;
		FEXMLoutput(index_xyz, total_gcoord, total_nodes, total_FiberElement, XYZIIIFilename, XYZIIIfilenumber);

		string XYZFilename = "m-2D-data/2D-XYZXML-2D-";
		int XYZfilenumber = 1;
		FEXMLoutput(index_xyz, total_gcoord, total_nodes, total_Interstitial, XYZFilename, XYZfilenumber);
	}
	if (wmth == 2)//    2.5D
	{
		string FEFilename = "m-2D-data/2.5D-FEXML-2.5D-";
		int FEfilenumber = 1;
		FEXMLoutput(index_xyz, gcoord, nodes, FiberElement, FEFilename, FEfilenumber);

		string IEFilename = "m-2D-data/2.5D-IEXML-2.5D-";
		int IEfilenumber = 1;
		FEXMLoutput(index_xyz, gcoord, nodes, Interstitial, IEFilename, IEfilenumber);

		string XYZIIIFilename = "m-2D-data/2.5D-XYZIIIXML-2.5D-";
		int XYZIIIfilenumber = 1;
		FEXMLoutput(index_xyz, total_gcoord, total_nodes, total_FiberElement, XYZIIIFilename, XYZIIIfilenumber);

		string XYZFilename = "m-2D-data/2.5D-XYZXML-2.5D-";
		int XYZfilenumber = 1;
		FEXMLoutput(index_xyz, total_gcoord, total_nodes, total_Interstitial, XYZFilename, XYZfilenumber);
	}
	if (wmth == 3)//    3D
	{
		string FEFilename = "m-2D-data/3D-FEXML-3D-";
		int FEfilenumber = 1;
		FEXMLoutput(index_xyz, gcoord, nodes, FiberElement, FEFilename, FEfilenumber);

		string IEFilename = "m-2D-data/3D-IEXML-3D-";
		int IEfilenumber = 1;
		FEXMLoutput(index_xyz, gcoord, nodes, Interstitial, IEFilename, IEfilenumber);

		string XYZIIIFilename = "m-2D-data/3D-XYZIIIXML-3D-";
		int XYZIIIfilenumber = 1;
		FEXMLoutput(index_xyz, total_gcoord, total_nodes, total_FiberElement, XYZIIIFilename, XYZIIIfilenumber);

		string XYZFilename = "m-2D-data/3D-XYZXML-3D-";
		int XYZfilenumber = 1;
		FEXMLoutput(index_xyz, total_gcoord, total_nodes, total_Interstitial, XYZFilename, XYZfilenumber);
	}
	//string FEFilename = "m-2D-data/FEXML-";
	//int FEfilenumber = 1;
	//FEXMLoutput(index_xyz, gcoord,nodes,FiberElement,FEFilename,FEfilenumber);
	//string IEFilename = "m-2D-data/IEXML-";
	//int IEfilenumber = 1;
	//FEXMLoutput(index_xyz, gcoord, nodes, Interstitial, IEFilename, IEfilenumber);

	//string XYZIIIFilename = "m-2D-data/XYZIIIXML-";
	//int XYZIIIfilenumber = 1;
	//FEXMLoutput(index_xyz, total_gcoord, total_nodes, total_FiberElement, XYZIIIFilename, XYZIIIfilenumber);
	//string XYZFilename = "m-2D-data/XYZXML-";
	//int XYZfilenumber = 1;
	//FEXMLoutput(index_xyz, total_gcoord, total_nodes, total_Interstitial, XYZFilename, XYZfilenumber);
	int zz = 0;
	///////////////////////////////////////////////////////////////////
	////有效模量计算////
	///////////////////////////////////////////////////////////////////
	MianModuli(gcoord, nodes, FiberEle, Interstitial, Magnitude, Curve);
	//
	//for (size_t i = 0; i < gcoord.size(); i++)
	//{
	//	for (size_t j = 0; j < 3; j++)
	//	{
	//		cout << gcoord[i][j] << ' ';
	//	}
	//	cout << endl;
	//}
	//
	return 0;






	//for (int i = 0; i < (Nx * Ny * Nz); i++)                        //删除gcoord数组
	//	delete[]gcoord[i];
	//delete[]gcoord;

	//for (int i = 0; i < ((Nx - 1) * (Ny - 1) * (Nz - 1) * 5); i++)  //删除nodes数组
	//	delete[]nodes[i];
	//delete[]nodes;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
//switch (index_xy)
//{
//case 0:
//	for (int it = 0; it < gcoord.size(); it++)
//	{
//		total_gcoord[it + i * gcoord.size()][0] = gcoord[it][0];
//	}
//	break;
//case 0:
//	for (int it = 0; it < gcoord.size(); it++)
//	{
//		total_gcoord[it + i * gcoord.size()][0] = gcoord[it][0];
//	}
//	break;
//case 0:
//	for (int it = 0; it < gcoord.size(); it++)
//	{
//		total_gcoord[it + i * gcoord.size()][0] = gcoord[it][0];
//	}
//	break;
//}

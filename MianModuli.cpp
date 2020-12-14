#define EIGEN_USE_MKL_ALL
//#define EIGEN_VECTORIZE_SSE4_2
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <Eigen/Dense>
#include <Eigen/Core>
//#include <omp.h>
using namespace Eigen;
using namespace std;
void FeCofBC_Rotation_old_C4(vector<double>& Tot_Bond_value, double &TotalVolume,vector<double>& dofFace, vector<double>& dofVaule, vector< vector<double> >& gcoord, int iopt);
void Boundarymatrix(vector<vector<double>>& matix_e, double TotalVolume, vector<double>& Tot_Bond_value, vector< vector<double> >& gcoord, int iopt);
void BCcondPeriodic(vector<vector<double>>& Tab_dep, vector< vector<double> >& gcoord, vector<vector<double>>& matix_e, int Mode);
void feglqd4(vector<vector<double>>& point, vector<double>& weight, int N);
vector<vector<double>> fematiso(int iopt, vector<double> elprop);
vector<vector<double>> Trans_Matrix(vector<double> xcoord, vector<double> ycoord, vector<double> zcoord, double Magnitude, int N);
vector<vector<double>> vectors_multiply(vector<vector<double>> a, vector<vector<double>> b);//矩阵乘法
vector<vector<double>> vectors_Transpose(vector<vector<double>> a);//转置
void feisos8(vector<double>& shapes4, vector<double>& dhdrs4, vector<double>& dhdss4, vector<double>& dhdts4, int nnel, vector<vector<double>> Lpoint);
vector<vector<double>> fejacob3(int nnel, vector<double> dhdr, vector<double> dhds, vector<double> dhdt, vector<double> xcoord, vector<double> ycoord, vector<double> zcoord);
double vector_det(vector< vector<double> > matrix);//行列式
vector<vector<double>> vectors_inversion(vector<vector<double>> a);//矩阵的逆
void federiv3(vector<double>& dhdx, vector<double>& dhdy, vector<double>& dhdz, int nnel, vector<double> dhdr, vector<double> dhds, vector<double> dhdt, vector<vector<double>> invjacob);
double ComputeVolume4V2(vector<double> xcoord, vector<double> ycoord, vector<double> zcoord);
vector<vector<double>> fekine3d(int nnel, vector<double> dhdx, vector<double> dhdy, vector<double> dhdz);
vector<vector<double>> vectors_2plus(vector<vector<double>> v1, vector<vector<double>> v2);//二阶矩阵加法
vector<vector<double>> vectors_multiply_2number(vector<vector<double>> a, double b);//二阶矩阵数乘
vector<vector<double>> vectors_1combine(vector<double> v1, vector<double> v2);//合并一维矩阵
vector<vector<double>> vector_sparse(vector<int> row, vector<int> col, vector<double>val, int m, int n);//稀疏矩阵
vector<vector<double>> ternary_sparse(vector<int> row, vector<int> col, vector<double>val, int m, int n);//三元稀疏矩阵
//void BCimposeT3(vector<vector<double>>& Kr, vector<vector<double>>& Fr, vector<int>& listeddl, vector<double>& T, vector<vector<double>> K, vector<double> F, vector<vector<double>> Tab_dep);
double* BCimposeT3(vector<vector<double>>& Kr, vector<int>& listeddl, vector<double>& T, vector<vector<double>> K, vector<double> F, vector<vector<double>> Tab_dep);
void MKL_inv(float* pDst, float* pSrc, int dim);//MKL求逆
vector<vector<double>> vectors_reshape(vector<double> Resdisp, int m, int n);//reshape
vector<int> feeldof(vector<int> nd, int nnel, int ndof);
void MianModuli(vector< vector<double> > &gcoord, vector< vector<int> > &nodes, vector< vector<int> > &FiberEle, vector<int> &Interstitial, double Magnitude, int Curve)
{
	vector<int> AllEles3D;
	for (size_t i = 0; i < nodes.size(); i++)
	{
		AllEles3D.push_back(i);
	}
	double Val_D11, Val_D12, Val_D22, Val_D13, Val_D23, Val_D33;
	double Val_D16, Val_D26, Val_D36, Val_D46, Val_D56, Val_D66;
	double Val_D15, Val_D25, Val_D35, Val_D45, Val_D55;
	double Val_D14, Val_D24, Val_D34, Val_D44;
	for (size_t Mode = 1; Mode < 7; Mode++)
	{
		int MODE = Mode;
		int nnel = 4;    //每个单元四个节点
		int ndof = 3;   //每个节点三个自由度
		int nnode = gcoord.size();
		int nel = nodes.size();
		int sdof = nnode * ndof;
		int edof = nnel * ndof;
		int n_ddl = 3 * gcoord.size();
		int nK = (ndof * nnel) * (ndof * nnel) * nodes.size();
		int nF = (ndof * nnel) * (ndof * nnel) * nodes.size();
		vector<int> colK(nK, 0);
		vector<int> rowK(nK, 0);
		vector<double> valK(nK, 0);
		vector<int> rowF(nF, 0);
		vector<double> valF(nF, 0);
		nK = 0; nF = 0;
		vector<int> index(nnel * ndof, 0);
		vector<int> elforce(nnel * ndof, 0);
		vector<double> eldisp(nnel * ndof, 0);
		vector<vector<int>> stress(nnel, vector<int>(3, 0));
		vector<vector<int>> strain(nnel, vector<int>(3, 0));
		vector<vector<int>> kinmtx(3, vector<int>(edof, 0));
		vector<vector<double>> matmtx(6, vector<double>(6, 0));
		vector<double> xcoord(nnel, 0);
		vector<double> ycoord(nnel, 0);
		vector<double> zcoord(nnel, 0);
		vector<int> nd(nnel, 0);
		vector<vector<int>> node_stressx(AllEles3D.size(), vector<int>(nnel, 0));
		vector<vector<int>> node_stressy(AllEles3D.size(), vector<int>(nnel, 0));
		vector<vector<int>> node_stressz(AllEles3D.size(), vector<int>(nnel, 0));
		vector<vector<int>> node_stressxy(AllEles3D.size(), vector<int>(nnel, 0));
		vector<vector<int>> node_stressyz(AllEles3D.size(), vector<int>(nnel, 0));
		vector<vector<int>> node_stresszx(AllEles3D.size(), vector<int>(nnel, 0));
		int N = 1;
		vector<double> shape(4, 0), dhdr(4, 0), dhds(4, 0), dhdt(4, 0);

		////边界条件////
		int Boundary = 0;   //1
		double TotalVolume=0;
		vector<double> Tot_Bond_value(4, 0);
		vector<double> bcdof;
		vector<double> bcval;
		vector<vector<double>> Tab_dep;
		vector<vector<double>> matix_e(3, vector<double>(3, 0));
		if (Boundary == 0)
		{
			FeCofBC_Rotation_old_C4(Tot_Bond_value, TotalVolume, bcdof, bcval, gcoord, Mode);
		}
		else if (Boundary == 1)
		{
			Boundarymatrix(matix_e, TotalVolume, Tot_Bond_value, gcoord, Mode);
			BCcondPeriodic(Tab_dep, gcoord, matix_e, Mode);
		}

		////材料属性////
		int Matrial = 1;
		vector<vector<double>> elprop;
		vector<double> Elprop;
		vector<vector<double>> Lpoint;
		vector<double> weight;
		feglqd4(Lpoint, weight, N);
		if (Matrial == 0)
		{
			//vector<double> elprop1, elprop2;
			elprop.resize(2);
			elprop[0].push_back(10e9); elprop[0].push_back(0.2);
			elprop[1].push_back(10e9); elprop[1].push_back(0.2);
		}
		else if (Matrial == 1)
		{
			elprop.resize(1);
			elprop[0].push_back(168.04e9);
			elprop[0].push_back(30.15e9);
			elprop[0].push_back(0.166);
			elprop[0].push_back(0.468);
			elprop[0].push_back(13.27e9);
			//vector<double> Elprop;
			Elprop.push_back(350e9); Elprop.push_back(0.2);
		}

		////Fiber////
		vector<int> FiberElement;
		int in, eiER;
		//vector< vector<int> > k(edof,vector<int>(edof,0));
		vector<vector<double>> k(((nnel - 1) * 3 + 3), vector<double>(((nnel - 1) * 3 + 3), 0));
		for (size_t II = 0; II < FiberEle.size(); II++)
		{
			//FiberElement=cell2mat(FiberEle(1,II));
			/*for (size_t j = 0; j < FiberEle[II].size(); j++)
			{
				FiberElement.push_back(FiberEle[II][j]);
			}*/
			//FiberEle[II]
			for (size_t ij = 0; ij < FiberEle[II].size(); ij++)
			{
				in = FiberEle[II][ij];
				eiER = FiberEle[II][ij];
				for (size_t ind = 0; ind < nnel; ind++)
				{
					nd[ind] = nodes[eiER][ind];
					xcoord[ind] = gcoord[nd[ind]][0];
					ycoord[ind] = gcoord[nd[ind]][1];
					zcoord[ind] = gcoord[nd[ind]][2];
				}
				//}
				if (Matrial == 0)
				{
					matmtx = fematiso(4, elprop[0]);
				}
				else if (Matrial == 1)
				{
					if (Curve == 0)
					{
						matmtx = fematiso(5, elprop[0]);
					}
					else if (Curve == 1)
					{
						vector<vector<double>> Trans_matrix(6, vector<double>(6, 0));
						Trans_matrix = Trans_Matrix(xcoord, ycoord, zcoord, Magnitude, II+1);
						vector<vector<double>> Matmtx(6, vector<double>(6, 0));
						Matmtx = fematiso(5, elprop[0]);
						vector<vector<double>> TT;
						vector<vector<double>> TT_M;
						TT = vectors_Transpose(Trans_matrix);
						TT_M = vectors_multiply(TT, Matmtx);
						matmtx = vectors_multiply(TT_M, Trans_matrix);
						//int jjj = 0;
					}
				}
				//vector<vector<double>> k(((nnel - 1) * 3 + 3), vector<double>(((nnel - 1) * 3 + 3), 0));
				for (size_t i = 0; i < N; i++)
				{
					vector<vector<double>> jacob3;
					double detjacob;
					vector<vector<double>> invjacob;
					double V;
					vector<vector<double>> kinmtx;
					feisos8(shape, dhdr, dhds, dhdt, nnel, Lpoint);
					jacob3 = fejacob3(nnel, dhdr, dhds, dhdt, xcoord, ycoord, zcoord);
					detjacob = vector_det(jacob3);
					invjacob = vectors_inversion(jacob3);
					vector<double> dhdx(nnel,0), dhdy(nnel, 0), dhdz(nnel, 0);
					federiv3(dhdx, dhdy, dhdz, nnel, dhdr, dhds, dhdt, invjacob);
					V = ComputeVolume4V2(xcoord, ycoord, zcoord);
					kinmtx = fekine3d(nnel, dhdx, dhdy, dhdz);
					//vector<vector<double>> k(kinmtx[0].size(),vector<double>(kinmtx[0].size(),0));
					vector<vector<double>> kinmtxT = vectors_Transpose(kinmtx);
					vector<vector<double>> kT_m = vectors_multiply(kinmtxT, matmtx);
					vector<vector<double>> kT_m_k = vectors_multiply(kT_m, kinmtx);
					vector<vector<double>> kT_m_kaw = vectors_multiply_2number(kT_m_k, abs(detjacob) * weight[i]);
					k = vectors_2plus(k, kT_m_kaw);
				}
				vector<int> pts(4, 0);
				pts[0] = nodes[in][0]; pts[1] = nodes[in][1]; pts[2] = nodes[in][2]; pts[3] = nodes[in][3];
				vector<int> ddl(ndof * nnel, 0);
				for (size_t id = 0,it=0; id < ndof * nnel; id = id + 3,it++)
				{
					ddl[id] = pts[it] * 3;
					ddl[id + 1] = pts[it] * 3 + 1;
					ddl[id + 2] = pts[it] * 3+2;
				}
				//============================assemblage==================================
				for (size_t j = 0; j < ndof * nnel; j++)
				{
					for (size_t m = 0; m < ndof * nnel; m++)
					{
						//nK = nK + 1;
						rowK[nK] = ddl[j];
						colK[nK] = ddl[m];
						valK[nK] = k[j][m];
						nK = nK + 1;
					}
				}
				for (size_t ik = 0; ik < k.size(); ik++)
				{
					for (size_t jk = 0; jk < k[ik].size(); jk++)
					{
						k[ik][jk] = 0;
					}
				}
			}
			int ae = 1;
		}
		int aaa = 111;
		k.clear();
		////Out////
		int ou;
		//vector<vector<double>> k(edof, vector<double>(edof, 0));
		k.resize(edof);
		//omp_set_num_threads(8);
//#pragma omp parallel
		//{
           // #pragma omp for
			for (int i = 0; i < k.size(); i++)
			{
				k[i].resize(edof);
			}
		//}
//#pragma omp parallel for
//#pragma omp parallel
		//{
            //#pragma omp for
			for (int ij = 0; ij < Interstitial.size(); ij++)
			{
				ou = Interstitial[ij];
				eiER = Interstitial[ij];
				for (size_t ind = 0; ind < nnel; ind++)
				{
					nd[ind] = nodes[eiER][ind];
					xcoord[ind] = gcoord[nd[ind]][0];
					ycoord[ind] = gcoord[nd[ind]][1];
					zcoord[ind] = gcoord[nd[ind]][2];
				}
				//}
				if (Matrial == 0)
				{
					matmtx = fematiso(4, elprop[1]);
				}
				else if (Matrial == 1)
				{
					matmtx = fematiso(4, Elprop);
				}
				//vector<vector<double>> k(((nnel - 1) * 3 + 3), vector<double>(((nnel - 1) * 3 + 3), 0));
				for (size_t i = 0; i < N; i++)
				{
					vector<vector<double>> jacob3;
					double detjacob;
					vector<vector<double>> invjacob;
					double V;
					vector<vector<double>> kinmtx;
					feisos8(shape, dhdr, dhds, dhdt, nnel, Lpoint);
					jacob3 = fejacob3(nnel, dhdr, dhds, dhdt, xcoord, ycoord, zcoord);
					detjacob = vector_det(jacob3);
					invjacob = vectors_inversion(jacob3);
					vector<double> dhdx(nnel, 0), dhdy(nnel, 0), dhdz(nnel, 0);
					federiv3(dhdx, dhdy, dhdz, nnel, dhdr, dhds, dhdt, invjacob);
					V = ComputeVolume4V2(xcoord, ycoord, zcoord);
					kinmtx = fekine3d(nnel, dhdx, dhdy, dhdz);
					//vector<vector<double>> k(kinmtx[0].size(),vector<double>(kinmtx[0].size(),0));
					vector<vector<double>> kinmtxT = vectors_Transpose(kinmtx);
					vector<vector<double>> kT_m = vectors_multiply(kinmtxT, matmtx);
					vector<vector<double>> kT_m_k = vectors_multiply(kT_m, kinmtx);
					vector<vector<double>> kT_m_kaw = vectors_multiply_2number(kT_m_k, abs(detjacob) * weight[i]);
					k = vectors_2plus(k, kT_m_kaw);
				}
				vector<int> pts(4, 0);
				pts[0] = nodes[ou][0]; pts[1] = nodes[ou][1]; pts[2] = nodes[ou][2]; pts[3] = nodes[ou][3];
				vector<int> ddl(ndof * nnel, 0);
				for (size_t id = 0, it = 0; id < ndof * nnel; id = id + 3, it++)
				{
					ddl[id] = pts[it] * 3;
					ddl[id + 1] = pts[it] * 3 + 1;
					ddl[id + 2] = pts[it] * 3 + 2;
				}
				//============================assemblage==================================

				for (size_t j = 0; j < ndof * nnel; j++)
				{
					for (size_t m = 0; m < ndof * nnel; m++)
					{
						//nK = nK + 1;
						rowK[nK] = ddl[j];
						colK[nK] = ddl[m];
						valK[nK] = k[j][m];
						nK = nK + 1;
					}
				}
				for (size_t ik = 0; ik < k.size(); ik++)
				{
					for (size_t jk = 0; jk < k[ik].size(); jk++)
					{
						k[ik][jk] = 0;
					}
				}
			}
		//}
		////%%////
		vector<vector<double>> kk= vector_sparse(rowK, colK, valK, n_ddl, n_ddl);
		//vector<vector<double>> kk1 = ternary_sparse(rowK, colK, valK, n_ddl, n_ddl);
		//////////////////////////////////////////////////////////////////
		////计算位移////
 		int a = 111;
		vector<double> Resdisp;
		if (Boundary == 0)
		{
			vector<double> ff(sdof, 0);
			vector<vector<double>> Tab_dep = vectors_1combine(bcdof, bcval);
			vector<vector<double>> Kr;
			vector<int> listeddl;
			//vector<double> Resdisp;
			double* Fr = BCimposeT3(Kr, listeddl, Resdisp, kk, ff, Tab_dep);
			// Resdisp(listeddl,1) =Kr\Fr;
			//vector<vector<double>> Kr_inv = vectors_inversion(Kr);
			//********************
			//建立动态数组，将vector数组的数据转入该动态数组求逆，后期考虑将需要求逆的矩阵保存为vector数组
			//********************
			clock_t start, end;
			start = clock();
			int m = Kr.size();
			int n = Kr[0].size();
			float* Kr_invm = new float[m * n];
			for (size_t i = 0; i < m; i++)
			{
				for (size_t j = 0; j < n; j++)
				{
					Kr_invm[i * n + j] = Kr[i][j];
				}
			}
			//double* Fr_d = new double[m * n];
			float* Kr_invmb = new float[m * n]();
			MKL_inv(Kr_invmb, Kr_invm, m);
			end = clock();
			double dur = (double)(end - start);
			cout << "Time is " << (dur / CLOCKS_PER_SEC) << endl;
			//vector<vector<double>> Kr_invFr = vectors_multiply(Kr_inv, Fr);//矩阵乘法;
			MatrixXf MKr_invmb(m, n);
			MatrixXf MFr(n, 1);
			for (size_t i = 0; i < m; i++)
			{
				for (size_t j = 0; j < n; j++)
				{
					MKr_invmb(i, j) = Kr_invmb[i * n + j];
				}
				MFr(i) = Fr[i];
			}
			MatrixXf MKK = MKr_invmb * MFr;
			for (size_t i = 0; i < listeddl.size(); i++)
			{
				Resdisp[listeddl[i]] = MKK(i);
			}

			//释放动态数组
			delete[] Kr_invm;
			delete[] Kr_invmb;
			delete[] Fr;
			int aaaa = 0;
		}
		else if (Boundary == 1)
		{
			vector<vector<double>> ff = vector_sparse(rowK, colK, valK, n_ddl, n_ddl);
		}
		vector<vector<double>> d = vectors_reshape(Resdisp, ndof, nnode);
		vector<double> num(nnode, 0);
		for (size_t i = 0; i < nnode; i++)
		{
			num[i] = i;
		}
		vector<vector<double>> Disp(nnode, vector<double>(ndof + 1, 0));
		for (size_t i = 0; i < nnode; i++)
		{
				Disp[i][0] = num[i];
				Disp[i][1] = d[0][i];
				Disp[i][2] = d[1][i];
				Disp[i][3] = d[2][i];
		}
		//%%
		double S11 = 0; 
		double T11 = 0;
		double T22 = 0;
		double S22 = 0;
		double S33 = 0;
		double S12 = 0;
		double S13 = 0;
		double S23 = 0;
		double T33 = 0;
		double T12 = 0;
		double T13 = 0;
		double T23 = 0;
		double iopt = 0;

		////////////
		//%% Fiber//
		////////////
		for (size_t II = 0; II < FiberEle.size(); II++)
		{
			for (size_t ij = 0; ij < FiberEle[II].size(); ij++)
			{
				eiER = FiberEle[II][ij];
				for (size_t ind = 0; ind < nnel; ind++)
				{
					nd[ind] = nodes[eiER][ind];
					xcoord[ind] = gcoord[nd[ind]][0];
					ycoord[ind] = gcoord[nd[ind]][1];
					zcoord[ind] = gcoord[nd[ind]][2];
				}
				//}
				if (Matrial == 0)
				{
					matmtx = fematiso(4, elprop[0]);
				}
				else if (Matrial == 1)
				{
					if (Curve == 0)
					{
						matmtx = fematiso(5, elprop[0]);
					}
					else if (Curve == 1)
					{
						vector<vector<double>> Trans_matrix(6, vector<double>(6, 0));
						Trans_matrix = Trans_Matrix(xcoord, ycoord, zcoord, Magnitude, II + 1);
						vector<vector<double>> Matmtx(6, vector<double>(6, 0));
						Matmtx = fematiso(5, elprop[0]);
						vector<vector<double>> TT;
						vector<vector<double>> TT_M;
						TT = vectors_Transpose(Trans_matrix);
						TT_M = vectors_multiply(TT, Matmtx);
						matmtx = vectors_multiply(TT_M, Trans_matrix);
					}
				}
				int intp = 0;
				MatrixXf Gauss_strain(N, 6);
				MatrixXf Gauss_stress(N, 6);
				for (size_t i = 0; i < N; i++)
				{
					vector<vector<double>> jacob3;
					//double detjacob;
					vector<vector<double>> invjacob;
					//double V;
					vector<vector<double>> kinmtx;
					feisos8(shape, dhdr, dhds, dhdt, nnel, Lpoint);
					jacob3 = fejacob3(nnel, dhdr, dhds, dhdt, xcoord, ycoord, zcoord);
					//detjacob = vector_det(jacob3);
					invjacob = vectors_inversion(jacob3);
					vector<double> dhdx(nnel, 0), dhdy(nnel, 0), dhdz(nnel, 0);
					federiv3(dhdx, dhdy, dhdz, nnel, dhdr, dhds, dhdt, invjacob);
					kinmtx = fekine3d(nnel, dhdx, dhdy, dhdz);
					vector<int> index = feeldof(nd, nnel, ndof);
					int aaasd;
					for (size_t id = 0; id < edof; id++)
					{
						eldisp[id]= Resdisp[index[id]];
					}
					MatrixXf MKr_kinmtx(kinmtx.size(), kinmtx[0].size());
					MatrixXf MFr_eldisp(eldisp.size(), 1);
					for (size_t i1 = 0; i1 < kinmtx.size(); i1++)
					{
						for (size_t j = 0; j < kinmtx[0].size(); j++)
						{
							MKr_kinmtx(i1, j) = kinmtx[i1][j];
						}
						//MFr_eldisp(i1) = eldisp[i1];
					}
					//
					for (size_t i1 = 0; i1 < eldisp.size(); i1++)
					{
						MFr_eldisp(i1) = eldisp[i1];
					}

					MatrixXf Gstrain = MKr_kinmtx * MFr_eldisp;//Gstrain = kinmtx * eldisp; compute Gauss point strains
					MatrixXf MKr_matmtx(matmtx.size(), matmtx[0].size());
					for (size_t i1 = 0; i1 < matmtx.size(); i1++)
					{
						for (size_t j = 0; j < matmtx[i1].size(); j++)
						{
							MKr_matmtx(i1, j) = matmtx[i1][j];
						}
					}
					MatrixXf Gstress = MKr_matmtx * Gstrain;//Gstress = matmtx*Gstrain;% compute Gauss point stresses
					//intp = intp + 1;
					for (size_t ig = 0; ig < 6; ig++)
					{
						Gauss_strain(intp, ig) = Gstrain(ig);
						Gauss_stress(intp, ig) = Gstress(ig);
					}
					intp = intp + 1;
				}
				for (size_t i = 0; i < N; i++)
				{
					vector<vector<double>> jacob3;
					double detjacob;
					vector<vector<double>> invjacob;
					//double V;
					vector<vector<double>> kinmtx;
					feisos8(shape, dhdr, dhds, dhdt, nnel, Lpoint);
					jacob3 = fejacob3(nnel, dhdr, dhds, dhdt, xcoord, ycoord, zcoord);
					detjacob = vector_det(jacob3);
					invjacob = vectors_inversion(jacob3);
					vector<double> dhdx(nnel, 0), dhdy(nnel, 0), dhdz(nnel, 0);
					federiv3(dhdx, dhdy, dhdz, nnel, dhdr, dhds, dhdt, invjacob);
					kinmtx = fekine3d(nnel, dhdx, dhdy, dhdz);
					S11 = S11 + 1 / TotalVolume * Gauss_stress(i, 0) * abs(detjacob) * weight[i];
					S22 = S22 + 1 / TotalVolume * Gauss_stress(i, 1) * abs(detjacob) * weight[i];
					S33 = S33 + 1 / TotalVolume * Gauss_stress(i, 2) * abs(detjacob) * weight[i];
					S23 = S23 + 1 / TotalVolume * Gauss_stress(i, 3) * abs(detjacob) * weight[i];
					S13 = S13 + 1 / TotalVolume * Gauss_stress(i, 4) * abs(detjacob) * weight[i];
					S12 = S12 + 1 / TotalVolume * Gauss_stress(i, 5) * abs(detjacob) * weight[i];
					T11 = T11 + 1 / TotalVolume * Gauss_strain(i, 0) * abs(detjacob) * weight[i];
					T22 = T22 + 1 / TotalVolume * Gauss_strain(i, 1) * abs(detjacob) * weight[i];
					T33 = T33 + 1 / TotalVolume * Gauss_strain(i, 2) * abs(detjacob) * weight[i];
					T23 = T23 + 1 / TotalVolume * Gauss_strain(i, 3) * abs(detjacob) * weight[i];
					T13 = T13 + 1 / TotalVolume * Gauss_strain(i, 4) * abs(detjacob) * weight[i];
					T12 = T12 + 1 / TotalVolume * Gauss_strain(i, 5) * abs(detjacob) * weight[i];
				}
			}
		}

		//////////
		//%% Out//
		for (size_t ij = 0; ij < Interstitial.size(); ij++)
		{
			eiER = Interstitial[ij];
			for (size_t ind = 0; ind < nnel; ind++)
			{
				nd[ind] = nodes[eiER][ind];
				xcoord[ind] = gcoord[nd[ind]][0];
				ycoord[ind] = gcoord[nd[ind]][1];
				zcoord[ind] = gcoord[nd[ind]][2];
			}
			//}
			if (Matrial == 0)
			{
				matmtx = fematiso(4, elprop[0]);
			}
			else if (Matrial == 1)
			{
				matmtx = fematiso(4, Elprop);
			}
			int intp = 0;
			MatrixXf Gauss_strain(N, 6);
			MatrixXf Gauss_stress(N, 6);
			for (size_t i = 0; i < N; i++)
			{
				vector<vector<double>> jacob3;
				vector<vector<double>> invjacob;
				vector<vector<double>> kinmtx;
				feisos8(shape, dhdr, dhds, dhdt, nnel, Lpoint);
				jacob3 = fejacob3(nnel, dhdr, dhds, dhdt, xcoord, ycoord, zcoord);
				invjacob = vectors_inversion(jacob3);
				vector<double> dhdx(nnel, 0), dhdy(nnel, 0), dhdz(nnel, 0);
				federiv3(dhdx, dhdy, dhdz, nnel, dhdr, dhds, dhdt, invjacob);
				kinmtx = fekine3d(nnel, dhdx, dhdy, dhdz);
				vector<int> index = feeldof(nd, nnel, ndof);
				for (size_t id = 0; id < edof; id++)
				{
					eldisp[id]=Resdisp[index[id]];
				}
				MatrixXf MKr_kinmtx(kinmtx.size(), kinmtx[0].size());
				MatrixXf MFr_eldisp(eldisp.size(), 1);
				for (size_t i1 = 0; i1 < kinmtx.size(); i1++)
				{
					for (size_t j = 0; j < kinmtx[0].size(); j++)
					{
						MKr_kinmtx(i1, j) = kinmtx[i1][j];
					}
					//MFr_eldisp(i1) = eldisp[i1];
				}
				for (size_t i1 = 0; i1 < eldisp.size(); i1++)
				{
					MFr_eldisp(i1) = eldisp[i1];
				}
				MatrixXf Gstrain = MKr_kinmtx * MFr_eldisp;//Gstrain = kinmtx * eldisp; compute Gauss point strains
				MatrixXf MKr_matmtx(matmtx.size(), matmtx[0].size());
				for (size_t i1 = 0; i1 < matmtx.size(); i1++)
				{
					for (size_t j = 0; j < matmtx[i1].size(); j++)
					{
						MKr_matmtx(i1, j) = matmtx[i1][j];
					}
				}
				MatrixXf Gstress = MKr_matmtx * Gstrain;//Gstress = matmtx*Gstrain;% compute Gauss point stresses
				//intp = intp + 1;
				for (size_t ig = 0; ig < 6; ig++)
				{
					Gauss_strain(intp, ig) = Gstrain(ig);
					Gauss_stress(intp, ig) = Gstress(ig);
				}
				intp = intp + 1;
			}
			for (size_t i = 0; i < N; i++)
			{
				vector<vector<double>> jacob3;
				double detjacob;
				vector<vector<double>> invjacob;
				vector<vector<double>> kinmtx;
				feisos8(shape, dhdr, dhds, dhdt, nnel, Lpoint);
				jacob3 = fejacob3(nnel, dhdr, dhds, dhdt, xcoord, ycoord, zcoord);
				detjacob = vector_det(jacob3);
				invjacob = vectors_inversion(jacob3);
				vector<double> dhdx(nnel, 0), dhdy(nnel, 0), dhdz(nnel, 0);
				federiv3(dhdx, dhdy, dhdz, nnel, dhdr, dhds, dhdt, invjacob);
				kinmtx = fekine3d(nnel, dhdx, dhdy, dhdz);
				S11 = S11 + 1 / TotalVolume * Gauss_stress(i, 0) * abs(detjacob) * weight[i];
				S22 = S22 + 1 / TotalVolume * Gauss_stress(i, 1) * abs(detjacob) * weight[i];
				S33 = S33 + 1 / TotalVolume * Gauss_stress(i, 2) * abs(detjacob) * weight[i];
				S23 = S23 + 1 / TotalVolume * Gauss_stress(i, 3) * abs(detjacob) * weight[i];
				S13 = S13 + 1 / TotalVolume * Gauss_stress(i, 4) * abs(detjacob) * weight[i];
				S12 = S12 + 1 / TotalVolume * Gauss_stress(i, 5) * abs(detjacob) * weight[i];
				T11 = T11 + 1 / TotalVolume * Gauss_strain(i, 0) * abs(detjacob) * weight[i];
				T22 = T22 + 1 / TotalVolume * Gauss_strain(i, 1) * abs(detjacob) * weight[i];
				T33 = T33 + 1 / TotalVolume * Gauss_strain(i, 2) * abs(detjacob) * weight[i];
				T23 = T23 + 1 / TotalVolume * Gauss_strain(i, 3) * abs(detjacob) * weight[i];
				T13 = T13 + 1 / TotalVolume * Gauss_strain(i, 4) * abs(detjacob) * weight[i];
				T12 = T12 + 1 / TotalVolume * Gauss_strain(i, 5) * abs(detjacob) * weight[i];
			}
		}

		//////////
		//%% /////
		//////////
		vector<double> SS;
		vector<double> TT;
		SS.push_back(S11), SS.push_back(S22), SS.push_back(S33), SS.push_back(S23), SS.push_back(S13), SS.push_back(S12);
		TT.push_back(T11), TT.push_back(T22), TT.push_back(T33), TT.push_back(T23), TT.push_back(T13), TT.push_back(T12);

		//double Val_D11, Val_D12, Val_D22, Val_D13, Val_D23, Val_D33;
		//double Val_D16, Val_D26, Val_D36, Val_D46, Val_D56, Val_D66;
		//double Val_D15, Val_D25, Val_D35, Val_D45, Val_D55;
		//double Val_D14, Val_D24, Val_D34, Val_D44;
		if (Mode == 1)
		{
			Val_D11 = S11 / (T11);
		}
		else if (Mode == 2)
		{
			Val_D12 = S11 / (T22);
			Val_D22 = S22 / (T22);
		}
		else if (Mode == 3)
		{
			Val_D13 = S11 / T33;
			Val_D23 = S22 / T33;
			Val_D33 = S33 / T33;
		}
		else if (Mode == 4)
		{
			Val_D16 = S11 / (sqrt(2) * T12);
			Val_D26 = S22 / (sqrt(2) * T12);
			Val_D36 = S33 / (sqrt(2) * T12);
			Val_D46 = S23 / (2 * T12);
			Val_D56 = S13 / (2 * T12);
			Val_D66 = S12 / (2 * T12);
		}
		else if (Mode == 5)
		{
			Val_D15 = S11 / (sqrt(2) * T13);
			Val_D25 = S22 / (sqrt(2) * T13);
			Val_D35 = S33 / (sqrt(2) * T13);
			Val_D45 = S23 / (2 * T13);
			Val_D55 = S13 / (2 * T13);
		}
		else if (Mode == 6)
		{
			Val_D14 = S11 / (sqrt(2) * T23);
			Val_D24 = S22 / (sqrt(2) * T23);
			Val_D34 = S33 / (sqrt(2) * T23);
			Val_D44 = S23 / (2 * T23);
		}
	}
	float* Val_D = new float[36]();
	Val_D[0] = Val_D11;  Val_D[1] = Val_D12;  Val_D[2] = Val_D13;  Val_D[3] = Val_D14;  Val_D[4] = Val_D15;  Val_D[5] = Val_D16;
	Val_D[6] = Val_D12;  Val_D[7] = Val_D22;  Val_D[8] = Val_D23;  Val_D[9] = Val_D24;  Val_D[10] = Val_D25; Val_D[11] = Val_D26;
	Val_D[12] = Val_D13; Val_D[13] = Val_D23; Val_D[14] = Val_D33; Val_D[15] = Val_D34; Val_D[16] = Val_D35; Val_D[17] = Val_D36;
	Val_D[18] = Val_D14; Val_D[19] = Val_D24; Val_D[20] = Val_D34; Val_D[21] = Val_D44; Val_D[22] = Val_D45; Val_D[23] = Val_D46;
	Val_D[24] = Val_D15; Val_D[25] = Val_D25; Val_D[26] = Val_D35; Val_D[27] = Val_D45; Val_D[28] = Val_D55; Val_D[29] = Val_D56;
	Val_D[30] = Val_D16; Val_D[31] = Val_D26; Val_D[32] = Val_D36; Val_D[33] = Val_D46; Val_D[34] = Val_D56; Val_D[35] = Val_D66;
	float* MKL_invVal = new float[36]();
	MKL_inv(MKL_invVal, Val_D, 6);
	double A, B, C;
	A = 1 / MKL_invVal[0];
	B = 1 / MKL_invVal[7];
	C = 1 / MKL_invVal[14];
	int aassd = 0;
}
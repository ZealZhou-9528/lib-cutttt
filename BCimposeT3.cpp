#define EIGEN_USE_MKL_ALL
//#define EIGEN_VECTORIZE_SSE4_2
#include <iostream>
#include <vector>
#include <algorithm>
#include <Eigen/Dense>
#include <ctime>
#include <Eigen/Core>
//#include <omp.h>
using namespace Eigen;
using namespace std;
vector<int> vectors_setdiff(vector<int> v1, vector<int> v2);
vector<double> vector_m1multi(int Tab_dep1, vector<vector<double>> K, double Tab_dep2);
vector<double> vectors_1subtract(vector<double> v1, vector<double> v2);   //一维数组减法
double* BCimposeT3(vector<vector<double>>& Kr, vector<int>& listeddl, vector<double>& T, vector<vector<double>> K, vector<double> F, vector<vector<double>> Tab_dep)
{
	vector<int> ddlconnus;
	for (size_t i = 0; i < Tab_dep.size(); i++)
	{
		ddlconnus.push_back(Tab_dep[i][0]);
	}
	//vector<double> T(F.size(),0);
	T.resize(F.size());
	for (size_t i = 0; i < Tab_dep.size(); i++)
	{
		T[Tab_dep[i][0]] = Tab_dep[i][1];
	}
	////////////////////////////////////////////////Tab_dep.size()

	///////////////////KTab自写
	///////////////////KEigen使用Eigen库
	///////////////////
	//clock_t startKT, endKT;
	//startKT = clock();
	//vector<double> KTab;
	//for (size_t i = 0; i < Tab_dep.size(); i++)
	//{
	//	KTab = vector_m1multi(Tab_dep[i][0], K, Tab_dep[i][1]);
	//	F[i] = F[i] - K[Tab_dep[i][0]][i]* Tab_dep[i][1];
	//	F = vectors_1subtract(F, KTab);
	//}
	//endKT = clock();
	//double dur = (double)(endKT - startKT);
	//cout << "（自写）Time is " << (dur / CLOCKS_PER_SEC) << endl;
	//////////////////
	clock_t startKE, endKE;
	startKE = clock();
	MatrixXf Ktab(K.size(), 1);
	MatrixXf Ktab2(1, 1);
	MatrixXf Ktabt2;
	int aaa;
	//omp_set_num_threads(8);
//#pragma omp parallel for
	for (size_t i = 0; i < Tab_dep.size(); i++)
	{
		for (size_t j = 0; j < K.size(); j++)
		{
			Ktab(j) = K[Tab_dep[i][0]][j];
		}
		Ktab2(0) = Tab_dep[i][1];
		Ktabt2 = Ktab * Ktab2;
		for (size_t k = 0; k < F.size(); k++)
		{
			F[k] = F[k] - Ktabt2(k);
		}
		//F = vectors_1subtract(F, KTab);
		aaa = 0;
	}
	endKE = clock();
	double dur1 = (double)(endKE - startKE);
	cout << "（Eigen）Time is " << (dur1 / CLOCKS_PER_SEC) << endl;
	//////////////////
	//////////////////
	//////////////////
	vector<int> Fsize;
	for (size_t i = 0; i < F.size(); i++)
	{
		Fsize.push_back(i);
	}
	listeddl = vectors_setdiff(Fsize, ddlconnus);
	Kr.resize(listeddl.size());
	for (size_t i = 0; i < listeddl.size(); i++)
	{
		Kr[i].resize(listeddl.size());
	}
	Kr.resize(listeddl.size());
	//Fr.resize(listeddl.size());
	double* Fr = new double[listeddl.size()];
	for (size_t i = 0; i < listeddl.size(); i++)
	{
		for (size_t j = 0; j < listeddl.size(); j++)
		{
			Kr[i][j] = K[listeddl[i]][listeddl[j]];
		}
		Fr[i] = F[listeddl[i]];

	}
	int aaaa = 0;
	//double* Fr = new double[listeddl.size()];
	return Fr;
}

vector<double> vector_m1multi(int Tab_dep1, vector<vector<double>> K, double Tab_dep2)
{
	vector<double> Km(K.size());
	for (size_t i = 0; i < K.size(); i++)
	{
		Km[i] = K[Tab_dep1][i] * Tab_dep2;
	}
	return Km;
}

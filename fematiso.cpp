#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<vector<double>> vectors_inversion(vector<vector<double>> a);
vector<vector<double>> fematiso(int iopt, vector<double> elprop)
{
	double El=0;   // 轴向弹性模量
	double Ep=0;   // 横向弹性模量
	double Vl=0;   // 轴向泊松比
	double Vp=0;   // 横向泊松比
	double mul=0;  // 轴向剪切模量
	double Kp=0;   // 横向面积模量
	double mup=0;  // 横向剪切模量
	double Sital=0;// 轴向模量
	double Iotal=0;// 横向模量
	double E=0;    // 轴向弹性模量
	double mu=0;   // 轴向剪切模量
	if (elprop.size()==5)
	{
		El = elprop[0];   
		Ep = elprop[1];   
		Vl = elprop[2];   
		Vp = elprop[3];   
		mul = elprop[4];  
		Kp = (Ep * El) / (2 * (El * (1 - Vp) - 2 * Ep * Vl * Vl)); 
		mup = Ep / (2 * (1 + Vp));                               
		Sital = (El * El * (1 - Vp)) / (El * (1 - Vp) - 2 * Ep * Vl * Vl);
		Iotal = (Ep * El * Vl) / (El * (1 - Vp) - 2 * Ep * Vl * Vl);
	}
	else
	{
		E = elprop[0];
		mu = elprop[1];
	}
	vector< vector<double> > matmtrx(3, vector<double>(3, 0));
	if (iopt == 1)
	{
		double midex = E / (1 - mu * mu);
		matmtrx[0][0] = 1 * midex; matmtrx[0][1] = mu * midex; matmtrx[0][2] = 0 * midex;
		matmtrx[1][0] = mu * midex; matmtrx[1][1] = 1 * midex; matmtrx[1][2] = 0 * midex;
		matmtrx[2][0] = 0 * midex; matmtrx[2][1] = 0 * midex; matmtrx[2][2] = ((1 - mu) / 2) * midex;
	}
	else if (iopt == 2)
	{
		double midex = E / ((1 + mu) * (1 - 2 * mu));
		matmtrx[0][0] = (1 - mu) * midex; matmtrx[0][1] = mu * midex; matmtrx[0][2] = 0 * midex;
		matmtrx[1][0] = mu * midex; matmtrx[1][1] = (1 - mu) * midex; matmtrx[1][2] = 0 * midex;
		matmtrx[2][0] = 0 * midex; matmtrx[2][1] = 0 * midex; matmtrx[2][2] = ((1 - 2 * mu) / 2) * midex;
	}
	else if (iopt == 3)
	{
		double midex = E / ((1 + mu) * (1 - 2 * mu));
		for (size_t i3 = 0; i3 < 3; i3++)
		{
			matmtrx[i3].resize(4);
		}
		matmtrx[0][0] = (1 - mu) * midex; matmtrx[0][1] = mu * midex; matmtrx[0][2] = mu * midex; matmtrx[0][3] = 0 * midex;
		matmtrx[1][0] = mu * midex; matmtrx[1][1] = (1 - mu) * midex; matmtrx[1][2] = mu * midex; matmtrx[1][3] = 0 * midex;
		matmtrx[2][0] = 0 * midex; matmtrx[2][1] = 0 * midex; matmtrx[2][2] = 0 * midex; matmtrx[2][3] = ((1 - 2 * mu) / 2) * midex;
	}
	else if (iopt == 4)
	{
		double midex = E / ((1 + mu) * (1 - 2 * mu));
		matmtrx.resize(6);
		for (size_t i3 = 0; i3 < matmtrx.size(); i3++)
		{
			matmtrx[i3].resize(6);
		}
		matmtrx[0][0] = (1 - mu) * midex;  matmtrx[0][1] = mu * midex;       matmtrx[0][2] = mu * midex;        matmtrx[0][3] = 0 * midex; matmtrx[0][4] = 0 * midex; matmtrx[0][5] = 0 * midex;
		matmtrx[1][0] = mu * midex;        matmtrx[1][1] = (1 - mu) * midex; matmtrx[1][2] = mu * midex;        matmtrx[1][3] = 0 * midex; matmtrx[1][4] = 0 * midex; matmtrx[1][5] = 0 * midex;
		matmtrx[2][0] = mu * midex;        matmtrx[2][1] = mu * midex;       matmtrx[2][2] = (1 - mu) * midex;  matmtrx[2][3] = 0 * midex; matmtrx[2][4] = 0 * midex; matmtrx[2][5] = 0 * midex;
		matmtrx[3][0] = 0 * midex; matmtrx[3][1] = 0 * midex; matmtrx[3][2] = 0 * midex; matmtrx[3][3] = (1 - 2 * mu) * midex; matmtrx[3][4] = 0 * midex;             matmtrx[3][5] = 0 * midex;
		matmtrx[4][0] = 0 * midex; matmtrx[4][1] = 0 * midex; matmtrx[4][2] = 0 * midex; matmtrx[4][3] = 0 * midex;            matmtrx[4][4] = (1 - 2 * mu) * midex;  matmtrx[4][5] = 0 * midex;
		matmtrx[5][0] = 0 * midex; matmtrx[5][1] = 0 * midex; matmtrx[5][2] = 0 * midex; matmtrx[5][3] = 0 * midex;            matmtrx[5][4] = 0 * midex;             matmtrx[5][5] = (1 - 2 * mu) * midex;
	}
	else if (iopt == 5)
	{
		matmtrx.resize(6);
		for (size_t i3 = 0; i3 < matmtrx.size(); i3++)
		{
			matmtrx[i3].resize(6);
		}
		matmtrx[0][0] = Kp + mup; matmtrx[0][1] = Kp - mup; matmtrx[0][2] = Iotal; matmtrx[0][3] = 0; matmtrx[0][4] = 0; matmtrx[0][5] = 0;
		matmtrx[1][0] = Kp - mup; matmtrx[1][1] = Kp + mup; matmtrx[1][2] = Iotal; matmtrx[1][3] = 0; matmtrx[1][4] = 0; matmtrx[1][5] = 0;
		matmtrx[2][0] = Iotal;    matmtrx[2][1] = Iotal;    matmtrx[2][2] = Sital; matmtrx[2][3] = 0; matmtrx[2][4] = 0; matmtrx[2][5] = 0;
		matmtrx[3][0] = 0; matmtrx[3][1] = 0; matmtrx[3][2] = 0; matmtrx[3][3] = 2 * mul; matmtrx[3][4] = 0;        matmtrx[3][5] = 0;
		matmtrx[4][0] = 0; matmtrx[4][1] = 0; matmtrx[4][2] = 0; matmtrx[4][3] = 0;       matmtrx[4][4] = 2 * mul;  matmtrx[4][5] = 0;
		matmtrx[5][0] = 0; matmtrx[5][1] = 0; matmtrx[5][2] = 0; matmtrx[5][3] = 0;       matmtrx[5][4] = 0;        matmtrx[5][5] = 2 * mup;
	}
	else if (iopt == 6)    //LuCunYou
	{
		/*matmtrx.resize(6);
		for (size_t i3 = 0; i3 < 3; i3++)
		{
			matmtrx[i3].resize(6);
		}
		matmtrx[0][0] = k12 + mu12; matmtrx[0][1] = k12 - mu12; matmtrx[0][2] = 1; matmtrx[0][3] = 0; matmtrx[0][4] = 0; matmtrx[0][5] = 0;
		matmtrx[1][0] = k12 - mu12; matmtrx[1][1] = k12 + mu12; matmtrx[1][2] = 1; matmtrx[1][3] = 0; matmtrx[1][4] = 0; matmtrx[1][5] = 0;
		matmtrx[2][0] = 1;    matmtrx[2][1] = 1;    matmtrx[2][2] = n; matmtrx[2][3] = 0; matmtrx[2][4] = 0; matmtrx[2][5] = 0;
		matmtrx[3][0] = 0; matmtrx[3][1] = 0; matmtrx[3][2] = 0; matmtrx[3][3] = 2 * G;   matmtrx[3][4] = 0;      matmtrx[3][5] = 0;
		matmtrx[4][0] = 0; matmtrx[4][1] = 0; matmtrx[4][2] = 0; matmtrx[4][3] = 0;       matmtrx[4][4] = 2 * G;  matmtrx[4][5] = 0;
		matmtrx[5][0] = 0; matmtrx[5][1] = 0; matmtrx[5][2] = 0; matmtrx[5][3] = 0;       matmtrx[5][4] = 0;      matmtrx[5][5] = 2 * mu12;*/
	}
	else if (iopt == 7)
	{
		/*E1 = elprop[0]; E2 = elprop[1]; E3 = elprop[2];
		Nu12 = elprop[3]; Nu13 = elprop[4]; Nu23 = elprop[5];
		G12 = elprop[6]; G13 = elprop[7]; G23 = elprop[8];*/
	/*	vector< vector<double> > FlexiMatrix(6, vector<double>(6, 0));
		matmtrx.resize(6);
		for (size_t i3 = 0; i3 < 3; i3++)
		{
			matmtrx[i3].resize(6);
		}
		FlexiMatrix[0][0] = 1 / E1;     FlexiMatrix[0][1] = -Nu12 / E2; FlexiMatrix[0][2] = -Nu13 / E3; FlexiMatrix[0][3] = 0; FlexiMatrix[0][4] = 0; FlexiMatrix[0][5] = 0;
		FlexiMatrix[1][0] = -Nu12 / E1; FlexiMatrix[1][1] = 1 / E2;     FlexiMatrix[1][2] = -Nu23 / E3; FlexiMatrix[1][3] = 0; FlexiMatrix[1][4] = 0; FlexiMatrix[1][5] = 0;
		FlexiMatrix[2][0] = -Nu13 / E1; FlexiMatrix[2][1] = -Nu23 / E2; FlexiMatrix[2][2] = 1 / E3;     FlexiMatrix[2][3] = 0; FlexiMatrix[2][4] = 0; FlexiMatrix[2][5] = 0;
		FlexiMatrix[3][0] = 0; FlexiMatrix[3][1] = 0; FlexiMatrix[3][2] = 0; FlexiMatrix[3][3] = 1 / G12; FlexiMatrix[3][4] = 0;        FlexiMatrix[3][5] = 0;
		FlexiMatrix[4][0] = 0; FlexiMatrix[4][1] = 0; FlexiMatrix[4][2] = 0; FlexiMatrix[4][3] = 0;       FlexiMatrix[4][4] = 1 / G13;  FlexiMatrix[4][5] = 0;
		FlexiMatrix[5][0] = 0; FlexiMatrix[5][1] = 0; FlexiMatrix[5][2] = 0; FlexiMatrix[5][3] = 0;       FlexiMatrix[5][4] = 0;        FlexiMatrix[5][5] = 1 / G23;
		matmtrx= vectors_inversion(FlexiMatrix);*/
	}
	else if (iopt == 0)
	{
		double midex = E / ((1 + mu) * (1 - 2 * mu));
		matmtrx.resize(6);
		for (size_t i3 = 0; i3 < matmtrx.size(); i3++)
		{
			matmtrx[i3].resize(6);
		}
		matmtrx[0][0] = (1 - mu) * midex;  matmtrx[0][1] = mu * midex;       matmtrx[0][2] = mu * midex;        matmtrx[0][3] = 0 * midex; matmtrx[0][4] = 0 * midex; matmtrx[0][5] = 0 * midex;
		matmtrx[1][0] = mu * midex;        matmtrx[1][1] = (1 - mu) * midex; matmtrx[1][2] = mu * midex;        matmtrx[1][3] = 0 * midex; matmtrx[1][4] = 0 * midex; matmtrx[1][5] = 0 * midex;
		matmtrx[2][0] = mu * midex;        matmtrx[2][1] = mu * midex;       matmtrx[2][2] = (1 - mu) * midex;  matmtrx[2][3] = 0 * midex; matmtrx[2][4] = 0 * midex; matmtrx[2][5] = 0 * midex;
		matmtrx[3][0] = 0 * midex; matmtrx[3][1] = 0 * midex; matmtrx[3][2] = 0 * midex; matmtrx[3][3] = (1 - 2 * mu)/2 * midex; matmtrx[3][4] = 0 * midex;               matmtrx[3][5] = 0 * midex;
		matmtrx[4][0] = 0 * midex; matmtrx[4][1] = 0 * midex; matmtrx[4][2] = 0 * midex; matmtrx[4][3] = 0 * midex;              matmtrx[4][4] = (1 - 2 * mu)/2 * midex;  matmtrx[4][5] = 0 * midex;
		matmtrx[5][0] = 0 * midex; matmtrx[5][1] = 0 * midex; matmtrx[5][2] = 0 * midex; matmtrx[5][3] = 0 * midex;              matmtrx[5][4] = 0 * midex;               matmtrx[5][5] = (1 - 2 * mu)/2 * midex;
	}
	else if (iopt == 0.1)
	{
	    double D1111 = 13.7e9; 
		double D1122 = 4.25e9; 
		double D2222 = 13.7e9; 
		double D1133 = 5.49e9; 
		double D2233 = 5.49e9; 
		double D3333 = 17.2e9; 
		double D1212 = 3.96e9;
		double D1313 = 3.96e9; 
		double D2323 = 4.725e9;
	    matmtrx.resize(6);
		for (size_t i3 = 0; i3 < matmtrx.size(); i3++)
		{
			matmtrx[i3].resize(6);
		}
		matmtrx[0][0] = D1111; matmtrx[0][1] = D1122; matmtrx[0][2] = D1133; matmtrx[0][3] = 0; matmtrx[0][4] = 0; matmtrx[0][5] = 0;
		matmtrx[1][0] = D1122; matmtrx[1][1] = D2222; matmtrx[1][2] = D2233; matmtrx[1][3] = 0; matmtrx[1][4] = 0; matmtrx[1][5] = 0;
		matmtrx[2][0] = D1133; matmtrx[2][1] = D2233; matmtrx[2][2] = D3333; matmtrx[2][3] = 0; matmtrx[2][4] = 0; matmtrx[2][5] = 0;
		matmtrx[3][0] = 0; matmtrx[3][1] = 0; matmtrx[3][2] = 0; matmtrx[3][3] = D1212;  matmtrx[3][4] = 0;        matmtrx[3][5] = 0;
		matmtrx[4][0] = 0; matmtrx[4][1] = 0; matmtrx[4][2] = 0; matmtrx[4][3] = 0;      matmtrx[4][4] = D1313;    matmtrx[4][5] = 0;
		matmtrx[5][0] = 0; matmtrx[5][1] = 0; matmtrx[5][2] = 0; matmtrx[5][3] = 0;      matmtrx[5][4] = 0;        matmtrx[5][5] = D2323;
	}
	int asd = 0;
	return matmtrx;
}
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<vector<double>> fekine3d(int nnel, vector<double> dhdx, vector<double> dhdy, vector<double> dhdz)
{
	int ki3= (nnel - 1) * 3 + 3;
	vector<vector<double>> kinmtx(6,vector<double>(ki3,0));
	int i1, i2, i3;
	for (size_t i = 0; i < nnel; i++)
	{
		//int i1, i2, i3;
		i1 = i * 3;
		i2 = i1+1;
		i3 = i2+1;
		kinmtx[0][i1] = dhdx[i];
		kinmtx[1][i2] = dhdy[i];
		kinmtx[2][i3] = dhdz[i];
		kinmtx[3][i2] = (sqrt(2) / 2) * dhdz[i];
		kinmtx[3][i3] = (sqrt(2) / 2) * dhdy[i];
		kinmtx[4][i1] = (sqrt(2) / 2) * dhdz[i];
		kinmtx[4][i3] = (sqrt(2) / 2) * dhdx[i];
		kinmtx[5][i1] = (sqrt(2) / 2) * dhdy[i];
		kinmtx[5][i2] = (sqrt(2) / 2) * dhdx[i];
	}
	return kinmtx;
}
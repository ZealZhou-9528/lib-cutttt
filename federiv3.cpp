#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void federiv3(vector<double> &dhdx, vector<double> &dhdy, vector<double> &dhdz, int nnel, vector<double> dhdr, vector<double> dhds, vector<double> dhdt, vector<vector<double>> invjacob)
{
	for (size_t i = 0; i < nnel; i++)
	{
		dhdx[i] = invjacob[0][0] * dhdr[i] + invjacob[0][1] * dhds[i] + invjacob[0][2] * dhdt[i];
		dhdy[i] = invjacob[1][0] * dhdr[i] + invjacob[1][1] * dhds[i] + invjacob[1][2] * dhdt[i];
		dhdz[i] = invjacob[2][0] * dhdr[i] + invjacob[2][1] * dhds[i] + invjacob[2][2] * dhdt[i];
	}
}
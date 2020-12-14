#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void feisos8(vector<double> &shapes4, vector<double>& dhdrs4, vector<double>& dhdss4, vector<double>& dhdts4, int nnel, vector<vector<double>> Lpoint)
{
	shapes4[0] = Lpoint[0][0];
	shapes4[1] = Lpoint[0][1];
	shapes4[2] = Lpoint[0][2];
	shapes4[3] = 1 - Lpoint[0][0] - Lpoint[0][1] - Lpoint[0][2];
	//
	dhdrs4[0] = 1;
	dhdrs4[1] = 0;
	dhdrs4[2] = 0;
	dhdrs4[3] = -1;
	//
	dhdss4[0] = 0;
	dhdss4[1] = 1;
	dhdss4[2] = 0;
	dhdss4[3] = -1;
	//
	dhdts4[0] = 0;
	dhdts4[1] = 0;
	dhdts4[2] = 1;
	dhdts4[3] = -1;
	int a = nnel;
}
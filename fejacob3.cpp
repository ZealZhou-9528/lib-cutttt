#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<vector<double>> fejacob3(int nnel, vector<double> dhdr, vector<double> dhds, vector<double> dhdt, vector<double> xcoord, vector<double> ycoord, vector<double> zcoord)
{
	vector<vector<double>> jacob3(3, vector<double>(3, 0));
	for (size_t i = 0; i < nnel; i++)
	{
		jacob3[0][0] = jacob3[0][0] + dhdr[i] * xcoord[i];
		jacob3[0][1] = jacob3[0][1] + dhdr[i] * ycoord[i];
		jacob3[0][2] = jacob3[0][2] + dhdr[i] * zcoord[i];
		//
		jacob3[1][0] = jacob3[1][0] + dhds[i] * xcoord[i];
		jacob3[1][1] = jacob3[1][1] + dhds[i] * ycoord[i];
		jacob3[1][2] = jacob3[1][2] + dhds[i] * zcoord[i];
		//
		jacob3[2][0] = jacob3[2][0] + dhdt[i] * xcoord[i];
		jacob3[2][1] = jacob3[2][1] + dhdt[i] * ycoord[i];
		jacob3[2][2] = jacob3[2][2] + dhdt[i] * zcoord[i];
	}
	return jacob3;
	int a = 0;
}
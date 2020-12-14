#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void feglqd4(vector<vector<double>> &point, vector<double> &weight,int N)
{
	if (N == 1)
	{
		vector<double> pointN1(4,0.25);
		point.push_back(pointN1);
		//double wei = 1.0 / 6;
		weight.push_back(1.0 / 6);
		pointN1.clear();
	}
	else if (N == 4)
	{
		double a = 0.58541020;
		double b = 0.13819660;
		vector<double> pointN41(4, 0);
		vector<double> pointN42(4, 0);
		vector<double> pointN43(4, 0);
		vector<double> pointN44(4, 0);
		pointN41[0] = a; pointN41[1] = b; pointN41[2] = b; pointN41[3] = b;
		pointN42[0] = b; pointN42[1] = a; pointN42[2] = b; pointN42[3] = b;
		pointN43[0] = b; pointN43[1] = b; pointN43[2] = a; pointN43[3] = b;
		pointN44[0] = b; pointN44[1] = b; pointN44[2] = b; pointN44[3] = a;
		point.push_back(pointN41);
		weight.push_back(0.25); weight.push_back(0.25); weight.push_back(0.25); weight.push_back(0.25);
		pointN41.clear(); pointN42.clear(); pointN43.clear(); pointN44.clear();
	}
}
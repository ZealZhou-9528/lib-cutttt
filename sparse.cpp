#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
vector<vector<double>> ternary_sparse(vector<int> row,vector<int> col, vector<double>val, int m, int n)
{
	//vector<int> row1, col1;
	//row1 = row, col1= col;
	//sort(row1.begin(), row1.end());
	//row1.erase(unique(row1.begin(), row1.end()), row1.end());
	//sort(col1.begin(), col1.end());
	//col1.erase(unique(col1.begin(), col1.end()), col1.end());
	vector<vector<double>> sp (val.size(), vector<double>(3, 0));
	//vector<double> spr;
	//vector<vector<vector<double>>> sp(m);
	//vector<Triple> ss;
	for (size_t i = 0; i < val.size(); i++)
	{
		for (size_t j = 0; j < i; j++)
		{
			if (sp[j][0] == row[i] && sp[j][1] == col[i])
			{
				sp[i][2] = sp[i][2] + val[i];
				break;
			}
			if (j==i-1)
			{
				sp[i][2] = val[i];
			}
		}
		
		sp[i][0] = row[i];
		sp[i][1] = col[i];
		// if (true)
		//{

		//}
		//sp[i][2] = sp[i][2] + val[i];
	}
	//else
	//{
	//	cout << " Sparse matrix construction error" << endl;
	//}
	return sp;
}
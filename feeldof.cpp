#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> feeldof(vector<int> nd, int nnel, int ndof)
{
	vector<int> index(nnel * ndof, 0);
	int k = 0;
	for (size_t i = 0; i < nnel; i++)
	{
		int start = (nd[i] - 1) * ndof;
		for (size_t j = 0; j < ndof; j++)
		{
			index[k] = start + j+ ndof;
			k = k + 1;
		}
		
	}
	return index;
}
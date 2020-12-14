#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> vectors_setdiff(vector<int> v1, vector<int> v2)    //返回在v1中却不在v2中的数
{
	vector<int> v;
	int outpd = 0;
	for (int i = 0; i < v1.size(); i++)
	{
		for (int i1 = 0; i1 < v2.size(); i1++)
		{
			if (v1[i] != v2[i1])
			{
				outpd = outpd + 1;
			}
		}
		if (outpd == v2.size())
		{
			v.push_back(v1[i]);
		}
		outpd = 0;
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	return v;
}
/////////////////////////////////////////////////合并
vector<vector<double>> vectors_1combine(vector<double> v1, vector<double> v2)
{
	vector<vector<double>> v3(v1.size(), vector<double>(2, 0));
	if (v1.size()==v2.size())
	{
		for (size_t i = 0; i < v1.size(); i++)
		{
			v3[i][0] = v1[i];
			v3[i][1] = v2[i];
		}
		return v3;
	}
	else
	{
		cout << "Matrix error"<<endl;
		return v3;
	}
}
/////////////////////////////////////////////////稀疏矩阵
vector<vector<double>> vector_sparse(vector<int> row, vector<int> col, vector<double>val, int m, int n)
{
	vector<vector<double>> sp(m, vector<double>(n, 0));
	for (size_t i = 0; i < row.size(); i++)
	{
		sp[row[i]][col[i]] = sp[row[i]][col[i]] + val[i];
	}
	return sp;
}
/////////////////////////////////////////////////
vector<double> vectors_1plus(vector<double> v1, vector<double> v2)
{
	vector<double> v(v1.size(),0);
	if (v1.size()!=v2.size())
	{
		cout << "Matrix error" << endl;
		return v;
	}
	else	{
		for (size_t i = 0; i < v1.size(); i++)
		{
			v[i] = v1[i] + v2[i];
		}
		return v;
	}
}
/////////////////////////////////////////////////
vector<vector<double>> vectors_2plus(vector<vector<double>> v1, vector<vector<double>> v2)
{
	vector<vector<double>> v(v1.size(), vector<double>(v1[0].size(),0));
	if (v1.size() != v2.size() || v1[0].size() != v2[0].size())
	{
		cout << "Matrix error" << endl;
		return v;
	}
	else
	{
		for (size_t i = 0; i < v1.size(); i++)
		{
			for (size_t j = 0; j < v1[i].size(); j++)
			{
				v[i][j] = v1[i][j] + v2[i][j];
			}
		}
		return v;
	}
}
////////////////////////////////////////////////////////////////
vector<double> vectors_plus_1number(vector<double> a, double b)
{
	for (size_t i = 0; i < a.size(); i++)
	{
		a[i] = a[i] + b;
	}
	return a;
}
////////////////////////////////////////////////////////////////
vector<vector<double>> vectors_plus_2number(vector<vector<double>> a, double b)
{
	for (size_t i = 0; i < a.size(); i++)
	{
		for (size_t j = 0; j < a[i].size(); j++)
		{
			a[i][j] = a[i][j] + b;
		}
	}
	return a;
}
/////////////////////////////////////////////////
vector<double> vectors_1subtract(vector<double> v1, vector<double> v2)
{
	vector<double> v(v1.size(), 0);
	if (v1.size() != v2.size())
	{
		cout << "Matrix error" << endl;
		return v;
	}
	else
	{
		for (size_t i = 0; i < v1.size(); i++)
		{
			v[i] = v1[i] - v2[i];
		}
		return v;
	}
}
/////////////////////////////////////////////////
vector<vector<double>> vectors_2subtract(vector<vector<double>> v1, vector<vector<double>> v2)
{
	vector<vector<double>> v(v1.size(), vector<double>(v1[0].size(), 0));
	if (v1.size() != v2.size() || v1[0].size() != v2[0].size())
	{
		cout << "Matrix error" << endl;
		return v;
	}
	else
	{
		for (size_t i = 0; i < v1.size(); i++)
		{
			for (size_t j = 0; j < v1[i].size(); j++)
			{
				v[i][j] = v1[i][j] - v2[i][j];
			}
		}
		return v;
	}
}
////////////////////////////////////////////////////////////////
vector<double> vectors_subtract_1number(vector<double> a, double b)
{
	for (size_t i = 0; i < a.size(); i++)
	{
		a[i] = a[i] - b;
	}
	return a;
}
////////////////////////////////////////////////////////////////
vector<vector<double>> vectors_subtract_2number(vector<vector<double>> a, double b)
{
	for (size_t i = 0; i < a.size(); i++)
	{
		for (size_t j = 0; j < a[i].size(); j++)
		{
			a[i][j] = a[i][j] - b;
		}
	}
	return a;
}
/////////////////////////////////////////////////
vector<int> vectors_intersection(vector<int> v1, vector<int> v2)    //求v1和v2的交集
{
	vector<int> v;
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v));//求交集 
	return v;
}
//////////////////////////////////////////////////矩阵转置
vector<vector<double>> vectors_Transpose(vector<vector<double>> a)
{
	vector<vector<double>> b(a[0].size(), vector<double>(a.size(), 0));
	for (size_t j = 0; j < a[0].size(); j++)
	{
		for (size_t i = 0; i < a.size(); i++)
		{
			b[j][i] = a[i][j];
		}
	}
	return b;
}
//////////////////////////////////////////////////reshape
vector<vector<double>> vectors_reshape(vector<double> Resdisp, int m, int n)
{
	vector<vector<double>> d(m, vector<double>(n, 0));
	for (size_t i = 0; i < m; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			d[i][j] = Resdisp[j*m+i];
		}
	}
	return d;
}
//////////////////////////////////////////////////
vector<vector<double>> vectors_multiply(vector<vector<double>> a, vector<vector<double>> b)
{
	//double adc=0;
	vector<vector<double>> c(a.size(), vector<double>(b[0].size(), 0));
	if (a[0].size() == b.size())
	{
		//vector<vector<double>> c(a.size(), vector<double>(b[0].size(), 0));
		for (size_t i = 0; i < a.size(); i++)
		{
			for (size_t j = 0; j < b[0].size(); j++)
			{
				//adc = 0;
				for (size_t k = 0; k < b.size(); k++)
				{
					c[i][j] = c[i][j] + a[i][k] * b[k][j];
				}
			}
		}
	}
	else
	{
		cout << "error:Wrong input matrix" << endl;
	}
	return c;
}
////////////////////////////////////////////////////////////////
vector<vector<double>> vectors_multiply_2number(vector<vector<double>> a, double b)
{
	for (size_t i = 0; i < a.size(); i++)
	{
		for (size_t j = 0; j < a[i].size(); j++)
		{
			a[i][j] = a[i][j] * b;
		}
	}
	return a;
}
////////////////////////////////////////////////////////////////
vector<double> vectors_multiply_1number(vector<double> a, double b)
{
	for (size_t i = 0; i < a.size(); i++)
	{
			a[i] = a[i] * b;
	}
	return a;
}
////////////////////////////////////////////////////////////////矩阵的逆
vector<vector<double>> vectors_inversion(vector<vector<double>> a)
{
	int n = a.size();
	vector<vector<double>> vec(n, vector<double>(n, 0));
	//for (int i = 0; i < n; i++)
	//	vec[i].resize(n);
	//int* is = new int[n];
	//int* js = new int[n];
	vector<int> is(n);
	vector<int> js(n);
	int i, j, k;
	double d, p;
	for (k = 0; k < n; k++)
	{
		d = 0.0;
		for (i = k; i <= n - 1; i++)
		{
			for (j = k; j <= n - 1; j++)
			{
				p = fabs(a[i][j]);
				if (p > d)
				{
					d = p; is[k] = i; js[k] = j;
				}
			}
		}
		if (0.0 == d)
		{
			//free(is); free(js);
			return vec;
		}
		if (is[k] != k)
		{
			for (j = 0; j <= n - 1; j++)
			{
				p = a[k][j];
				a[k][j] = a[is[k]][j];
				a[is[k]][j] = p;
			}
		}
		if (js[k] != k)
		{
			for (i = 0; i <= n - 1; i++)
			{
				p = a[i][k];
				a[i][k] = a[i][js[k]];
				a[i][js[k]] = p;
			}
		}
		a[k][k] = 1.0 / a[k][k];
		for (j = 0; j <= n - 1; j++)
		{
			if (j != k)
			{
				a[k][j] *= a[k][k];
			}
		}
		for (i = 0; i <= n - 1; i++)
		{
			if (i != k)
			{
				for (j = 0; j <= n - 1; j++)
				{
					if (j != k)
					{
						a[i][j] -= a[i][k] * a[k][j];
					}
				}
			}
		}
		for (i = 0; i <= n - 1; i++)
		{
			if (i != k)
			{
				a[i][k] = -a[i][k] * a[k][k];
			}
		}
	}
	for (k = n - 1; k >= 0; k--)
	{
		if (js[k] != k)
			for (j = 0; j <= n - 1; j++)
			{
				p = a[k][j];
				a[k][j] = a[js[k]][j];
				a[js[k]][j] = p;
			}
		if (is[k] != k)
			for (i = 0; i <= n - 1; i++)
			{
				p = a[i][k];
				a[i][k] = a[i][is[k]];
				a[i][is[k]] = p;
			}
	}
	//free(is); free(js);
	vec = a;
	return vec;
}
#include <iostream>
#include <vector>
using namespace std;
// 定义矩阵阶数
//#define N 3
//double CalculateDetMatr(vector< vector<double> > matrix, int rank);  //求取矩阵行列式，rank为矩阵的阶数 
void GetSubMatrix(vector< vector<double> > &matrix, int i, int j);    //矩阵matrix的第i行第j列的代数余子式矩阵
double vector_det(vector< vector<double> > matrix)
{
	int rank = matrix.size();
	double DetValue = 0;
	vector< vector<double> > temp;
	if (rank == 1)
	{
		return matrix[0][0];
	}
	if (rank == 2)
	{
		DetValue = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
		return DetValue;
	}
	else
	{
		int coe = 1;
		// 每个矩阵都按第一行展开，所以下面的循环，当i为奇数时，奇数和
		// 1相加为偶数所以系数为1；当i为偶数时，偶数加1为奇数系数为－1；
		for (int i = 1; i <= rank; i++)
		{
			if (i % 2 != 0)
			{
				coe = 1;
			}
			else
			{
				coe = -1;
			}
			temp = matrix;
			double temp2 = temp[0][i - 1];   // 保存系数
			// 计算代数余子式矩阵
			GetSubMatrix(temp, 1, i);
			DetValue += coe * temp2 * vector_det(temp);
		}
		return DetValue;
	}
}
/************************************************************************/
/*               求取矩阵matrix的第i行第j列的代数余子式矩阵             */
/************************************************************************/
void GetSubMatrix(vector< vector<double> > &matrix, int i, int j)
{
	vector< vector<double> >::iterator it1;   //vector<int>::iterator是定义向量迭代器  使用iterator和使用下标效果是一样的。
	vector<double>::iterator it2;             //迭代器类型可使用解引用操作符（*操作符）来访问迭代器所指向r元素：假设iter指向vector对象ivec的第一个元素，那么*iter和ivec[0]就是指向同一个元素。
	int idx;
	for (idx = 1, it1 = matrix.begin(); idx < i && it1 != matrix.end(); idx++, it1++)
	{
	}
	if (it1 == matrix.end())
	{
		cout << "Matrix error" << endl;
		return;
	}
	else
	{
		matrix.erase(it1);
	}
	for (it1 = matrix.begin(); it1 != matrix.end(); it1++)
	{
		for (idx = 1, it2 = it1->begin(); idx < j && it2 != it1->end(); idx++, it2++)
		{
		}
		if (it2 == it1->end())
		{
			cout << "Matrix error" << endl;
			return;
		}
		else
		{
			it1->erase(it2);
		}
	}
}
/************************************************************************/
/*              求取矩阵行列式，rank为矩阵的阶数                        */
/************************************************************************/
//double CalculateDetMatr(vector< vector<double> > matrix, int rank)
//{
//	double DetValue = 0;
//	vector< vector<double> > temp;
//	if (rank == 1)
//	{
//		return matrix[0][0];
//	}
//	if (rank == 2)
//	{
//		DetValue = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
//		return DetValue;
//	}
//	else
//	{
//		int coe = 1;
//		// 每个矩阵都按第一行展开，所以下面的循环，当i为奇数时，奇数和
//		// 1相加为偶数所以系数为1；当i为偶数时，偶数加1为奇数系数为－1；
//		for (int i = 1; i <= rank; i++)
//		{
//			if (i % 2 != 0)
//			{
//				coe = 1;
//			}
//			else
//			{
//				coe = -1;
//			}
//			temp = matrix;
//			double temp2 = temp[0][i - 1];   // 保存系数
//			// 计算代数余子式矩阵
//			GetSubMatrix(temp, 1, i);
//			DetValue += coe * temp2 * CalculateDetMatr(temp, rank - 1);
//		}
//		return DetValue;
//	}
//}
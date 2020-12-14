#include <iostream>
#include <vector>
using namespace std;
// ����������
//#define N 3
//double CalculateDetMatr(vector< vector<double> > matrix, int rank);  //��ȡ��������ʽ��rankΪ����Ľ��� 
void GetSubMatrix(vector< vector<double> > &matrix, int i, int j);    //����matrix�ĵ�i�е�j�еĴ�������ʽ����
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
		// ÿ�����󶼰���һ��չ�������������ѭ������iΪ����ʱ��������
		// 1���Ϊż������ϵ��Ϊ1����iΪż��ʱ��ż����1Ϊ����ϵ��Ϊ��1��
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
			double temp2 = temp[0][i - 1];   // ����ϵ��
			// �����������ʽ����
			GetSubMatrix(temp, 1, i);
			DetValue += coe * temp2 * vector_det(temp);
		}
		return DetValue;
	}
}
/************************************************************************/
/*               ��ȡ����matrix�ĵ�i�е�j�еĴ�������ʽ����             */
/************************************************************************/
void GetSubMatrix(vector< vector<double> > &matrix, int i, int j)
{
	vector< vector<double> >::iterator it1;   //vector<int>::iterator�Ƕ�������������  ʹ��iterator��ʹ���±�Ч����һ���ġ�
	vector<double>::iterator it2;             //���������Ϳ�ʹ�ý����ò�������*�������������ʵ�������ָ��rԪ�أ�����iterָ��vector����ivec�ĵ�һ��Ԫ�أ���ô*iter��ivec[0]����ָ��ͬһ��Ԫ�ء�
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
/*              ��ȡ��������ʽ��rankΪ����Ľ���                        */
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
//		// ÿ�����󶼰���һ��չ�������������ѭ������iΪ����ʱ��������
//		// 1���Ϊż������ϵ��Ϊ1����iΪż��ʱ��ż����1Ϊ����ϵ��Ϊ��1��
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
//			double temp2 = temp[0][i - 1];   // ����ϵ��
//			// �����������ʽ����
//			GetSubMatrix(temp, 1, i);
//			DetValue += coe * temp2 * CalculateDetMatr(temp, rank - 1);
//		}
//		return DetValue;
//	}
//}
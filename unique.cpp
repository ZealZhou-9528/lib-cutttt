#include <iostream>
using namespace std;
void unique(int** AEN, int** AENu) 
{
	int AENn = _msize(AEN) / sizeof(int);   //行数
	int AENw = AENn;   //新数组行数，每当有重复行，减一

	for (int i = 0; i < AENn; i++)
	{
		for (int j = i + 1; j < AENn; j++)
		{
			if (AEN[i][0] == AEN[j][0] && AEN[i][1] == AEN[j][1])
			{
				AEN[j][0] = -1;// , AEN[j][1] = -1;
				if (AEN[i][0] != -1)
				{
					AENw = AENw - 1;
				}
			}
		}
	}
	int** AENnew = new int* [AENw];       //定义EdgeNodes  496*2
	for (int i = 0; i < AENw; i++)
		AENnew[i] = new int[2]();
	int AENwx = 0;
	for (int i = 0; i < AENn; i++)
	{
		if (AEN[i][0] != -1)
		{
			AENnew[AENwx][0] = AEN[i][0];
			AENnew[AENwx][1] = AEN[i][1];
			AENwx = AENwx + 1;
		}
	}

	for (int i = 0; i < AENw - 1; ++i)
		for (int j = 0; j < AENw - 1 - i; ++j)
			if (AENnew[j][0] > AENnew[j + 1][0])
			{
				swap(AENnew[j][0], AENnew[j + 1][0]);
				swap(AENnew[j][1], AENnew[j + 1][1]);
			}

	for (int i = 0; i < AENw - 1; ++i)
		for (int j = 0; j < AENw - 1 - i; ++j)
			if (AENnew[j][0] == AENnew[j + 1][0])
			{
				if (AENnew[j][1] > AENnew[j + 1][1])
				{
					swap(AENnew[j][0], AENnew[j + 1][0]);
					swap(AENnew[j][1], AENnew[j + 1][1]);
				}
			}

	for (int i = 0; i < AENw; i++)
	{
		cout << AENnew[i][0] << " " << AENnew[i][1] << endl;
	}
	for (int i = 0; i < AENw; i++)
		delete[]AENnew[i];
	delete[]AENnew;     //删除AENnew数组
}
#include <iostream>
#include <vector>
using namespace std;
void ReSameRows(int** NewEleNode, vector< vector<int> > &CutEdgNodes, int Mode)
{
	
	int Nrow = _msize(NewEleNode) / (2*sizeof(int));   //行数
	int Ncol = 2;//_msize(*NewEleNode) / (sizeof(int));   //列数    int Ncol = _msize(*NewEleNode) / (sizeof(int));
	int** JuNum = new int* [Nrow];       //定义JuNum  123*2
	for (int i = 0; i < Nrow; i++)
		JuNum[i] = new int[3]();
	if (Ncol == 3)
	{
		for (int i1 = 0; i1 < Nrow; i1++)
		{
			JuNum[i1][0] = NewEleNode[i1][0] + NewEleNode[i1][1] + NewEleNode[i1][2];
			JuNum[i1][1] = NewEleNode[i1][0] * NewEleNode[i1][1] * NewEleNode[i1][2];
			JuNum[i1][2] = NewEleNode[i1][0] * NewEleNode[i1][0] + NewEleNode[i1][1]* NewEleNode[i1][1] + NewEleNode[i1][2] * NewEleNode[i1][2];
		}
	}
	else if (Ncol == 2)
	{
		for (int i2 = 0; i2 < Nrow; i2++)
		{
			JuNum[i2][0] = NewEleNode[i2][0] + NewEleNode[i2][1];
			JuNum[i2][1] = NewEleNode[i2][0] * NewEleNode[i2][1];
			JuNum[i2][2] = NewEleNode[i2][0] * NewEleNode[i2][0] + NewEleNode[i2][1] * NewEleNode[i2][1];
		}
	}
	if (Mode == 1)
	{
		int** JuNumA = new int* [Nrow];       //定义EdgeNodes  496*2
		for (int i = 0; i < Nrow; i++)
			JuNumA[i] = new int[3]();
		for (int i1 = 0; i1 < Nrow; i1++)     //JuNumA =JuNum
		{
			for (int i2 = 0; i2 < 3; i2++)
			{
				JuNumA[i1][i2] = JuNum[i1][i2];
			}

			int c = 1, CC = 0;
			int JuNumB[3] = { 0 };
			for (int ju = 0; ju < Nrow; ju++)         //JuNumB = JuNum(jn,:)
			{
				for (int i4 = 0; i4 < 3; i4++)
				{
					JuNumB[i4] = JuNum[ju][i4];
				}
				for (int i6 = 0; i6 < Nrow; i6++)     //JuNumA =JuNum
				{
					for (int i2 = 0; i2 < 3; i2++)
					{
						JuNumA[i6][i2] = JuNum[i6][i2];
					}
				}
				for (int i5 = 0; i5 < 3; i5++)        //JuNumA(jn,:) = 0
				{
					JuNumA[ju][i5] = 0;
				}
			}
			//  [AA,BB] = ismember(JuNumB,JuNumA,'rows');  //因为没有用过，以后再写
			//if BB ~= 0
		    //CC(c) = BB;
			//c = c + 1;
		}
		for (int i = 0; i < Nrow; i++)
			delete[]JuNumA[i];
		delete[]JuNumA;     //删除JuNumA数组
		
	}
	else
	{
		int** JuNumA = new int* [Nrow];       //定义EdgeNodes  496*2
		for (int i = 0; i < Nrow; i++)
			JuNumA[i] = new int[3]();
		for (int i1 = 0; i1 < Nrow; i1++)     //JuNumA =JuNum
		{
			for (int i2 = 0; i2 < 3; i2++)
			{
				JuNumA[i1][i2] = JuNum[i1][i2];
			}
		}
		// JudgeNum = unique(JuNumA,'rows');
		int JNw = Nrow;   //新数组行数，每当有重复行，减一
		for (int i = 0; i < Nrow; i++)
		{
			for (int j = i + 1; j < Nrow; j++)   //将重复的数组换成-1做标识
			{
				if (JuNumA[i][0] == JuNumA[j][0] && JuNumA[i][1] == JuNumA[j][1]&& JuNumA[i][2] == JuNumA[j][2])
				{
					JuNumA[j][0] = -1;// , AEN[j][1] = -1;
					if (JuNumA[i][0] != -1)
					{
						JNw = JNw - 1;
					}
				}
			}
		}
		int** JNnew = new int* [JNw];       //定义JNnew，容量为不重复的JuNumA  94*2
		for (int i = 0; i < JNw; i++)
			JNnew[i] = new int[3]();
		int JNwx = 0;
		for (int i = 0; i < Nrow; i++)      //将JuNumA不重复的项赋给JNnew
		{
			if (JuNumA[i][0] != -1)
			{
				JNnew[JNwx][0] = JuNumA[i][0];
				JNnew[JNwx][1] = JuNumA[i][1];
				JNnew[JNwx][2] = JuNumA[i][2];

				JNwx = JNwx + 1;
			}
		}
		for (int i = 0; i < JNw - 1; ++i)               //对第一列排序
			for (int j = 0; j < JNw - 1 - i; ++j)
				if (JNnew[j][0] > JNnew[j + 1][0])
				{
					swap(JNnew[j][0], JNnew[j + 1][0]);
					swap(JNnew[j][1], JNnew[j + 1][1]);
					swap(JNnew[j][2], JNnew[j + 1][2]);
				}
		for (int i = 0; i < JNw - 1; ++i)               //对第二列排序  
			for (int j = 0; j < JNw - 1 - i; ++j)
				if (JNnew[j][0] == JNnew[j + 1][0])
				{
					if (JNnew[j][1] > JNnew[j + 1][1])
					{
						swap(JNnew[j][0], JNnew[j + 1][0]);
						swap(JNnew[j][1], JNnew[j + 1][1]);
						swap(JNnew[j][2], JNnew[j + 1][2]);
					}
				}
		for (int i = 0; i < JNw - 1; ++i)               //对第三列排序  
			for (int j = 0; j < JNw - 1 - i; ++j)
				if (JNnew[j][0] == JNnew[j + 1][0])
				{
					if (JNnew[j][1] == JNnew[j + 1][1])
					{
						if (JNnew[j][2] > JNnew[j + 1][2])
						{
							swap(JNnew[j][0], JNnew[j + 1][0]);
							swap(JNnew[j][1], JNnew[j + 1][1]);
							swap(JNnew[j][2], JNnew[j + 1][2]);
						}
					}
				}
		// [IndexA,IndexB] = ismember(JudgeNum,JuNumA,'rows');
		int* IndexA = new int[JNw]();
		int* IndexB = new int[JNw]();
		for (int i = 0; i < JNw; i++)
		{
			for (int i1 = 0; i1 < Nrow; i1++)
			{
				if (JNnew[i][0] == JuNum[i1][0] && JNnew[i][1] == JuNum[i1][1] && JNnew[i][2] == JuNum[i1][2])
				{
					IndexA[i] = 1;
					IndexB[i] = i1;
					break;
				}
			}
		}
		//NewEleNodeAA = NewEleNode(IndexB,:);
		//CENn = JNw;
		vector<int> CENEN(2);
		for (int i = 0; i < JNw; i++)
		{
			CENEN[0] = NewEleNode[IndexB[i]][0];
			CENEN[1] = NewEleNode[IndexB[i]][1];
			CutEdgNodes.push_back(CENEN);//NewEleNode[IndexB[i]][0]
		}



		for (int i = 0; i < JNw; i++)
			delete[]JNnew[i];
		delete[]JNnew;      //删除JNnew数组
		for (int i = 0; i < Nrow; i++)
			delete[]JuNum[i];
		delete[]JuNum;      //删除JuNum数组
		delete[]IndexA;     //删除IndexA数组
		delete[]IndexB;     //删除IndexB数组
	}
}
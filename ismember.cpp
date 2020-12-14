#include <iostream>
using namespace std;
void ismember()
{
	int JNw = 15, Nrow = 17;
	int** JNnew = new int* [JNw];       //定义JNnew，容量为不重复的JuNumA  94*2
	for (int i = 0; i < JNw; i++)
		JNnew[i] = new int[3]();
	int** JuNum = new int* [Nrow];       //定义JuNum  123*2
	for (int i = 0; i < Nrow; i++)
		JuNum[i] = new int[3]();
	JNnew[0][0] = 131, JNnew[0][1] = 250, JNnew[0][2] = 360;      //0
	JNnew[1][0] = 131, JNnew[1][1] = 132, JNnew[1][2] = 125;      //4
	JNnew[2][0] = 152, JNnew[2][1] = 174, JNnew[2][2] = 182;      //3
	JNnew[3][0] = 121, JNnew[3][1] = 187, JNnew[3][2] = 146;      //6
	JNnew[4][0] = 280, JNnew[4][1] = 131, JNnew[4][2] = 131;      //5
	JNnew[5][0] = 247, JNnew[5][1] = 131, JNnew[5][2] = 158;      //8
	JNnew[6][0] = 131, JNnew[6][1] = 131, JNnew[6][2] = 131;      //9
	JNnew[7][0] = 141, JNnew[7][1] = 131, JNnew[7][2] = 131;      //7
	JNnew[8][0] = 163, JNnew[8][1] = 131, JNnew[8][2] = 131;      //10
	JNnew[9][0] = 179, JNnew[9][1] = 131, JNnew[9][2] = 131;////////11
	JNnew[10][0] = 162, JNnew[10][1] = 131, JNnew[10][2] = 131;   //12
	JNnew[11][0] = 155, JNnew[11][1] = 131, JNnew[11][2] = 131;   //15
	JNnew[12][0] = 157, JNnew[12][1] = 131, JNnew[12][2] = 131;   //16
	JNnew[13][0] = 186, JNnew[13][1] = 131, JNnew[13][2] = 131;   //2
	JNnew[14][0] = 193, JNnew[14][1] = 131, JNnew[14][2] = 131;   //1

	JuNum[0][0] = 131, JuNum[0][1] = 250, JuNum[0][2] = 360;//
	JuNum[1][0] = 193, JuNum[1][1] = 131, JuNum[1][2] = 131;//
	JuNum[2][0] = 186, JuNum[2][1] = 131, JuNum[2][2] = 131;//
	JuNum[3][0] = 152, JuNum[3][1] = 174, JuNum[3][2] = 182;//     
	JuNum[4][0] = 131, JuNum[4][1] = 132, JuNum[4][2] = 125;//  
	JuNum[5][0] = 280, JuNum[5][1] = 131, JuNum[5][2] = 131;//
	JuNum[6][0] = 121, JuNum[6][1] = 187, JuNum[6][2] = 146;//
	JuNum[7][0] = 141, JuNum[7][1] = 131, JuNum[7][2] = 131;   //
	JuNum[8][0] = 247, JuNum[8][1] = 131, JuNum[8][2] = 158;   //
	JuNum[9][0] = 131, JuNum[9][1] = 131, JuNum[9][2] = 131;//
	JuNum[10][0] = 163, JuNum[10][1] = 131, JuNum[10][2] = 131;//
	JuNum[11][0] = 179, JuNum[11][1] = 131, JuNum[11][2] = 131;//
	JuNum[12][0] = 162, JuNum[12][1] = 131, JuNum[12][2] = 131;//
	JuNum[13][0] = 131, JuNum[13][1] = 166, JuNum[13][2] = 131;
	JuNum[14][0] = 121, JuNum[14][1] = 187, JuNum[14][2] = 146;
	JuNum[15][0] = 155, JuNum[15][1] = 131, JuNum[15][2] = 131;//
	JuNum[16][0] = 157, JuNum[16][1] = 131, JuNum[16][2] = 131;//
	//JNnew[12][0] = 131, JNnew[12][1] = 131, JNnew[12][2] = 131;
	//JNnew[13][0] = 131, JNnew[13][1] = 131, JNnew[13][2] = 131;
	//JNnew[14][0] = 131, JNnew[14][1] = 131, JNnew[14][2] = 131;



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

	for (int i = 0; i < JNw; i++)
	{
		cout << IndexA[i] << endl;
	}
	cout << endl << endl;
	for (int i = 0; i < JNw; i++)
	{
		cout << IndexB[i] << endl;
	}
	for (int i = 0; i < JNw; i++)
		delete[]JNnew[i];
	delete[]JNnew;     //删除AENnew数组
	for (int i = 0; i < Nrow; i++)
		delete[]JuNum[i];
	delete[]JuNum;     //删除AENnew数组
	delete[]IndexA;     //删除AENnew数组
	delete[]IndexB;     //删除AENnew数组
}
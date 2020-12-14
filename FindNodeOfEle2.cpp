#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iterator>
#include <omp.h>
using namespace std;
void FindNodeOfEle2(int Num, int LinNode[2], vector< vector<int> >& nodes, vector< vector<double> >& gcoord)
{
	omp_set_num_threads(8);
	int LNA = LinNode[0];
	int LNB = LinNode[1];
	vector<int> AA,CC,EdgeEles;

	for (int j = 0; j < 4; j++)
	{
//#pragma omp parallel for
		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i][j] == LNA)
			{AA.push_back(i);}
		}
	}
	for (int j = 0; j < 4; j++)
	{
//#pragma omp parallel for
		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i][j] == LNB)
			{CC.push_back(i);}
		}
	}
	//EdgeEles = intersect(AA,CC);     
	sort(AA.begin(), AA.end());
	sort(CC.begin(), CC.end());
	set_intersection(AA.begin(), AA.end(), CC.begin(), CC.end(), back_inserter(EdgeEles));// inserter(EdgeEles, EdgeEles.begin())
	int row = EdgeEles.size();
	vector< vector<int> > EdgeEleNode(row, vector<int>(4, 0));
	vector< vector<int> > EdgeEleNodeA(row, vector<int>(4, 0));
	vector< vector<int> > EdgeEleNodeB(row, vector<int>(4, 0));
//#pragma omp parallel for
	for (int m = 0; m < EdgeEleNode.size(); m++)
	{ 
		for (int n = 0; n < EdgeEleNode[m].size(); n++)
		{ 
			EdgeEleNode[m][n] = nodes[EdgeEles[m]][n];
			EdgeEleNodeA[m][n] = nodes[EdgeEles[m]][n];
			EdgeEleNodeB[m][n] = nodes[EdgeEles[m]][n];
		}        
	}
	vector<int> RA, CA;
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < EdgeEleNode.size(); i++)
		{
			if (EdgeEleNode[i][j] == LNA)
			{
				RA.push_back(i);
			}
		}
	}
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < EdgeEleNode.size(); i++)
		{
			if (EdgeEleNode[i][j] == LNA)
			{
				CA.push_back(j);
			}
		}
	}
	for (int i = 0; i < RA.size(); i++)
	{
		EdgeEleNodeA[(RA[i])][(CA[i])]=Num;
	}
	vector<int> RB, CB;
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < EdgeEleNode.size(); i++)
		{
			if (EdgeEleNode[i][j] == LNB)
			{
				RB.push_back(i);
			}
		}
	}
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < EdgeEleNode.size(); i++)
		{
			if (EdgeEleNode[i][j] == LNB)
			{
				CB.push_back(j);
			}
		}
	}
//#pragma omp parallel for
	for (int i = 0; i < RB.size(); i++)
	{
		EdgeEleNodeB[(RB[i])][(CB[i])] = Num;
	}
	for (int i = 0; i < EdgeEles.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			nodes[(EdgeEles[i])][j] = EdgeEleNodeA[i][j];
		}
	}
	for (int i = 0; i < EdgeEleNodeB.size(); i++)
	{
		nodes.push_back(EdgeEleNodeB[i]);
	}
}
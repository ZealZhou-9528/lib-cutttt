#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
void BCimposePeriodic(double *Kr, double *Fr, vector<vector<double>> Tmtx, vector<vector<double>> ghat, vector<vector<double>> kk, vector<double> ff, vector<vector<double>> Tab_dep, int nnode)
{
	int n_ddl = ff.size();
	int nF = ff.size();
	vector<int> colTmtx(nF, 0);
	vector<int> rowTmtx(nF, 0); 
	vector<int> valTmtx(nF, 0); 
	vector<int> rowghat(nF, 0); 
	vector<int> valghat(nF, 0);
	int nTmtx = 0; 
	nF = 1;
	int Tab_num = 0;
	vector<int> LOCmul;
	int symbolBC = 0;
	for (int i = 0; i < nnode; i++)
	{
		nTmtx = nTmtx + 1;
		//isempty(find(Tab_dep(:,1)==i))
		for (size_t j = 0; j < Tab_dep.size(); j++)
		{
			if (Tab_dep[j][0]==i)
			{
				Tab_num = Tab_num + 1;
				LOCmul.push_back(j);
			}
		}
		////////////////////////////////
		if (Tab_num=0)
		{
			rowTmtx[3 * nTmtx - 3] = 3 * i - 3;
			colTmtx[3 * nTmtx - 3] = 3 * i - 3;
			valTmtx[3 * nTmtx - 3] = 1;
			rowTmtx[3 * nTmtx - 2] = 3 * i - 2;
			colTmtx[3 * nTmtx - 2] = 3 * i - 2;
			valTmtx[3 * nTmtx - 2] = 1;
			rowTmtx[3 * nTmtx - 1] = 3 * i - 1;
			colTmtx[3 * nTmtx - 1] = 3 * i - 1;
			valTmtx[3 * nTmtx - 1] = 1;
		}
		else
		{
			if (LOCmul.size()==3)
			{
				symbolBC = 3;
			}
			else if (LOCmul.size() == 2)
			{
				symbolBC = 2;
			}
			else
			{
				for (size_t kk = 0; kk < 3; kk++)
				{
					if (Tab_dep[LOCmul[0]][kk+2]==9999)
					{
						symbolBC = 1;
						break;
					}
					else
					{
						symbolBC = 0;
					}
				}
			}
		}

		if (symbolBC == 0)
		{
			rowTmtx[3 * nTmtx - 3] = 3 * Tab_dep[LOCmul[0]][0];// -3;
			colTmtx[3 * nTmtx - 3] = 3 * Tab_dep[LOCmul[0]][1];// -3;
			valTmtx[3 * nTmtx - 3] = 1;
			rowTmtx[3 * nTmtx - 2] = 3 * Tab_dep[LOCmul[0]][0] + 1;// -2;
			colTmtx[3 * nTmtx - 2] = 3 * Tab_dep[LOCmul[0]][1] + 1;// -2;
			valTmtx[3 * nTmtx - 2] = 1;
			rowTmtx[3 * nTmtx - 1] = 3 * Tab_dep[LOCmul[0]][0] + 2;
			colTmtx[3 * nTmtx - 1] = 3 * Tab_dep[LOCmul[0]][1] + 2;
			valTmtx[3 * nTmtx - 1] = 1;

			rowghat[nF - 1] = 3 * Tab_dep[LOCmul[0]][0];// -3;
			valghat[nF - 1] = Tab_dep[LOCmul[0]][2];
			rowghat[nF] = 3 * Tab_dep[LOCmul[0]][0] + 1;// -2;
			valghat[nF] = Tab_dep[LOCmul[0]][3];
			rowghat[nF + 1] = 3 * Tab_dep[LOCmul[0]][0] + 2;
			valghat[nF + 1] = Tab_dep[LOCmul[0]][4];
			nF = nF + 3;
		}
		else if (symbolBC == 1)
		{
			for (size_t kk = 0; kk < 3; kk++)
			{
				if (Tab_dep[LOCmul[0]][kk + 2] == 9999)
				{
					kk;
				}
				else
				{
					rowTmtx[3 * nTmtx - 4 + kk] = 3 * Tab_dep[LOCmul[0]][0] - 1 + kk;
					colTmtx[3 * nTmtx - 4 + kk] = 3 * Tab_dep[LOCmul[0]][1] - 1 + kk;
					valTmtx[3 * nTmtx - 4 + kk] = 1;

					rowghat[nF - 1] = 3 * Tab_dep[LOCmul[0]][0] - 1 + kk;
					valghat[nF - 1] = Tab_dep[LOCmul[0]][kk+2];

					if (kk==1)
					{
						rowTmtx[3 * nTmtx - 3 + kk] = 3 * Tab_dep[LOCmul[0]][0] - 1 + kk + 1;
						colTmtx[3 * nTmtx - 3 + kk] = 3 * Tab_dep[LOCmul[0]][0] - 1 + kk + 1;
						valTmtx[3 * nTmtx - 3 + kk] = 1;
						rowTmtx[3 * nTmtx - 3 + kk + 1] = 3 * Tab_dep[LOCmul[0]][0] - 1 + kk + 2;
						colTmtx[3 * nTmtx - 3 + kk + 1] = 3 * Tab_dep[LOCmul[0]][0] - 1 + kk + 2;
						valTmtx[3 * nTmtx - 3 + kk + 1] = 1;
					}
					else if (kk == 2)
					{
						rowTmtx[3 * nTmtx - 3 + kk -2] = 3 * Tab_dep[LOCmul[0]][0] - 1 + kk - 1;
						colTmtx[3 * nTmtx - 3 + kk -2] = 3 * Tab_dep[LOCmul[0]][0] - 1 + kk - 1;
						valTmtx[3 * nTmtx - 3 + kk -2] = 1;
						rowTmtx[3 * nTmtx - 3 + kk] = 3 * Tab_dep[LOCmul[0]][0] - 1 + kk + 1;
						colTmtx[3 * nTmtx - 3 + kk] = 3 * Tab_dep[LOCmul[0]][0] - 1 + kk + 1;
						valTmtx[3 * nTmtx - 3 + kk] = 1;
					}
					else
					{
						rowTmtx[3 * nTmtx - 3 + kk - 2] = 3 * Tab_dep[LOCmul[0]][0] - 1 + kk - 1;
						colTmtx[3 * nTmtx - 3 + kk - 2] = 3 * Tab_dep[LOCmul[0]][0] - 1 + kk - 1;
						valTmtx[3 * nTmtx - 3 + kk - 2] = 1;
						rowTmtx[3 * nTmtx - 3 + kk - 3] = 3 * Tab_dep[LOCmul[0]][0] - 1 + kk - 2;
						colTmtx[3 * nTmtx - 3 + kk - 3] = 3 * Tab_dep[LOCmul[0]][0] - 1 + kk - 2;
						valTmtx[3 * nTmtx - 3 + kk - 3] = 1;
					}
				}
			}
			nF = nF + 1;
		}
		else if (symbolBC == 3)
		{
			for (size_t sNO = 0; sNO < LOCmul.size(); sNO++)
			{
				int LOC = LOCmul[sNO];
			}
		}


		Tab_num = 0;
		LOCmul.clear();
	}
}
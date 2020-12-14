#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void SelectionPeriodNodes(vector<vector<double>> &dofFace, vector<vector<double>>&dofVaule,vector<vector<double>>& h0, vector<int> Fxh, vector<int> Fx0, vector<int> Fyh, vector<int> Fy0, vector<int> Fzh, vector<int> Fz0, vector< vector<double> >& gcoord, double tole)
{
	int FyhFxh = 0;////
	int Fy0Fxh = 0;////
	///////////////
	int FzhFxh = 0;
	int Fz0Fxh = 0;
	vector<double>dofF;
	vector<double>dofV;
	//vector<int> dofFace;
	//vector<int> dofVaule;
	//dofFace.resize(Fx0.size()+ Fy0.size()+ Fz0.size());
	//dofVaule.resize(Fx0.size() + Fy0.size() + Fz0.size());
	for (size_t i = 0; i < Fxh.size(); i++)
	{
		for (size_t i1 = 0; i1 < Fyh.size(); i1++)
		{
			if (Fxh[i] == Fyh[i1]) FyhFxh = FyhFxh + 1;
		}
		for (size_t i1 = 0; i1 < Fy0.size(); i1++)
		{
			if (Fxh[i] == Fy0[i1]) Fy0Fxh = Fy0Fxh + 1;
		}
		for (size_t i1 = 0; i1 < Fzh.size(); i1++)
		{
			if (Fxh[i] == Fzh[i1]) FzhFxh = FzhFxh + 1;
		}
		for (size_t i1 = 0; i1 < Fz0.size(); i1++)
		{
			if (Fxh[i] == Fz0[i1]) Fz0Fxh = Fz0Fxh + 1;
		}
		if (FyhFxh != 0)
		{
			if (FzhFxh != 0)
			{
				for (size_t jj = 0; jj < Fx0.size(); jj++)
				{
					if (gcoord[Fxh[i]][1] <= (gcoord[Fx0[jj]][1] + tole) && gcoord[Fxh[i]][1] >= (gcoord[Fx0[jj]][1] - tole) &&
						gcoord[Fxh[i]][2] <= (gcoord[Fx0[jj]][2] + tole) && gcoord[Fxh[i]][2] >= (gcoord[Fx0[jj]][2] - tole))
					{
						dofF.push_back(Fxh[i]);
						dofF.push_back(Fx0[jj]);
						dofFace.push_back(dofF);
						///////////////////////////////////////////////////////////////////////////
						dofV.push_back(h0[0][0] * (gcoord[Fxh[i]][0] - gcoord[Fx0[jj]][0]) + h0[0][1] * (gcoord[Fxh[i]][1] - gcoord[Fx0[jj]][1]) + h0[0][2] * (gcoord[Fxh[i]][2] - gcoord[Fx0[jj]][2]));
						dofV.push_back(9999);
						dofV.push_back(9999);
						dofVaule.push_back(dofV);
						dofF.clear();
						dofV.clear();
						break;
					}
				}
				for (size_t jj = 0; jj < Fy0.size(); jj++)
				{
					if (gcoord[Fxh[i]][0] <= (gcoord[Fy0[jj]][0] + tole) && gcoord[Fxh[i]][0] >= (gcoord[Fy0[jj]][0] - tole) &&
						gcoord[Fxh[i]][2] <= (gcoord[Fy0[jj]][2] + tole) && gcoord[Fxh[i]][2] >= (gcoord[Fy0[jj]][2] - tole))
					{
						dofF.push_back(Fxh[i]);
						dofF.push_back(Fy0[jj]);
						dofFace.push_back(dofF);
						///////////////////////////////////////////////////////////////////////////
						dofV.push_back(9999);
						dofV.push_back(h0[1][0] * (gcoord[Fxh[i]][0] - gcoord[Fy0[jj]][0]) + h0[1][1] * (gcoord[Fxh[i]][1] - gcoord[Fy0[jj]][1]) + h0[1][2] * (gcoord[Fxh[i]][2] - gcoord[Fy0[jj]][2]));
						dofV.push_back(9999);
						dofVaule.push_back(dofV);
						dofF.clear();
						dofV.clear();
						break;
					}
				}
				for (size_t jj = 0; jj < Fz0.size(); jj++)
				{
					if (gcoord[Fxh[i]][0] <= (gcoord[Fz0[jj]][0] + tole) && gcoord[Fxh[i]][0] >= (gcoord[Fz0[jj]][0] - tole) &&
						gcoord[Fxh[i]][1] <= (gcoord[Fz0[jj]][1] + tole) && gcoord[Fxh[i]][1] >= (gcoord[Fz0[jj]][1] - tole))
					{
						dofF.push_back(Fxh[i]);
						dofF.push_back(Fz0[jj]);
						dofFace.push_back(dofF);
						///////////////////////////////////////////////////////////////////////////
						dofV.push_back(9999);
						dofV.push_back(9999);
						dofV.push_back(h0[2][0] * (gcoord[Fxh[i]][0] - gcoord[Fz0[jj]][0]) + h0[2][1] * (gcoord[Fxh[i]][1] - gcoord[Fz0[jj]][1]) + h0[2][2] * (gcoord[Fxh[i]][2] - gcoord[Fz0[jj]][2]));
						dofVaule.push_back(dofV);
						dofF.clear();
						dofV.clear();
						break;
					}
				}
			}
			else if (Fz0Fxh != 0)
			{
				for (size_t jj = 0; jj < Fx0.size(); jj++)
				{
					if (gcoord[Fxh[i]][1] <= (gcoord[Fx0[jj]][1] + tole) && gcoord[Fxh[i]][1] >= (gcoord[Fx0[jj]][1] - tole) &&
						gcoord[Fxh[i]][2] <= (gcoord[Fx0[jj]][2] + tole) && gcoord[Fxh[i]][2] >= (gcoord[Fx0[jj]][2] - tole))
					{
						dofF.push_back(Fxh[i]);
						dofF.push_back(Fx0[jj]);
						dofFace.push_back(dofF);
						///////////////////////////////////////////////////////////////////////////
						dofV.push_back(h0[0][0] * (gcoord[Fxh[i]][0] - gcoord[Fx0[jj]][0]) + h0[0][1] * (gcoord[Fxh[i]][1] - gcoord[Fx0[jj]][1]) + h0[0][2] * (gcoord[Fxh[i]][2] - gcoord[Fx0[jj]][2]));
						dofV.push_back(9999);
						dofV.push_back(9999);
						dofVaule.push_back(dofV);
						dofF.clear();
						dofV.clear();
						break;
					}
				}
				for (size_t jj = 0; jj < Fy0.size(); jj++)
				{
					if (gcoord[Fxh[i]][0] <= (gcoord[Fy0[jj]][0] + tole) && gcoord[Fxh[i]][0] >= (gcoord[Fy0[jj]][0] - tole) &&
						gcoord[Fxh[i]][2] <= (gcoord[Fy0[jj]][2] + tole) && gcoord[Fxh[i]][2] >= (gcoord[Fy0[jj]][2] - tole))
					{
						dofF.push_back(Fxh[i]);
						dofF.push_back(Fy0[jj]);
						dofFace.push_back(dofF);
						///////////////////////////////////////////////////////////////////////////
						dofV.push_back(9999);
						dofV.push_back(h0[1][0] * (gcoord[Fxh[i]][0] - gcoord[Fy0[jj]][0]) + h0[1][1] * (gcoord[Fxh[i]][1] - gcoord[Fy0[jj]][1]) + h0[1][2] * (gcoord[Fxh[i]][2] - gcoord[Fy0[jj]][2]));
						dofV.push_back(9999);
						dofVaule.push_back(dofV);
						dofF.clear();
						dofV.clear();
						break;
					}
				}
			}
			else
			{
				for (size_t jj = 0; jj < Fx0.size(); jj++)
				{
					if (gcoord[Fxh[i]][1] <= (gcoord[Fx0[jj]][1] + tole) && gcoord[Fxh[i]][1] >= (gcoord[Fx0[jj]][1] - tole) &&
						gcoord[Fxh[i]][2] <= (gcoord[Fx0[jj]][2] + tole) && gcoord[Fxh[i]][2] >= (gcoord[Fx0[jj]][2] - tole))
					{
						dofF.push_back(Fxh[i]);
						dofF.push_back(Fx0[jj]);
						dofFace.push_back(dofF);
						///////////////////////////////////////////////////////////////////////////
						dofV.push_back(h0[0][0] * (gcoord[Fxh[i]][0] - gcoord[Fx0[jj]][0]) + h0[0][1] * (gcoord[Fxh[i]][1] - gcoord[Fx0[jj]][1]) + h0[0][2] * (gcoord[Fxh[i]][2] - gcoord[Fx0[jj]][2]));
						dofV.push_back(9999);
						dofV.push_back(9999);
						dofVaule.push_back(dofV);
						dofF.clear();
						dofV.clear();
						break;
					}
				}
				for (size_t jj = 0; jj < Fy0.size(); jj++)
				{
					if (gcoord[Fxh[i]][0] <= (gcoord[Fy0[jj]][0] + tole) && gcoord[Fxh[i]][0] >= (gcoord[Fy0[jj]][0] - tole) &&
						gcoord[Fxh[i]][2] <= (gcoord[Fy0[jj]][2] + tole) && gcoord[Fxh[i]][2] >= (gcoord[Fy0[jj]][2] - tole))
					{
						dofF.push_back(Fxh[i]);
						dofF.push_back(Fy0[jj]);
						dofFace.push_back(dofF);
						///////////////////////////////////////////////////////////////////////////
						dofV.push_back(9999);
						dofV.push_back(h0[1][0] * (gcoord[Fxh[i]][0] - gcoord[Fy0[jj]][0]) + h0[1][1] * (gcoord[Fxh[i]][1] - gcoord[Fy0[jj]][1]) + h0[1][2] * (gcoord[Fxh[i]][2] - gcoord[Fy0[jj]][2]));
						dofV.push_back(9999);
						dofVaule.push_back(dofV);
						dofF.clear();
						dofV.clear();
						break;
					}
				}
			}
		}
		////////////////////////////////////////////////////////////
		else if (Fy0Fxh != 0)
		{
			if (FzhFxh != 0)
			{
				for (size_t jj = 0; jj < Fx0.size(); jj++)
				{
					if (gcoord[Fxh[i]][1] <= (gcoord[Fx0[jj]][1] + tole) && gcoord[Fxh[i]][1] >= (gcoord[Fx0[jj]][1] - tole) &&
						gcoord[Fxh[i]][2] <= (gcoord[Fx0[jj]][2] + tole) && gcoord[Fxh[i]][2] >= (gcoord[Fx0[jj]][2] - tole))
					{
						dofF.push_back(Fxh[i]);
						dofF.push_back(Fx0[jj]);
						dofFace.push_back(dofF);
						///////////////////////////////////////////////////////////////////////////
						dofV.push_back(h0[0][0] * (gcoord[Fxh[i]][0] - gcoord[Fx0[jj]][0]) + h0[0][1] * (gcoord[Fxh[i]][1] - gcoord[Fx0[jj]][1]) + h0[0][2] * (gcoord[Fxh[i]][2] - gcoord[Fx0[jj]][2]));
						dofV.push_back(9999);
						dofV.push_back(9999);
						dofVaule.push_back(dofV);
						dofF.clear();
						dofV.clear();
						break;
					}
				}
				for (size_t jj = 0; jj < Fz0.size(); jj++)
				{
					if (gcoord[Fxh[i]][0] <= (gcoord[Fz0[jj]][0] + tole) && gcoord[Fxh[i]][0] >= (gcoord[Fz0[jj]][0] - tole) &&
						gcoord[Fxh[i]][1] <= (gcoord[Fz0[jj]][1] + tole) && gcoord[Fxh[i]][1] >= (gcoord[Fz0[jj]][1] - tole))
					{
						dofF.push_back(Fxh[i]);
						dofF.push_back(Fz0[jj]);
						dofFace.push_back(dofF);
						///////////////////////////////////////////////////////////////////////////
						dofV.push_back(9999);
						dofV.push_back(9999);
						dofV.push_back(h0[2][0] * (gcoord[Fxh[i]][0] - gcoord[Fz0[jj]][0]) + h0[2][1] * (gcoord[Fxh[i]][1] - gcoord[Fz0[jj]][1]) + h0[2][2] * (gcoord[Fxh[i]][2] - gcoord[Fz0[jj]][2]));
						dofVaule.push_back(dofV);
						dofF.clear();
						dofV.clear();
						break;
					}
				}
			}
			else if (Fz0Fxh != 0)
			{
				for (size_t jj = 0; jj < Fx0.size(); jj++)
				{
					if (gcoord[Fxh[i]][1] <= (gcoord[Fx0[jj]][1] + tole) && gcoord[Fxh[i]][1] >= (gcoord[Fx0[jj]][1] - tole) &&
						gcoord[Fxh[i]][2] <= (gcoord[Fx0[jj]][2] + tole) && gcoord[Fxh[i]][2] >= (gcoord[Fx0[jj]][2] - tole))
					{
						dofF.push_back(Fxh[i]);
						dofF.push_back(Fx0[jj]);
						dofFace.push_back(dofF);
						///////////////////////////////////////////////////////////////////////////
						dofV.push_back(h0[0][0] * (gcoord[Fxh[i]][0] - gcoord[Fx0[jj]][0]) + h0[0][1] * (gcoord[Fxh[i]][1] - gcoord[Fx0[jj]][1]) + h0[0][2] * (gcoord[Fxh[i]][2] - gcoord[Fx0[jj]][2]));
						dofV.push_back(9999);
						dofV.push_back(9999);
						dofVaule.push_back(dofV);
						dofF.clear();
						dofV.clear();
						break;
					}
				}
			}
			else
			{
				for (size_t jj = 0; jj < Fx0.size(); jj++)
				{
					if (gcoord[Fxh[i]][1] <= (gcoord[Fx0[jj]][1] + tole) && gcoord[Fxh[i]][1] >= (gcoord[Fx0[jj]][1] - tole) &&
						gcoord[Fxh[i]][2] <= (gcoord[Fx0[jj]][2] + tole) && gcoord[Fxh[i]][2] >= (gcoord[Fx0[jj]][2] - tole))
					{
						dofF.push_back(Fxh[i]);
						dofF.push_back(Fx0[jj]);
						dofFace.push_back(dofF);
						///////////////////////////////////////////////////////////////////////////
						dofV.push_back(h0[0][0] * (gcoord[Fxh[i]][0] - gcoord[Fx0[jj]][0]) + h0[0][1] * (gcoord[Fxh[i]][1] - gcoord[Fx0[jj]][1]) + h0[0][2] * (gcoord[Fxh[i]][2] - gcoord[Fx0[jj]][2]));
						dofV.push_back(9999);
						dofV.push_back(9999);
						dofVaule.push_back(dofV);
						dofF.clear();
						dofV.clear();
						break;
					}
				}
			}
		}
		//////////////////////////////////////////////////////////////
		else if (FzhFxh != 0)
		{
			for (size_t jj = 0; jj < Fx0.size(); jj++)
			{
				if (gcoord[Fxh[i]][1] <= (gcoord[Fx0[jj]][1] + tole) && gcoord[Fxh[i]][1] >= (gcoord[Fx0[jj]][1] - tole) &&
					gcoord[Fxh[i]][2] <= (gcoord[Fx0[jj]][2] + tole) && gcoord[Fxh[i]][2] >= (gcoord[Fx0[jj]][2] - tole))
				{
					dofF.push_back(Fxh[i]);
					dofF.push_back(Fx0[jj]);
					dofFace.push_back(dofF);
					///////////////////////////////////////////////////////////////////////////
					dofV.push_back(h0[0][0] * (gcoord[Fxh[i]][0] - gcoord[Fx0[jj]][0]) + h0[0][1] * (gcoord[Fxh[i]][1] - gcoord[Fx0[jj]][1]) + h0[0][2] * (gcoord[Fxh[i]][2] - gcoord[Fx0[jj]][2]));
					dofV.push_back(9999);
					dofV.push_back(9999);
					dofVaule.push_back(dofV);
					dofF.clear();
					dofV.clear();
					break;
				}
			}
			for (size_t jj = 0; jj < Fz0.size(); jj++)
			{
				if (gcoord[Fxh[i]][0] <= (gcoord[Fz0[jj]][0] + tole) && gcoord[Fxh[i]][0] >= (gcoord[Fz0[jj]][0] - tole) &&
					gcoord[Fxh[i]][1] <= (gcoord[Fz0[jj]][1] + tole) && gcoord[Fxh[i]][1] >= (gcoord[Fz0[jj]][1] - tole))
				{
					dofF.push_back(Fxh[i]);
					dofF.push_back(Fz0[jj]);
					dofFace.push_back(dofF);
					///////////////////////////////////////////////////////////////////////////
					dofV.push_back(9999);
					dofV.push_back(9999);
					dofV.push_back(h0[2][0] * (gcoord[Fxh[i]][0] - gcoord[Fz0[jj]][0]) + h0[2][1] * (gcoord[Fxh[i]][1] - gcoord[Fz0[jj]][1]) + h0[2][2] * (gcoord[Fxh[i]][2] - gcoord[Fz0[jj]][2]));
					dofVaule.push_back(dofV);
					dofF.clear();
					dofV.clear();
					break;
				}
			}
		}
		//////////////////////////////////////////////////////
		else if (Fz0Fxh != 0)
		{
			for (size_t jj = 0; jj < Fx0.size(); jj++)
			{
				if (gcoord[Fxh[i]][1] <= (gcoord[Fx0[jj]][1] + tole) && gcoord[Fxh[i]][1] >= (gcoord[Fx0[jj]][1] - tole) &&
					gcoord[Fxh[i]][2] <= (gcoord[Fx0[jj]][2] + tole) && gcoord[Fxh[i]][2] >= (gcoord[Fx0[jj]][2] - tole))
				{
					dofF.push_back(Fxh[i]);
					dofF.push_back(Fx0[jj]);
					dofFace.push_back(dofF);
					///////////////////////////////////////////////////////////////////////////
					dofV.push_back(h0[0][0] * (gcoord[Fxh[i]][0] - gcoord[Fx0[jj]][0]) + h0[0][1] * (gcoord[Fxh[i]][1] - gcoord[Fx0[jj]][1]) + h0[0][2] * (gcoord[Fxh[i]][2] - gcoord[Fx0[jj]][2]));
					dofV.push_back(9999);
					dofV.push_back(9999);
					dofVaule.push_back(dofV);
					dofF.clear();
					dofV.clear();
					break;
				}
			}
		}
		//////////////////////////////////////////
		else
	    {
			for (size_t jj = 0; jj < Fx0.size(); jj++)
			{
				if (gcoord[Fxh[i]][1] <= (gcoord[Fx0[jj]][1] + tole) && gcoord[Fxh[i]][1] >= (gcoord[Fx0[jj]][1] - tole) &&
					gcoord[Fxh[i]][2] <= (gcoord[Fx0[jj]][2] + tole) && gcoord[Fxh[i]][2] >= (gcoord[Fx0[jj]][2] - tole))
				{
					dofF.push_back(Fxh[i]);
					dofF.push_back(Fx0[jj]);
					dofFace.push_back(dofF);
					///////////////////////////////////////////////////////////////////////////
					dofV.push_back(h0[0][0] * (gcoord[Fxh[i]][0] - gcoord[Fx0[jj]][0]) + h0[0][1] * (gcoord[Fxh[i]][1] - gcoord[Fx0[jj]][1]) + h0[0][2] * (gcoord[Fxh[i]][2] - gcoord[Fx0[jj]][2]));
					dofV.push_back(h0[1][0] * (gcoord[Fxh[i]][0] - gcoord[Fx0[jj]][0]) + h0[1][1] * (gcoord[Fxh[i]][1] - gcoord[Fx0[jj]][1]) + h0[1][2] * (gcoord[Fxh[i]][2] - gcoord[Fx0[jj]][2]));
					dofV.push_back(h0[2][0] * (gcoord[Fxh[i]][0] - gcoord[Fx0[jj]][0]) + h0[2][1] * (gcoord[Fxh[i]][1] - gcoord[Fx0[jj]][1]) + h0[2][2] * (gcoord[Fxh[i]][2] - gcoord[Fx0[jj]][2]));
					dofVaule.push_back(dofV);
					dofF.clear();
					dofV.clear();
					break;
				}
			}
	    }
		FyhFxh = 0;
		Fy0Fxh = 0;
		FzhFxh = 0;
		Fz0Fxh = 0;
	}
	//////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////
	int FxhFyh = 0;////
	int Fx0Fyh = 0;////
	///////////////
	int FzhFyh = 0;
	int Fz0Fyh = 0;
	for (size_t i = 0; i < Fyh.size(); i++)
	{
		for (size_t i1 = 0; i1 < Fxh.size(); i1++)
		{
			if (Fyh[i] == Fxh[i1]) FxhFyh = FxhFyh + 1;
		}
		for (size_t i1 = 0; i1 < Fx0.size(); i1++)
		{
			if (Fyh[i] == Fx0[i1]) Fx0Fyh = Fx0Fyh + 1;
		}
		for (size_t i1 = 0; i1 < Fzh.size(); i1++)
		{
			if (Fyh[i] == Fzh[i1]) FzhFyh = FzhFyh + 1;
		}
		for (size_t i1 = 0; i1 < Fz0.size(); i1++)
		{
			if (Fyh[i] == Fz0[i1]) Fz0Fyh = Fz0Fyh + 1;
		}
		if (FxhFyh != 0)
		{
			//Already processed in the former part
		}
		////////////////////////////////////////////////////////////
		else if (Fx0Fyh != 0)
		{
			if (FzhFyh != 0)
			{
				for (size_t jj = 0; jj < Fy0.size(); jj++)
				{
					if (gcoord[Fyh[i]][0] <= (gcoord[Fy0[jj]][0] + tole) && gcoord[Fyh[i]][0] >= (gcoord[Fy0[jj]][0] - tole) &&
						gcoord[Fyh[i]][2] <= (gcoord[Fy0[jj]][2] + tole) && gcoord[Fyh[i]][2] >= (gcoord[Fy0[jj]][2] - tole))
					{
						dofF.push_back(Fyh[i]);
						dofF.push_back(Fy0[jj]);
						dofFace.push_back(dofF);
						///////////////////////////////////////////////////////////////////////////
						dofV.push_back(9999);
						dofV.push_back(h0[1][0] * (gcoord[Fyh[i]][0] - gcoord[Fy0[jj]][0]) + h0[1][1] * (gcoord[Fyh[i]][1] - gcoord[Fy0[jj]][1]) + h0[1][2] * (gcoord[Fyh[i]][2] - gcoord[Fy0[jj]][2]));
						dofV.push_back(9999);
						dofVaule.push_back(dofV);
						dofF.clear();
						dofV.clear();
						break;
					}
				}
				for (size_t jj = 0; jj < Fz0.size(); jj++)
				{
					if (gcoord[Fyh[i]][0] <= (gcoord[Fz0[jj]][0] + tole) && gcoord[Fyh[i]][0] >= (gcoord[Fz0[jj]][0] - tole) &&
						gcoord[Fyh[i]][1] <= (gcoord[Fz0[jj]][1] + tole) && gcoord[Fyh[i]][1] >= (gcoord[Fz0[jj]][1] - tole))
					{
						dofF.push_back(Fyh[i]);
						dofF.push_back(Fz0[jj]);
						dofFace.push_back(dofF);
						///////////////////////////////////////////////////////////////////////////
						dofV.push_back(9999);
						dofV.push_back(9999);
						dofV.push_back(h0[2][0] * (gcoord[Fyh[i]][0] - gcoord[Fz0[jj]][0]) + h0[2][1] * (gcoord[Fyh[i]][1] - gcoord[Fz0[jj]][1]) + h0[2][2] * (gcoord[Fyh[i]][2] - gcoord[Fz0[jj]][2]));
						dofVaule.push_back(dofV);
						dofF.clear();
						dofV.clear();
						break;
					}
				}
			}
			else if (Fz0Fyh != 0)
			{
				for (size_t jj = 0; jj < Fy0.size(); jj++)
				{
					if (gcoord[Fyh[i]][0] <= (gcoord[Fy0[jj]][0] + tole) && gcoord[Fyh[i]][0] >= (gcoord[Fy0[jj]][0] - tole) &&
						gcoord[Fyh[i]][2] <= (gcoord[Fy0[jj]][2] + tole) && gcoord[Fyh[i]][2] >= (gcoord[Fy0[jj]][2] - tole))
					{
						dofF.push_back(Fyh[i]);
						dofF.push_back(Fy0[jj]);
						dofFace.push_back(dofF);
						///////////////////////////////////////////////////////////////////////////
						dofV.push_back(9999);
						dofV.push_back(h0[1][0] * (gcoord[Fyh[i]][0] - gcoord[Fy0[jj]][0]) + h0[1][1] * (gcoord[Fyh[i]][1] - gcoord[Fy0[jj]][1]) + h0[1][2] * (gcoord[Fyh[i]][2] - gcoord[Fy0[jj]][2]));
						dofV.push_back(9999);
						dofVaule.push_back(dofV);
						dofF.clear();
						dofV.clear();
						break;
					}
				}
			}
			else
			{
				for (size_t jj = 0; jj < Fy0.size(); jj++)
				{
					if (gcoord[Fyh[i]][0] <= (gcoord[Fy0[jj]][0] + tole) && gcoord[Fyh[i]][0] >= (gcoord[Fy0[jj]][0] - tole) &&
						gcoord[Fyh[i]][2] <= (gcoord[Fy0[jj]][2] + tole) && gcoord[Fyh[i]][2] >= (gcoord[Fy0[jj]][2] - tole))
					{
						dofF.push_back(Fyh[i]);
						dofF.push_back(Fy0[jj]);
						dofFace.push_back(dofF);
						///////////////////////////////////////////////////////////////////////////
						dofV.push_back(9999);
						dofV.push_back(h0[1][0] * (gcoord[Fyh[i]][0] - gcoord[Fy0[jj]][0]) + h0[1][1] * (gcoord[Fyh[i]][1] - gcoord[Fy0[jj]][1]) + h0[1][2] * (gcoord[Fyh[i]][2] - gcoord[Fy0[jj]][2]));
						dofV.push_back(9999);
						dofVaule.push_back(dofV);
						dofF.clear();
						dofV.clear();
						break;
					}
				}
			}
		}
		//////////////////////////////////////////////////////////////
		else if (FzhFyh != 0)
		{
			for (size_t jj = 0; jj < Fy0.size(); jj++)
			{
				if (gcoord[Fyh[i]][0] <= (gcoord[Fy0[jj]][0] + tole) && gcoord[Fyh[i]][0] >= (gcoord[Fy0[jj]][0] - tole) &&
					gcoord[Fyh[i]][2] <= (gcoord[Fy0[jj]][2] + tole) && gcoord[Fyh[i]][2] >= (gcoord[Fy0[jj]][2] - tole))
				{
					dofF.push_back(Fyh[i]);
					dofF.push_back(Fy0[jj]);
					dofFace.push_back(dofF);
					///////////////////////////////////////////////////////////////////////////
					dofV.push_back(9999);
					dofV.push_back(h0[1][0] * (gcoord[Fyh[i]][0] - gcoord[Fy0[jj]][0]) + h0[1][1] * (gcoord[Fyh[i]][1] - gcoord[Fy0[jj]][1]) + h0[1][2] * (gcoord[Fyh[i]][2] - gcoord[Fy0[jj]][2]));
					dofV.push_back(9999);
					dofVaule.push_back(dofV);
					dofF.clear();
					dofV.clear();
					break;
				}
			}
			for (size_t jj = 0; jj < Fz0.size(); jj++)
			{
				if (gcoord[Fyh[i]][0] <= (gcoord[Fz0[jj]][0] + tole) && gcoord[Fyh[i]][0] >= (gcoord[Fz0[jj]][0] - tole) &&
					gcoord[Fyh[i]][1] <= (gcoord[Fz0[jj]][1] + tole) && gcoord[Fyh[i]][1] >= (gcoord[Fz0[jj]][1] - tole))
				{
					dofF.push_back(Fyh[i]);
					dofF.push_back(Fz0[jj]);
					dofFace.push_back(dofF);
					///////////////////////////////////////////////////////////////////////////
					dofV.push_back(9999);
					dofV.push_back(9999);
					dofV.push_back(h0[2][0] * (gcoord[Fyh[i]][0] - gcoord[Fz0[jj]][0]) + h0[2][1] * (gcoord[Fyh[i]][1] - gcoord[Fz0[jj]][1]) + h0[2][2] * (gcoord[Fyh[i]][2] - gcoord[Fz0[jj]][2]));
					dofVaule.push_back(dofV);
					dofF.clear();
					dofV.clear();
					break;
				}
			}
		}
		//////////////////////////////////////////////////////
		else if (Fz0Fyh != 0)
		{
			for (size_t jj = 0; jj < Fy0.size(); jj++)
			{
				if (gcoord[Fyh[i]][0] <= (gcoord[Fy0[jj]][0] + tole) && gcoord[Fyh[i]][0] >= (gcoord[Fy0[jj]][0] - tole) &&
					gcoord[Fyh[i]][2] <= (gcoord[Fy0[jj]][2] + tole) && gcoord[Fyh[i]][2] >= (gcoord[Fy0[jj]][2] - tole))
				{
					dofF.push_back(Fyh[i]);
					dofF.push_back(Fy0[jj]);
					dofFace.push_back(dofF);
					///////////////////////////////////////////////////////////////////////////
					dofV.push_back(9999);
					dofV.push_back(h0[1][0] * (gcoord[Fyh[i]][0] - gcoord[Fy0[jj]][0]) + h0[1][1] * (gcoord[Fyh[i]][1] - gcoord[Fy0[jj]][1]) + h0[1][2] * (gcoord[Fyh[i]][2] - gcoord[Fy0[jj]][2]));
					dofV.push_back(9999);
					dofVaule.push_back(dofV);
					dofF.clear();
					dofV.clear();
					break;
				}
			}
		}
		//////////////////////////////////////////
		else
		{
			for (size_t jj = 0; jj < Fy0.size(); jj++)
			{
				if (gcoord[Fyh[i]][0] <= (gcoord[Fy0[jj]][0] + tole) && gcoord[Fyh[i]][0] >= (gcoord[Fy0[jj]][0] - tole) &&
					gcoord[Fyh[i]][2] <= (gcoord[Fy0[jj]][2] + tole) && gcoord[Fyh[i]][2] >= (gcoord[Fy0[jj]][2] - tole))
				{
					dofF.push_back(Fyh[i]);
					dofF.push_back(Fy0[jj]);
					dofFace.push_back(dofF);
					///////////////////////////////////////////////////////////////////////////
					dofV.push_back(h0[0][0] * (gcoord[Fyh[i]][0] - gcoord[Fy0[jj]][0]) + h0[0][1] * (gcoord[Fyh[i]][1] - gcoord[Fy0[jj]][1]) + h0[0][2] * (gcoord[Fyh[i]][2] - gcoord[Fy0[jj]][2]));
					dofV.push_back(h0[1][0] * (gcoord[Fyh[i]][0] - gcoord[Fy0[jj]][0]) + h0[1][1] * (gcoord[Fyh[i]][1] - gcoord[Fy0[jj]][1]) + h0[1][2] * (gcoord[Fyh[i]][2] - gcoord[Fy0[jj]][2]));
					dofV.push_back(h0[2][0] * (gcoord[Fyh[i]][0] - gcoord[Fy0[jj]][0]) + h0[2][1] * (gcoord[Fyh[i]][1] - gcoord[Fy0[jj]][1]) + h0[2][2] * (gcoord[Fyh[i]][2] - gcoord[Fy0[jj]][2]));
					dofVaule.push_back(dofV);
					dofF.clear();
					dofV.clear();
					break;
				}
			}
		}
		FxhFyh = 0;
		Fx0Fyh = 0;
		FzhFyh = 0;
		Fz0Fyh = 0;
	}
	//////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////
	int FxhFzh = 0;////
	int Fx0Fzh = 0;////
	///////////////
	int FyhFzh = 0;
	int Fy0Fzh = 0;
	for (size_t i = 0; i < Fzh.size(); i++)
	{
		for (size_t i1 = 0; i1 < Fxh.size(); i1++)
		{
			if (Fzh[i] == Fxh[i1]) FxhFzh = FxhFzh + 1;
		}
		for (size_t i1 = 0; i1 < Fx0.size(); i1++)
		{
			if (Fzh[i] == Fx0[i1]) Fx0Fzh = Fx0Fzh + 1;
		}
		for (size_t i1 = 0; i1 < Fyh.size(); i1++)
		{
			if (Fzh[i] == Fyh[i1]) FyhFzh = FyhFzh + 1;
		}
		for (size_t i1 = 0; i1 < Fy0.size(); i1++)
		{
			if (Fzh[i] == Fy0[i1]) Fy0Fzh = Fy0Fzh + 1;
		}
		if (FxhFzh != 0)
		{
			//Already processed in the former part
		}
		////////////////////////////////////////////////////////////
		else if (FyhFzh != 0)
		{
			//Already processed in the former part
		}
		////////////////////////////////////////////////////////////
		else if (Fx0Fzh != 0)
		{
			if (Fy0Fzh != 0)
			{
				for (size_t jj = 0; jj < Fz0.size(); jj++)
				{
					if (gcoord[Fzh[i]][1] <= (gcoord[Fz0[jj]][1] + tole) && gcoord[Fzh[i]][1] >= (gcoord[Fz0[jj]][1] - tole) &&
						gcoord[Fzh[i]][0] <= (gcoord[Fz0[jj]][0] + tole) && gcoord[Fzh[i]][0] >= (gcoord[Fz0[jj]][0] - tole))
					{
						dofF.push_back(Fzh[i]);
						dofF.push_back(Fz0[jj]);
						dofFace.push_back(dofF);
						///////////////////////////////////////////////////////////////////////////
						dofV.push_back(9999);
						dofV.push_back(9999);
						dofV.push_back(h0[2][0] * (gcoord[Fzh[i]][0] - gcoord[Fz0[jj]][0]) + h0[2][1] * (gcoord[Fzh[i]][1] - gcoord[Fz0[jj]][1]) + h0[2][2] * (gcoord[Fzh[i]][2] - gcoord[Fz0[jj]][2]));
						dofVaule.push_back(dofV);
						dofF.clear();
						dofV.clear();
						break;
					}
				}
			}
			else
			{
				for (size_t jj = 0; jj < Fz0.size(); jj++)
				{
					if (gcoord[Fzh[i]][1] <= (gcoord[Fz0[jj]][1] + tole) && gcoord[Fzh[i]][1] >= (gcoord[Fz0[jj]][1] - tole) &&
						gcoord[Fzh[i]][0] <= (gcoord[Fz0[jj]][0] + tole) && gcoord[Fzh[i]][0] >= (gcoord[Fz0[jj]][0] - tole))
					{
						dofF.push_back(Fzh[i]);
						dofF.push_back(Fz0[jj]);
						dofFace.push_back(dofF);
						///////////////////////////////////////////////////////////////////////////
						dofV.push_back(9999);
						dofV.push_back(9999);
						dofV.push_back(h0[2][0] * (gcoord[Fzh[i]][0] - gcoord[Fz0[jj]][0]) + h0[2][1] * (gcoord[Fzh[i]][1] - gcoord[Fz0[jj]][1]) + h0[2][2] * (gcoord[Fzh[i]][2] - gcoord[Fz0[jj]][2]));
						dofVaule.push_back(dofV);
						dofF.clear();
						dofV.clear();
						break;
					}
				}
			}
		}
		//////////////////////////////////////////////////////
		else if (Fy0Fzh != 0)
		{
			for (size_t jj = 0; jj < Fz0.size(); jj++)
			{
				if (gcoord[Fzh[i]][1] <= (gcoord[Fz0[jj]][1] + tole) && gcoord[Fzh[i]][1] >= (gcoord[Fz0[jj]][1] - tole) &&
					gcoord[Fzh[i]][0] <= (gcoord[Fz0[jj]][0] + tole) && gcoord[Fzh[i]][0] >= (gcoord[Fz0[jj]][0] - tole))
				{
					dofF.push_back(Fzh[i]);
					dofF.push_back(Fz0[jj]);
					dofFace.push_back(dofF);
					///////////////////////////////////////////////////////////////////////////
					dofV.push_back(9999);
					dofV.push_back(9999);
					dofV.push_back(h0[2][0] * (gcoord[Fzh[i]][0] - gcoord[Fz0[jj]][0]) + h0[2][1] * (gcoord[Fzh[i]][1] - gcoord[Fz0[jj]][1]) + h0[2][2] * (gcoord[Fzh[i]][2] - gcoord[Fz0[jj]][2]));
					dofVaule.push_back(dofV);
					dofF.clear();
					dofV.clear();
					break;
				}
			}
		}
		//////////////////////////////////////////
		else
		{
			for (size_t jj = 0; jj < Fz0.size(); jj++)
			{
				if (gcoord[Fzh[i]][1] <= (gcoord[Fz0[jj]][1] + tole) && gcoord[Fzh[i]][1] >= (gcoord[Fz0[jj]][1] - tole) &&
					gcoord[Fzh[i]][0] <= (gcoord[Fz0[jj]][0] + tole) && gcoord[Fzh[i]][0] >= (gcoord[Fz0[jj]][0] - tole))
				{
					dofF.push_back(Fzh[i]);
					dofF.push_back(Fz0[jj]);
					dofFace.push_back(dofF);
					///////////////////////////////////////////////////////////////////////////
					dofV.push_back(h0[0][0] * (gcoord[Fzh[i]][0] - gcoord[Fz0[jj]][0]) + h0[0][1] * (gcoord[Fzh[i]][1] - gcoord[Fz0[jj]][1]) + h0[0][2] * (gcoord[Fzh[i]][2] - gcoord[Fz0[jj]][2]));
					dofV.push_back(h0[1][0] * (gcoord[Fzh[i]][0] - gcoord[Fz0[jj]][0]) + h0[1][1] * (gcoord[Fzh[i]][1] - gcoord[Fz0[jj]][1]) + h0[1][2] * (gcoord[Fzh[i]][2] - gcoord[Fz0[jj]][2]));
					dofV.push_back(h0[2][0] * (gcoord[Fzh[i]][0] - gcoord[Fz0[jj]][0]) + h0[2][1] * (gcoord[Fzh[i]][1] - gcoord[Fz0[jj]][1]) + h0[2][2] * (gcoord[Fzh[i]][2] - gcoord[Fz0[jj]][2]));
					dofVaule.push_back(dofV);
					dofF.clear();
					dofV.clear();
					break;
				}
			}
		}
		FxhFzh = 0;
		Fx0Fzh = 0;
		FyhFzh = 0;
		Fy0Fzh = 0;
	}
	//int ade = 10;
}
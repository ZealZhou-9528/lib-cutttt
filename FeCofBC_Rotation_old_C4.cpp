#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> vectors_setdiff(vector<int> v1, vector<int> v2);
void FeCofBC_Rotation_old_C4(vector<double> &Tot_Bond_value, double &TotalVolume, vector<double> &dofFace, vector<double> &dofVaule, vector< vector<double> >& gcoord, int iopt)
{
	int nnode = gcoord.size();
	double Xmax = gcoord[0][0], Xmin = gcoord[0][0];
	double Ymax = gcoord[0][1], Ymin = gcoord[0][1];
	double Zmax = gcoord[0][2], Zmin = gcoord[0][2];
	for (size_t i = 1; i < gcoord.size(); i++)
	{
		if (Xmax < gcoord[i][0]) Xmax = gcoord[i][0];
		if (Xmin > gcoord[i][0]) Xmin = gcoord[i][0];
		if (Ymax < gcoord[i][1]) Ymax = gcoord[i][1];
		if (Ymin > gcoord[i][1]) Ymin = gcoord[i][1];
		if (Zmax < gcoord[i][2]) Zmax = gcoord[i][2];
		if (Zmin > gcoord[i][2]) Zmin = gcoord[i][2];

	}
	//vector<double> Tot_Bond_value(4, 0);
	Tot_Bond_value[0] = Xmin;
	Tot_Bond_value[1] = Xmax;
	Tot_Bond_value[2] = Ymin;
	Tot_Bond_value[3] = Ymax;
	TotalVolume = (Zmax - Zmin) * (Ymax - Ymin) * (Xmax - Xmin);
	vector<int> x0;
	for (size_t i = 0; i < gcoord.size(); i++)
	{
		if (gcoord[i][0] == Xmin) x0.push_back(i);
	}
	vector<int> y0;
	for (size_t i = 0; i < gcoord.size(); i++)
	{
		if (gcoord[i][1] == Ymin) y0.push_back(i);
	}
	vector<int> z0;
	for (size_t i = 0; i < gcoord.size(); i++)
	{
		if (gcoord[i][2] == Zmin) z0.push_back(i);
	}
	vector<int> xh;
	for (size_t i = 0; i < gcoord.size(); i++)
	{
		if (gcoord[i][0] == Xmax) xh.push_back(i);
	}
	vector<int> yh;
	for (size_t i = 0; i < gcoord.size(); i++)
	{
		if (gcoord[i][1] == Ymax) yh.push_back(i);
	}
	vector<int> zh;
	for (size_t i = 0; i < gcoord.size(); i++)
	{
		if (gcoord[i][2] == Zmax) zh.push_back(i);
	}
	/////////////////////////////////////////////
	vector<int> Fx0, Fxh, Fy0, Fyh, Fz0, Fzh;
	vector<int> x0h, y0h, z0h, x0hy0h, y0hz0h, x0hz0h;
	x0h = x0; y0h = y0; z0h = z0;
	for (size_t i = 0; i < xh.size(); i++)
	{
		x0h.push_back(xh[i]);
	}
	for (size_t i = 0; i < yh.size(); i++)
	{
		y0h.push_back(yh[i]);
	}
	for (size_t i = 0; i < zh.size(); i++)
	{
		z0h.push_back(zh[i]);
	}
	x0hy0h = x0h; y0hz0h = y0h; x0hz0h = x0h;
	for (size_t i = 0; i < y0h.size(); i++)
	{
		x0hy0h.push_back(y0h[i]);
	}
	for (size_t i = 0; i < z0h.size(); i++)
	{
		y0hz0h.push_back(z0h[i]);
	}
	for (size_t i = 0; i < z0h.size(); i++)
	{
		x0hz0h.push_back(z0h[i]);
	}
	///////////////////////////////////////
	vector<vector<double>> matix_e(3, vector<double>(3, 0));
	if (iopt == 1)
	{
		Fx0 = x0; Fxh = xh;
		Fy0 = vectors_setdiff(y0, x0h); Fyh = vectors_setdiff(yh, x0h);
		Fz0 = vectors_setdiff(z0, x0hy0h); Fzh = vectors_setdiff(zh, x0hy0h);
		matix_e[0][0] = 0.01; matix_e[0][1] = 0; matix_e[0][2] = 0;
		matix_e[1][0] = 0; matix_e[1][1] = 0; matix_e[1][2] = 0;
		matix_e[2][0] = 0; matix_e[2][1] = 0; matix_e[2][2] = 0;
	}
	else if(iopt == 2)
	{
		Fy0 = y0; Fyh = yh;
		Fx0 = vectors_setdiff(x0, y0h); Fxh = vectors_setdiff(xh, y0h);
		Fz0 = vectors_setdiff(z0, x0hy0h); Fzh = vectors_setdiff(zh, x0hy0h);
		matix_e[0][0] = 0; matix_e[0][1] = 0; matix_e[0][2] = 0;
		matix_e[1][0] = 0; matix_e[1][1] = 0.01; matix_e[1][2] = 0;
		matix_e[2][0] = 0; matix_e[2][1] = 0; matix_e[2][2] = 0;
	}
	else if (iopt == 3)
	{
		Fz0 = z0; Fzh = zh;
		Fy0 = vectors_setdiff(y0, z0h); Fyh = vectors_setdiff(yh, z0h);
		Fx0 = vectors_setdiff(x0, y0hz0h); Fxh = vectors_setdiff(xh, y0hz0h);
		matix_e[0][0] = 0; matix_e[0][1] = 0; matix_e[0][2] = 0;
		matix_e[1][0] = 0; matix_e[1][1] = 0; matix_e[1][2] = 0;
		matix_e[2][0] = 0; matix_e[2][1] = 0; matix_e[2][2] = 0.01;
	}
	else if (iopt == 4)
	{
		Fx0 = x0; Fxh = xh;
		Fy0 = vectors_setdiff(y0, x0h); Fyh = vectors_setdiff(yh, x0h);
		Fz0 = vectors_setdiff(z0, x0hy0h); Fzh = vectors_setdiff(zh, x0hy0h);
		matix_e[0][0] = 0; matix_e[0][1] = 0.01; matix_e[0][2] = 0;
		matix_e[1][0] = 0.01; matix_e[1][1] = 0; matix_e[1][2] = 0;
		matix_e[2][0] = 0; matix_e[2][1] = 0; matix_e[2][2] = 0;
	}
	else if (iopt == 5)
	{
		Fz0 = z0; Fzh = zh;
		Fx0 = vectors_setdiff(x0, z0h); Fxh = vectors_setdiff(xh, z0h);
		Fy0 = vectors_setdiff(y0, x0hz0h); Fyh = vectors_setdiff(yh, x0hz0h);
		matix_e[0][0] = 0; matix_e[0][1] = 0; matix_e[0][2] = 0.01;
		matix_e[1][0] = 0; matix_e[1][1] = 0; matix_e[1][2] = 0;
		matix_e[2][0] = 0.01; matix_e[2][1] = 0; matix_e[2][2] = 0;
	}
	else if (iopt == 6)
	{
		Fz0 = z0; Fzh = zh;
		Fy0 = vectors_setdiff(y0, z0h); Fyh = vectors_setdiff(yh, z0h);
		Fx0 = vectors_setdiff(x0, y0hz0h); Fxh = vectors_setdiff(xh, y0hz0h);
		matix_e[0][0] = 0; matix_e[0][1] = 0; matix_e[0][2] = 0;
		matix_e[1][0] = 0; matix_e[1][1] = 0; matix_e[1][2] = 0.01;
		matix_e[2][0] = 0; matix_e[2][1] = 0.01; matix_e[2][2] = 0;
	}
	///////////////////////////////////////////////////////////////
	vector<int> Face;
	//for (size_t i = 0; i < Fx0.size; i++)
	//{
	//	Face.push_back(Fx0[i]);
	//}
	Face.insert(Face.end(), Fx0.begin(), Fx0.end());
	Face.insert(Face.end(), Fxh.begin(), Fxh.end());
	Face.insert(Face.end(), Fy0.begin(), Fy0.end());
	Face.insert(Face.end(), Fyh.begin(), Fyh.end());
	Face.insert(Face.end(), Fz0.begin(), Fz0.end());
	Face.insert(Face.end(), Fzh.begin(), Fzh.end());
	//int LocRec = 0;
	////////////////////////////////////////////////
	//vector<int> dofFace;
	//vector<double> dofVaule;
	for (size_t i = 0; i < Face.size(); i++)
	{
		dofFace.push_back(3 * Face[i] );
		dofFace.push_back(3 * Face[i] + 1);
		dofFace.push_back(3 * Face[i] + 2);
		dofVaule.push_back(matix_e[0][0] * gcoord[Face[i]][0] + matix_e[0][1] * gcoord[Face[i]][1] + matix_e[0][2] * gcoord[Face[i]][2]);
		dofVaule.push_back(matix_e[1][0] * gcoord[Face[i]][0] + matix_e[1][1] * gcoord[Face[i]][1] + matix_e[1][2] * gcoord[Face[i]][2]);
		dofVaule.push_back(matix_e[2][0] * gcoord[Face[i]][0] + matix_e[2][1] * gcoord[Face[i]][1] + matix_e[2][2] * gcoord[Face[i]][2]);
	}
	////////////////////////////////////////
	int a0 = 0;
}

//vector<int> vectors_setdiff(vector<int> v1, vector<int> v2)
//{
//	vector<int> v;
//	int outpd = 0;
//	for (int i = 0; i < v1.size(); i++)
//	{
//		for (int i1 = 0; i1 < v2.size(); i1++)
//		{
//			if (v1[i] != v2[i1])
//			{
//				outpd = outpd + 1;
//			}
//		}
//		if (outpd == v2.size())
//		{
//			v.push_back(v1[i]);
//		}
//		outpd = 0;
//	}
//	sort(v.begin(), v.end());
//	v.erase(unique(v.begin(), v.end()), v.end());
//	return v;
//}
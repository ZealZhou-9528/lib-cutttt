#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> vectors_intersection(vector<int> v1, vector<int> v2);
vector<int> vectors_setdiff(vector<int> v1, vector<int> v2);
void FindSinglePoint(vector< vector<double> >& gcoord, vector< vector<int> >& nodes, vector<int> &SinglePointXmin, vector<int> &SinglePointXmax, vector<int> &SinglePointYmin, vector<int> &SinglePointYmax, vector<int> &SinglePointZmin, vector<int> &SinglePointZmax, vector<vector<vector<int> > > &Edge, vector<vector<int>> &SurfacePoint)
{
	double gdmax1 = gcoord[0][0], gdmin1 = gcoord[0][0];
	double gdmax2 = gcoord[0][1], gdmin2 = gcoord[0][1];
	double gdmax3 = gcoord[0][2], gdmin3 = gcoord[0][2];
	for (size_t i = 1; i < gcoord.size(); i++)
	{
		if (gdmax1 < gcoord[i][0]) gdmax1 = gcoord[i][0];
		//{gdmax1 = gcoord[i][0];}
		if (gdmin1 > gcoord[i][0]) gdmin1 = gcoord[i][0];
		//{gdmin1 = gcoord[i][0];}
		if (gdmax2 < gcoord[i][1]) gdmax2 = gcoord[i][1];
		//{gdmax2 = gcoord[i][1];}
		if (gdmin2 > gcoord[i][1]) gdmin2 = gcoord[i][1];
		//{gdmin2 = gcoord[i][1];}
		if (gdmax3 < gcoord[i][2]) gdmax3 = gcoord[i][2];
		//{gdmax3 = gcoord[i][2];}
		if (gdmin3 > gcoord[i][2]) gdmin3 = gcoord[i][2];
		//{gdmin3 = gcoord[i][2];}
	}
	vector<int> xmax, xmin, ymax, ymin, zmax, zmin;
	for (size_t i = 0; i < gcoord.size(); i++)
	{
		if (gcoord[i][0] == gdmax1) xmax.push_back(i);
		if (gcoord[i][0] == gdmin1) xmin.push_back(i);
		if (gcoord[i][1] == gdmax2) ymax.push_back(i);
		if (gcoord[i][1] == gdmin2) ymin.push_back(i);
		if (gcoord[i][2] == gdmax3) zmax.push_back(i);
		if (gcoord[i][2] == gdmin3) zmin.push_back(i);
	}
	//vector<vector<int>> SurfacePoint;
	//SurfacePoint.resize(6);
	for (size_t i = 0; i < xmin.size(); i++)
	{
		SurfacePoint[0].push_back(xmin[i]);
	}
	for (size_t i = 0; i < ymin.size(); i++)
	{
		SurfacePoint[1].push_back(ymin[i]);
	}
	for (size_t i = 0; i < zmin.size(); i++)
	{
		SurfacePoint[2].push_back(zmin[i]);
	}
	for (size_t i = 0; i < xmax.size(); i++)
	{
		SurfacePoint[3].push_back(xmax[i]);
	}
	for (size_t i = 0; i < ymax.size(); i++)
	{
		SurfacePoint[4].push_back(ymax[i]);
	}
	for (size_t i = 0; i < zmax.size(); i++)
	{
		SurfacePoint[5].push_back(zmax[i]);
	}

	vector<int> XL1,XL2,XL3,XL4;
	XL1 = vectors_intersection(ymin, zmin);
	XL2 = vectors_intersection(ymax, zmin);
	XL3 = vectors_intersection(ymin, zmax);
	XL4 = vectors_intersection(ymax, zmax);

	vector<int> YL1, YL2, YL3, YL4;
	YL1 = vectors_intersection(xmin, zmin);
	YL2 = vectors_intersection(xmax, zmin);
	YL3 = vectors_intersection(xmin, zmax);
	YL4 = vectors_intersection(xmax, zmax);

	vector<int> ZL1, ZL2, ZL3, ZL4;
	ZL1 = vectors_intersection(xmin, ymin);
	ZL2 = vectors_intersection(xmax, ymin);
	ZL3 = vectors_intersection(xmin, ymax);
	ZL4 = vectors_intersection(xmax, ymax);

	vector<int> XminEdge;
	for (size_t i = 0; i < YL1.size(); i++)
	{
		XminEdge.push_back(YL1[i]);
	}
	for (size_t i = 0; i < YL3.size(); i++)
	{
		XminEdge.push_back(YL3[i]);
	}
	for (size_t i = 0; i < ZL1.size(); i++)
	{
		XminEdge.push_back(ZL1[i]);
	}
	for (size_t i = 0; i < ZL3.size(); i++)
	{
		XminEdge.push_back(ZL3[i]);
	}
	sort(XminEdge.begin(), XminEdge.end());
	XminEdge.erase(unique(XminEdge.begin(), XminEdge.end()), XminEdge.end());
	vector<int> Xmin;
	Xmin = vectors_setdiff(xmin, XminEdge);

	vector<int> XmaxEdge;
	for (size_t i = 0; i < YL2.size(); i++)
	{
		XmaxEdge.push_back(YL2[i]);
	}
	for (size_t i = 0; i < YL4.size(); i++)
	{
		XmaxEdge.push_back(YL4[i]);
	}
	for (size_t i = 0; i < ZL2.size(); i++)
	{
		XmaxEdge.push_back(ZL2[i]);
	}
	for (size_t i = 0; i < ZL4.size(); i++)
	{
		XmaxEdge.push_back(ZL4[i]);
	}
	sort(XmaxEdge.begin(), XmaxEdge.end());
	XmaxEdge.erase(unique(XmaxEdge.begin(), XmaxEdge.end()), XmaxEdge.end());
	vector<int> Xmax;
	Xmax = vectors_setdiff(xmax, XmaxEdge);

	vector<int> YminEdge;
	for (size_t i = 0; i < XL1.size(); i++)
	{
		YminEdge.push_back(XL1[i]);
	}
	for (size_t i = 0; i < XL3.size(); i++)
	{
		YminEdge.push_back(XL3[i]);
	}
	for (size_t i = 0; i < ZL1.size(); i++)
	{
		YminEdge.push_back(ZL1[i]);
	}
	for (size_t i = 0; i < ZL2.size(); i++)
	{
		YminEdge.push_back(ZL2[i]);
	}
	sort(YminEdge.begin(), YminEdge.end());
	YminEdge.erase(unique(YminEdge.begin(), YminEdge.end()), YminEdge.end());
	vector<int> Ymin;
	Ymin = vectors_setdiff(ymin, YminEdge);

	vector<int> YmaxEdge;
	for (size_t i = 0; i < XL2.size(); i++)
	{
		YmaxEdge.push_back(XL2[i]);
	}
	for (size_t i = 0; i < XL4.size(); i++)
	{
		YmaxEdge.push_back(XL4[i]);
	}
	for (size_t i = 0; i < ZL3.size(); i++)
	{
		YmaxEdge.push_back(ZL3[i]);
	}
	for (size_t i = 0; i < ZL4.size(); i++)
	{
		YmaxEdge.push_back(ZL4[i]);
	}
	sort(YmaxEdge.begin(), YmaxEdge.end());
	YmaxEdge.erase(unique(YmaxEdge.begin(), YmaxEdge.end()), YmaxEdge.end());
	vector<int> Ymax;
	Ymax = vectors_setdiff(ymax, YmaxEdge);
	
	vector<int> ZminEdge;
	for (size_t i = 0; i < XL1.size(); i++)
	{
		ZminEdge.push_back(XL1[i]);
	}
	for (size_t i = 0; i < XL2.size(); i++)
	{
		ZminEdge.push_back(XL2[i]);
	}
	for (size_t i = 0; i < YL1.size(); i++)
	{
		ZminEdge.push_back(YL1[i]);
	}
	for (size_t i = 0; i < YL2.size(); i++)
	{
		ZminEdge.push_back(YL2[i]);
	}
	sort(ZminEdge.begin(), ZminEdge.end());
	ZminEdge.erase(unique(ZminEdge.begin(), ZminEdge.end()), ZminEdge.end());
	vector<int> Zmin;
	Zmin = vectors_setdiff(zmin, ZminEdge);

	vector<int> ZmaxEdge;
	for (size_t i = 0; i < XL3.size(); i++)
	{
		ZmaxEdge.push_back(XL3[i]);
	}
	for (size_t i = 0; i < XL4.size(); i++)
	{
		ZmaxEdge.push_back(XL4[i]);
	}
	for (size_t i = 0; i < YL3.size(); i++)
	{
		ZmaxEdge.push_back(YL3[i]);
	}
	for (size_t i = 0; i < YL4.size(); i++)
	{
		ZmaxEdge.push_back(YL4[i]);
	}
	sort(ZmaxEdge.begin(), ZmaxEdge.end());
	ZmaxEdge.erase(unique(ZmaxEdge.begin(), ZmaxEdge.end()), ZmaxEdge.end());
	vector<int> Zmax;
	Zmax = vectors_setdiff(zmax, ZmaxEdge);
	///////////////////////////////////////////////////
	int X11 = 0, X12 = 0, X13 = 0, X14 = 0, ie = 0;
	vector<double> aa;
	vector<double> bb;
	vector<double> cc;
	vector<int> mun,Num;
	for (size_t i = 0; i < Xmin.size(); i++)
	{
		ie = Xmin[i];
		aa.push_back(gcoord[ie][0]);
		aa.push_back(gcoord[ie][1]);
		aa.push_back(gcoord[ie][2]);
		for (size_t i1 = 0; i1 < Xmax.size(); i1++)
		{
			bb.push_back(gcoord[Xmax[i1]][1]);
		}
		for (size_t i2 = 0; i2 < Xmax.size(); i2++)
		{
			if (bb[i2]==aa[1])
			{
				mun.push_back(Xmax[i2]);
			}
		}
		for (size_t i3 = 0; i3 < mun.size(); i3++)
		{
			cc.push_back(gcoord[mun[i3]][2]);
		}
		X11 = X11 + 1;
		for (size_t i4 = 0; i4 < cc.size(); i4++)
		{
			if (cc[i4]==aa[2])
			{
				Num.push_back(i4);
			}
		}
		if (Num.size()==0)
		{
			X12 = X12 + 1;
			SinglePointXmin.push_back(Xmin[X11]);
		}
		else if (Num.size() == 1)
		{
			X13 = X13 + 1;
		}
		else if (Num.size() > 1)
		{
			X14 = X14 + 1;
		}
		aa.clear(), bb.clear(), cc.clear();
		mun.clear(), Num.clear();
	}
	//////////////////////////////////////////////////
	int X21 = 0, X22 = 0, X23 = 0, X24 = 0;
	for (size_t i = 0; i < Xmax.size(); i++)
	{
		ie = Xmax[i];
		aa.push_back(gcoord[ie][0]);
		aa.push_back(gcoord[ie][1]);
		aa.push_back(gcoord[ie][2]);
		for (size_t i1 = 0; i1 < Xmin.size(); i1++)
		{
			bb.push_back(gcoord[Xmin[i1]][1]);
		}
		for (size_t i2 = 0; i2 < Xmin.size(); i2++)
		{
			if (bb[i2] == aa[1])
			{
				mun.push_back(Xmin[i2]);
			}
		}
		for (size_t i3 = 0; i3 < mun.size(); i3++)
		{
			cc.push_back(gcoord[mun[i3]][2]);
		}
		X21 = X21 + 1;
		for (size_t i4 = 0; i4 < cc.size(); i4++)
		{
			if (cc[i4] == aa[2])
			{
				Num.push_back(i4);
			}
		}
		if (Num.size() == 0)
		{
			X22 = X22 + 1;
			SinglePointXmax.push_back(Xmax[X21]);
		}
		else if (Num.size() == 1)
		{
			X23 = X23 + 1;
		}
		else if (Num.size() > 1)
		{
			X24 = X24 + 1;
		}
		aa.clear(), bb.clear(), cc.clear();
		mun.clear(), Num.clear();
	}
	////////////////////////////////////////////////
	int Y11 = 0, Y12 = 0, Y13 = 0, Y14 = 0;
	for (size_t i = 0; i < Ymin.size(); i++)
	{
		ie = Ymin[i];
		aa.push_back(gcoord[ie][0]);
		aa.push_back(gcoord[ie][1]);
		aa.push_back(gcoord[ie][2]);
		for (size_t i1 = 0; i1 < Ymax.size(); i1++)
		{
			bb.push_back(gcoord[Ymax[i1]][0]);
		}
		for (size_t i2 = 0; i2 < Ymax.size(); i2++)
		{
			if (bb[i2] == aa[0])
			{
				mun.push_back(Ymax[i2]);
			}
		}
		for (size_t i3 = 0; i3 < mun.size(); i3++)
		{
			cc.push_back(gcoord[mun[i3]][2]);
		}
		Y11 = Y11 + 1;
		for (size_t i4 = 0; i4 < cc.size(); i4++)
		{
			if (cc[i4] == aa[2])
			{
				Num.push_back(i4);
			}
		}
		if (Num.size() == 0)
		{
			Y12 = Y12 + 1;
			SinglePointYmin.push_back(Ymin[Y11]);
		}
		else if (Num.size() == 1)
		{
			Y13 = Y13 + 1;
		}
		else if (Num.size() > 1)
		{
			Y14 = Y14 + 1;
		}
		aa.clear(), bb.clear(), cc.clear();
		mun.clear(), Num.clear();
	}

	int Y21 = 0, Y22 = 0, Y23 = 0, Y24 = 0;
	for (size_t i = 0; i < Ymax.size(); i++)
	{
		ie = Ymax[i];
		aa.push_back(gcoord[ie][0]);
		aa.push_back(gcoord[ie][1]);
		aa.push_back(gcoord[ie][2]);
		for (size_t i1 = 0; i1 < Ymin.size(); i1++)
		{
			bb.push_back(gcoord[Ymin[i1]][0]);
		}
		for (size_t i2 = 0; i2 < Ymin.size(); i2++)
		{
			if (bb[i2] == aa[0])
			{
				mun.push_back(Ymin[i2]);
			}
		}
		for (size_t i3 = 0; i3 < mun.size(); i3++)
		{
			cc.push_back(gcoord[mun[i3]][2]);
		}
		X21 = X21 + 1;
		for (size_t i4 = 0; i4 < cc.size(); i4++)
		{
			if (cc[i4] == aa[2])
			{
				Num.push_back(i4);
			}
		}
		if (Num.size() == 0)
		{
			Y22 = Y22 + 1;
			SinglePointYmax.push_back(Ymax[Y21]);
		}
		else if (Num.size() == 1)
		{
			Y23 = Y23 + 1;
		}
		else if (Num.size() > 1)
		{
			Y24 = Y24 + 1;
		}
		aa.clear(), bb.clear(), cc.clear();
		mun.clear(), Num.clear();
	}
	/////////////////////////////////////////////////////
	int Z11 = 0, Z12 = 0, Z13 = 0, Z14 = 0;
	for (size_t i = 0; i < Zmin.size(); i++)
	{
		ie = Zmin[i];
		aa.push_back(gcoord[ie][0]);
		aa.push_back(gcoord[ie][1]);
		aa.push_back(gcoord[ie][2]);
		for (size_t i1 = 0; i1 < Zmax.size(); i1++)
		{
			bb.push_back(gcoord[Zmax[i1]][0]);
		}
		for (size_t i2 = 0; i2 < Zmax.size(); i2++)
		{
			if (bb[i2] == aa[0])
			{
				mun.push_back(Zmax[i2]);
			}
		}
		for (size_t i3 = 0; i3 < mun.size(); i3++)
		{
			cc.push_back(gcoord[mun[i3]][1]);
		}
		Z11 = Z11 + 1;
		for (size_t i4 = 0; i4 < cc.size(); i4++)
		{
			if (cc[i4] == aa[1])
			{
				Num.push_back(i4);
			}
		}
		if (Num.size() == 0)
		{
			Z12 = Z12 + 1;
			SinglePointZmin.push_back(Zmin[Z11]);
		}
		else if (Num.size() == 1)
		{
			Z13 = Z13 + 1;
		}
		else if (Num.size() > 1)
		{
			Z14 = Z14 + 1;
		}
		aa.clear(), bb.clear(), cc.clear();
		mun.clear(), Num.clear();
	}
	/////////////////////////////////////////////////
	int Z21 = 0, Z22 = 0, Z23 = 0, Z24 = 0;
	for (size_t i = 0; i < Zmax.size(); i++)
	{
		ie = Zmax[i];
		aa.push_back(gcoord[ie][0]);
		aa.push_back(gcoord[ie][1]);
		aa.push_back(gcoord[ie][2]);
		for (size_t i1 = 0; i1 < Zmin.size(); i1++)
		{
			bb.push_back(gcoord[Zmin[i1]][0]);
		}
		for (size_t i2 = 0; i2 < Zmin.size(); i2++)
		{
			if (bb[i2] == aa[0])
			{
				mun.push_back(Zmin[i2]);
			}
		}
		for (size_t i3 = 0; i3 < mun.size(); i3++)
		{
			cc.push_back(gcoord[mun[i3]][1]);
		}
		Z21 = Z21 + 1;
		for (size_t i4 = 0; i4 < cc.size(); i4++)
		{
			if (cc[i4] == aa[1])
			{
				Num.push_back(i4);
			}
		}
		if (Num.size() == 0)
		{
			Z22 = Z22 + 1;
			SinglePointZmax.push_back(Zmax[Z21]);
		}
		else if (Num.size() == 1)
		{
			Z23 = Z23 + 1;
		}
		else if (Num.size() > 1)
		{
			Z24 = Z24 + 1;
		}
		aa.clear(), bb.clear(), cc.clear();
		mun.clear(), Num.clear();
	}
	///////////////////////////////////////////////
	vector<int> Xedge;
	for (size_t i = 0; i < XL1.size(); i++)
	{
		Xedge.push_back(XL1[i]);
	}
	for (size_t i = 0; i < XL2.size(); i++)
	{
		Xedge.push_back(XL2[i]);
	}
	for (size_t i = 0; i < XL3.size(); i++)
	{
		Xedge.push_back(XL3[i]);
	}
	for (size_t i = 0; i < XL4.size(); i++)
	{
		Xedge.push_back(XL4[i]);
	}
	/////////////////////////////////////////
	vector<int> Yedge;
	for (size_t i = 0; i < YL1.size(); i++)
	{
		Yedge.push_back(YL1[i]);
	}
	for (size_t i = 0; i < YL2.size(); i++)
	{
		Yedge.push_back(YL2[i]);
	}
	for (size_t i = 0; i < YL3.size(); i++)
	{
		Yedge.push_back(YL3[i]);
	}
	for (size_t i = 0; i < YL4.size(); i++)
	{
		Yedge.push_back(YL4[i]);
	}
	//////////////////////////////////////////
	vector<int> Zedge;
	for (size_t i = 0; i < ZL1.size(); i++)
	{
		Zedge.push_back(ZL1[i]);
	}
	for (size_t i = 0; i < ZL2.size(); i++)
	{
		Zedge.push_back(ZL2[i]);
	}
	for (size_t i = 0; i < ZL3.size(); i++)
	{
		Zedge.push_back(ZL3[i]);
	}
	for (size_t i = 0; i < ZL4.size(); i++)
	{
		Zedge.push_back(ZL4[i]);
	}
	/////////////////////////////////////////////
	//vector<vector<vector<int> > > Edge(4);//创建2个vector<vector<int> >类型的数组
	//for (int n = 0; n < 4; n++)
	//{
	//	Edge[n].resize(4);
	//}
	//第一行
	Edge[0].push_back(Xedge);
	//for (size_t i = 0; i < Xedge.size(); i++)
	//{
	//	Edge[0][0].push_back(Xedge[i]);
	//}
	Edge[0].push_back(Yedge);
	//for (size_t i = 0; i < Yedge.size(); i++)
	//{
	//	Edge[0][1].push_back(Yedge[i]);
	//}
	Edge[0].push_back(Zedge);
	//for (size_t i = 0; i < Zedge.size(); i++)
	//{
	//	Edge[0][2].push_back(Zedge[i]);
	//}
	//第二行
	Edge[1].push_back(XL1);
	//for (size_t i = 0; i < XL1.size(); i++)
	//{
	//	Edge[1][0].push_back(XL1[i]);
	//}
	Edge[1].push_back(XL2);
	//for (size_t i = 0; i < XL2.size(); i++)
	//{
	//	Edge[1][1].push_back(XL2[i]);
	//}
	Edge[1].push_back(XL3);
	//for (size_t i = 0; i < XL3.size(); i++)
	//{
	//	Edge[1][2].push_back(XL3[i]);
	//}
	Edge[1].push_back(XL4);
	//for (size_t i = 0; i < XL4.size(); i++)
	//{
	//	Edge[1][3].push_back(XL4[i]);
	//}
	//第三行
	Edge[2].push_back(YL1);
	Edge[2].push_back(YL2);
	Edge[2].push_back(YL3);
	Edge[2].push_back(YL4);
	/*for (size_t i = 0; i < YL1.size(); i++)
	{
		Edge[2][0].push_back(YL1[i]);
	}
	for (size_t i = 0; i < YL2.size(); i++)
	{
		Edge[2][1].push_back(YL2[i]);
	}
	for (size_t i = 0; i < YL3.size(); i++)
	{
		Edge[2][2].push_back(YL3[i]);
	}
	for (size_t i = 0; i < YL4.size(); i++)
	{
		Edge[2][3].push_back(YL4[i]);
	}*/
	//第四行
	Edge[3].push_back(ZL1);
	Edge[3].push_back(ZL2);
	Edge[3].push_back(ZL3);
	Edge[3].push_back(ZL4);
	/*for (size_t i = 0; i < ZL1.size(); i++)
	{
		Edge[3][0].push_back(ZL1[i]);
	}
	for (size_t i = 0; i < ZL2.size(); i++)
	{
		Edge[3][1].push_back(ZL2[i]);
	}
	for (size_t i = 0; i < ZL3.size(); i++)
	{
		Edge[3][2].push_back(YL3[i]);
	}
	for (size_t i = 0; i < ZL4.size(); i++)
	{
		Edge[3][3].push_back(ZL4[i]);
	}*/
}



//vector<int> vectors_intersection(vector<int> v1, vector<int> v2) 
//{
//	vector<int> v;
//	sort(v1.begin(), v1.end());
//	sort(v2.begin(), v2.end());
//	set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v));//求交集 
//	return v;
//}
//
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

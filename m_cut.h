#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void ModelGenerationCUBE(double SideLength, int CutNum, int nn, int NLeng, int Nx, int Ny, int Nz, vector< vector<double> >& gcoord, vector< vector<int> >& nodes, int wmth);
//void ModelGenerationCUBE_da(double SideLength, int CutNum, int nn, int NLeng, int Nx, int Ny, int Nz, double** gcoord, double** nodes, int wmth);
void CutModel(vector< vector<double> >& gcoord, vector< vector<int> >& nodes, vector< vector<int> >& InnerElementsmain, vector<int>& OuterElementsmain, double CircumR, double CircumRint, double Magnitude, double CrossSectExp, double p, double q);
void CutModel2st(vector< vector<double> >& gcoord, vector< vector<int> >& nodes, vector< vector<int> >& InnerElementsmain, vector<int>& OuterElementsmain, double CircumR, double CircumRint, double Magnitude, double CrossSectExp, double p, double q);
void FEXMLoutput(double index_xyz, vector< vector<double> > gcoord, vector< vector<int> > nodes, vector<int> FiberElement, string Filename, int filenumber);
void MianModuli(vector< vector<double> >& gcoord, vector< vector<int> >& nodes, vector< vector<int> >& FiberEle, vector<int>& Interstitial, double Magnitude, int Curve);
void CutModel_3D(vector< vector<double> >& gcoord, vector< vector<int> >& nodes, vector< vector<int> >& InnerElementsmain, vector<int>& OuterElementsmain, double CircumR, double CircumRint, double Magnitude, double CrossSectExp, double p, double q);
void CutModel_25D(vector< vector<double> >& gcoord, vector< vector<int> >& nodes, vector< vector<int> >& InnerElementsmain, vector<int>& OuterElementsmain, double CircumR, double CircumRint, double Magnitude, double CrossSectExp, double p, double q);
void CutModel2st_25D(vector< vector<double> > & gcoord, vector< vector<int> > & nodes, vector< vector<int> > & InnerElementsmain, vector<int> & OuterElementsmain, double CircumR, double CircumRint, double Magnitude, double CrossSectExp, double p, double q); #pragma once

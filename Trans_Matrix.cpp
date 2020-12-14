#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<vector<double>> Trans_Matrix(vector<double> xcoord, vector<double> ycoord, vector<double> zcoord, double Magnitude, int N)
{
	double a = Magnitude;
	int b = 5;
	double pi = 3.141592653589793115997963468544185161590576171875;
	double pointX, pointY, theta;
	double Q11, Q12, Q13, Q21, Q22, Q23, Q31, Q32, Q33;
	vector<vector<double>> Trans_matrix(6, vector<double>(6, 0));
	if (N == 1)
	{
		pointX = 0.25 * (xcoord[0] + xcoord[1] + xcoord[2] + xcoord[3]);
		theta = atan((pi * a) / b * cos(((pointX + 0.5 * b) / b) * pi));
		Q11 = cos(pi / 2 - theta); Q12 = cos(pi / 2); Q13 = cos(pi - theta);
		Q21 = cos(pi / 2);         Q22 = cos(0);      Q23 = cos(pi / 2);
		Q31 = cos(theta);          Q32 = cos(pi / 2); Q33 = cos(pi / 2 - theta);

		//vector<vector<double>> Trans_matrix(6, vector<double>(6, 0));
		Trans_matrix[0][0] = Q11 * Q11; Trans_matrix[0][1] = Q12 * Q12; Trans_matrix[0][2] = Q13 * Q13; Trans_matrix[0][3] = (Q12 * Q13) * sqrt(2); Trans_matrix[0][4] = (Q13 * Q11) * sqrt(2); Trans_matrix[0][5] = (Q11 * Q12) * sqrt(2);
		Trans_matrix[1][0] = Q21 * Q21; Trans_matrix[1][1] = Q22 * Q22; Trans_matrix[1][2] = Q23 * Q23; Trans_matrix[1][3] = (Q22 * Q23) * sqrt(2); Trans_matrix[1][4] = (Q23 * Q21) * sqrt(2); Trans_matrix[1][5] = (Q21 * Q22) * sqrt(2);
		Trans_matrix[2][0] = Q31 * Q31; Trans_matrix[2][1] = Q32 * Q32; Trans_matrix[2][2] = Q33 * Q33; Trans_matrix[2][3] = (Q32 * Q33) * sqrt(2); Trans_matrix[2][4] = (Q33 * Q31) * sqrt(2); Trans_matrix[2][5] = (Q31 * Q32) * sqrt(2);
		Trans_matrix[3][0] = sqrt(2) * Q21 * Q31; Trans_matrix[3][1] = sqrt(2) * Q22 * Q32; Trans_matrix[3][2] = sqrt(2) * Q23 * Q33; Trans_matrix[3][3] = (Q22 * Q33 + Q32 * Q23); Trans_matrix[3][4] = (Q23 * Q31 + Q33 * Q21); Trans_matrix[3][5] = (Q21 * Q32 + Q31 * Q22);
		Trans_matrix[4][0] = sqrt(2) * Q31 * Q11; Trans_matrix[4][1] = sqrt(2) * Q32 * Q12; Trans_matrix[4][2] = sqrt(2) * Q33 * Q13; Trans_matrix[4][3] = (Q32 * Q13 + Q12 * Q33); Trans_matrix[4][4] = (Q33 * Q11 + Q13 * Q31); Trans_matrix[4][5] = (Q31 * Q12 + Q11 * Q32);
		Trans_matrix[5][0] = sqrt(2) * Q11 * Q21; Trans_matrix[5][1] = sqrt(2) * Q12 * Q22; Trans_matrix[5][2] = sqrt(2) * Q13 * Q23; Trans_matrix[5][3] = (Q12 * Q23 + Q22 * Q13); Trans_matrix[5][4] = (Q13 * Q21 + Q23 * Q11); Trans_matrix[5][5] = (Q11 * Q22 + Q21 * Q12);
	}
	else if (N == 2)
	{
		pointX = 0.25 * (xcoord[0] + xcoord[1] + xcoord[2] + xcoord[3]);
		theta = atan((pi * a) / b * cos(((pointX + 0.5 * b) / b) * pi));
		Q11 = cos(pi / 2 - theta); Q12 = cos(pi / 2); Q13 = cos(pi - theta);
		Q21 = cos(pi / 2);         Q22 = cos(0);      Q23 = cos(pi / 2);
		Q31 = cos(theta);          Q32 = cos(pi / 2); Q33 = cos(pi / 2 - theta);

		//vector<vector<double>> Trans_matrix(6, vector<double>(6, 0));
		Trans_matrix[0][0] = Q11 * Q11; Trans_matrix[0][1] = Q12 * Q12; Trans_matrix[0][2] = Q13 * Q13; Trans_matrix[0][3] = (Q12 * Q13) * sqrt(2); Trans_matrix[0][4] = (Q13 * Q11) * sqrt(2); Trans_matrix[0][5] = (Q11 * Q12) * sqrt(2);
		Trans_matrix[1][0] = Q21 * Q21; Trans_matrix[1][1] = Q22 * Q22; Trans_matrix[1][2] = Q23 * Q23; Trans_matrix[1][3] = (Q22 * Q23) * sqrt(2); Trans_matrix[1][4] = (Q23 * Q21) * sqrt(2); Trans_matrix[1][5] = (Q21 * Q22) * sqrt(2);
		Trans_matrix[2][0] = Q31 * Q31; Trans_matrix[2][1] = Q32 * Q32; Trans_matrix[2][2] = Q33 * Q33; Trans_matrix[2][3] = (Q32 * Q33) * sqrt(2); Trans_matrix[2][4] = (Q33 * Q31) * sqrt(2); Trans_matrix[2][5] = (Q31 * Q32) * sqrt(2);
		Trans_matrix[3][0] = sqrt(2) * Q21 * Q31; Trans_matrix[3][1] = sqrt(2) * Q22 * Q32; Trans_matrix[3][2] = sqrt(2) * Q23 * Q33; Trans_matrix[3][3] = (Q22 * Q33 + Q32 * Q23); Trans_matrix[3][4] = (Q23 * Q31 + Q33 * Q21); Trans_matrix[3][5] = (Q21 * Q32 + Q31 * Q22);
		Trans_matrix[4][0] = sqrt(2) * Q31 * Q11; Trans_matrix[4][1] = sqrt(2) * Q32 * Q12; Trans_matrix[4][2] = sqrt(2) * Q33 * Q13; Trans_matrix[4][3] = (Q32 * Q13 + Q12 * Q33); Trans_matrix[4][4] = (Q33 * Q11 + Q13 * Q31); Trans_matrix[4][5] = (Q31 * Q12 + Q11 * Q32);
		Trans_matrix[5][0] = sqrt(2) * Q11 * Q21; Trans_matrix[5][1] = sqrt(2) * Q12 * Q22; Trans_matrix[5][2] = sqrt(2) * Q13 * Q23; Trans_matrix[5][3] = (Q12 * Q23 + Q22 * Q13); Trans_matrix[5][4] = (Q13 * Q21 + Q23 * Q11); Trans_matrix[5][5] = (Q11 * Q22 + Q21 * Q12);
	}
	else if (N == 3)
	{
		pointX = 0.25 * (xcoord[0] + xcoord[1] + xcoord[2] + xcoord[3]);
		theta = atan((pi * a) / b * cos(((pointX + 1.5 * b) / b) * pi));
		Q11 = cos(pi / 2 - theta); Q12 = cos(pi / 2); Q13 = cos(pi - theta);
		Q21 = cos(pi / 2);         Q22 = cos(0);      Q23 = cos(pi / 2);
		Q31 = cos(theta);          Q32 = cos(pi / 2); Q33 = cos(pi / 2 - theta);

		//vector<vector<double>> Trans_matrix(6, vector<double>(6, 0));
		Trans_matrix[0][0] = Q11 * Q11; Trans_matrix[0][1] = Q12 * Q12; Trans_matrix[0][2] = Q13 * Q13; Trans_matrix[0][3] = (Q12 * Q13) * sqrt(2); Trans_matrix[0][4] = (Q13 * Q11) * sqrt(2); Trans_matrix[0][5] = (Q11 * Q12) * sqrt(2);
		Trans_matrix[1][0] = Q21 * Q21; Trans_matrix[1][1] = Q22 * Q22; Trans_matrix[1][2] = Q23 * Q23; Trans_matrix[1][3] = (Q22 * Q23) * sqrt(2); Trans_matrix[1][4] = (Q23 * Q21) * sqrt(2); Trans_matrix[1][5] = (Q21 * Q22) * sqrt(2);
		Trans_matrix[2][0] = Q31 * Q31; Trans_matrix[2][1] = Q32 * Q32; Trans_matrix[2][2] = Q33 * Q33; Trans_matrix[2][3] = (Q32 * Q33) * sqrt(2); Trans_matrix[2][4] = (Q33 * Q31) * sqrt(2); Trans_matrix[2][5] = (Q31 * Q32) * sqrt(2);
		Trans_matrix[3][0] = sqrt(2) * Q21 * Q31; Trans_matrix[3][1] = sqrt(2) * Q22 * Q32; Trans_matrix[3][2] = sqrt(2) * Q23 * Q33; Trans_matrix[3][3] = (Q22 * Q33 + Q32 * Q23); Trans_matrix[3][4] = (Q23 * Q31 + Q33 * Q21); Trans_matrix[3][5] = (Q21 * Q32 + Q31 * Q22);
		Trans_matrix[4][0] = sqrt(2) * Q31 * Q11; Trans_matrix[4][1] = sqrt(2) * Q32 * Q12; Trans_matrix[4][2] = sqrt(2) * Q33 * Q13; Trans_matrix[4][3] = (Q32 * Q13 + Q12 * Q33); Trans_matrix[4][4] = (Q33 * Q11 + Q13 * Q31); Trans_matrix[4][5] = (Q31 * Q12 + Q11 * Q32);
		Trans_matrix[5][0] = sqrt(2) * Q11 * Q21; Trans_matrix[5][1] = sqrt(2) * Q12 * Q22; Trans_matrix[5][2] = sqrt(2) * Q13 * Q23; Trans_matrix[5][3] = (Q12 * Q23 + Q22 * Q13); Trans_matrix[5][4] = (Q13 * Q21 + Q23 * Q11); Trans_matrix[5][5] = (Q11 * Q22 + Q21 * Q12);
	}
	else if (N == 4)
	{
		pointY = 0.25 * (ycoord[0] + ycoord[1] + ycoord[2] + ycoord[3]);
		theta = atan((pi * a) / b * cos(((pointY + 0.5 * b) / b) * pi));
		Q11 = cos(0);          Q12 = cos(pi / 2);              Q13 = cos(pi / 2);
		Q21 = cos(pi / 2);     Q22 = cos(pi / 2 - theta);      Q23 = cos(pi - theta);
		Q31 = cos(pi / 2);     Q32 = cos(theta);               Q33 = cos(pi / 2 - theta);

		//vector<vector<double>> Trans_matrix(6, vector<double>(6, 0));
		Trans_matrix[0][0] = Q11 * Q11; Trans_matrix[0][1] = Q12 * Q12; Trans_matrix[0][2] = Q13 * Q13; Trans_matrix[0][3] = (Q12 * Q13) * sqrt(2); Trans_matrix[0][4] = (Q13 * Q11) * sqrt(2); Trans_matrix[0][5] = (Q11 * Q12) * sqrt(2);
		Trans_matrix[1][0] = Q21 * Q21; Trans_matrix[1][1] = Q22 * Q22; Trans_matrix[1][2] = Q23 * Q23; Trans_matrix[1][3] = (Q22 * Q23) * sqrt(2); Trans_matrix[1][4] = (Q23 * Q21) * sqrt(2); Trans_matrix[1][5] = (Q21 * Q22) * sqrt(2);
		Trans_matrix[2][0] = Q31 * Q31; Trans_matrix[2][1] = Q32 * Q32; Trans_matrix[2][2] = Q33 * Q33; Trans_matrix[2][3] = (Q32 * Q33) * sqrt(2); Trans_matrix[2][4] = (Q33 * Q31) * sqrt(2); Trans_matrix[2][5] = (Q31 * Q32) * sqrt(2);
		Trans_matrix[3][0] = sqrt(2) * Q21 * Q31; Trans_matrix[3][1] = sqrt(2) * Q22 * Q32; Trans_matrix[3][2] = sqrt(2) * Q23 * Q33; Trans_matrix[3][3] = (Q22 * Q33 + Q32 * Q23); Trans_matrix[3][4] = (Q23 * Q31 + Q33 * Q21); Trans_matrix[3][5] = (Q21 * Q32 + Q31 * Q22);
		Trans_matrix[4][0] = sqrt(2) * Q31 * Q11; Trans_matrix[4][1] = sqrt(2) * Q32 * Q12; Trans_matrix[4][2] = sqrt(2) * Q33 * Q13; Trans_matrix[4][3] = (Q32 * Q13 + Q12 * Q33); Trans_matrix[4][4] = (Q33 * Q11 + Q13 * Q31); Trans_matrix[4][5] = (Q31 * Q12 + Q11 * Q32);
		Trans_matrix[5][0] = sqrt(2) * Q11 * Q21; Trans_matrix[5][1] = sqrt(2) * Q12 * Q22; Trans_matrix[5][2] = sqrt(2) * Q13 * Q23; Trans_matrix[5][3] = (Q12 * Q23 + Q22 * Q13); Trans_matrix[5][4] = (Q13 * Q21 + Q23 * Q11); Trans_matrix[5][5] = (Q11 * Q22 + Q21 * Q12);
	}
	else if (N == 5)
	{
		pointY = 0.25 * (ycoord[0] + ycoord[1] + ycoord[2] + ycoord[3]);
		theta = atan((pi * a) / b * cos(((pointY + 1.5 * b) / b) * pi));
		Q11 = cos(0);          Q12 = cos(pi / 2);              Q13 = cos(pi / 2);
		Q21 = cos(pi / 2);     Q22 = cos(pi / 2 - theta);      Q23 = cos(pi - theta);
		Q31 = cos(pi / 2);     Q32 = cos(theta);               Q33 = cos(pi / 2 - theta);

		//vector<vector<double>> Trans_matrix(6, vector<double>(6, 0));
		Trans_matrix[0][0] = Q11 * Q11; Trans_matrix[0][1] = Q12 * Q12; Trans_matrix[0][2] = Q13 * Q13; Trans_matrix[0][3] = (Q12 * Q13) * sqrt(2); Trans_matrix[0][4] = (Q13 * Q11) * sqrt(2); Trans_matrix[0][5] = (Q11 * Q12) * sqrt(2);
		Trans_matrix[1][0] = Q21 * Q21; Trans_matrix[1][1] = Q22 * Q22; Trans_matrix[1][2] = Q23 * Q23; Trans_matrix[1][3] = (Q22 * Q23) * sqrt(2); Trans_matrix[1][4] = (Q23 * Q21) * sqrt(2); Trans_matrix[1][5] = (Q21 * Q22) * sqrt(2);
		Trans_matrix[2][0] = Q31 * Q31; Trans_matrix[2][1] = Q32 * Q32; Trans_matrix[2][2] = Q33 * Q33; Trans_matrix[2][3] = (Q32 * Q33) * sqrt(2); Trans_matrix[2][4] = (Q33 * Q31) * sqrt(2); Trans_matrix[2][5] = (Q31 * Q32) * sqrt(2);
		Trans_matrix[3][0] = sqrt(2) * Q21 * Q31; Trans_matrix[3][1] = sqrt(2) * Q22 * Q32; Trans_matrix[3][2] = sqrt(2) * Q23 * Q33; Trans_matrix[3][3] = (Q22 * Q33 + Q32 * Q23); Trans_matrix[3][4] = (Q23 * Q31 + Q33 * Q21); Trans_matrix[3][5] = (Q21 * Q32 + Q31 * Q22);
		Trans_matrix[4][0] = sqrt(2) * Q31 * Q11; Trans_matrix[4][1] = sqrt(2) * Q32 * Q12; Trans_matrix[4][2] = sqrt(2) * Q33 * Q13; Trans_matrix[4][3] = (Q32 * Q13 + Q12 * Q33); Trans_matrix[4][4] = (Q33 * Q11 + Q13 * Q31); Trans_matrix[4][5] = (Q31 * Q12 + Q11 * Q32);
		Trans_matrix[5][0] = sqrt(2) * Q11 * Q21; Trans_matrix[5][1] = sqrt(2) * Q12 * Q22; Trans_matrix[5][2] = sqrt(2) * Q13 * Q23; Trans_matrix[5][3] = (Q12 * Q23 + Q22 * Q13); Trans_matrix[5][4] = (Q13 * Q21 + Q23 * Q11); Trans_matrix[5][5] = (Q11 * Q22 + Q21 * Q12);
	}
	else if (N == 6)
	{
		pointY = 0.25 * (ycoord[0] + ycoord[1] + ycoord[2] + ycoord[3]);
		theta = atan((pi * a) / b * cos(((pointY + 0.5 * b) / b) * pi));
		Q11 = cos(0);          Q12 = cos(pi / 2);              Q13 = cos(pi / 2);
		Q21 = cos(pi / 2);     Q22 = cos(pi / 2 - theta);      Q23 = cos(pi - theta);
		Q31 = cos(pi / 2);     Q32 = cos(theta);               Q33 = cos(pi / 2 - theta);

		//vector<vector<double>> Trans_matrix(6, vector<double>(6, 0));
		Trans_matrix[0][0] = Q11 * Q11; Trans_matrix[0][1] = Q12 * Q12; Trans_matrix[0][2] = Q13 * Q13; Trans_matrix[0][3] = (Q12 * Q13) * sqrt(2); Trans_matrix[0][4] = (Q13 * Q11) * sqrt(2); Trans_matrix[0][5] = (Q11 * Q12) * sqrt(2);
		Trans_matrix[1][0] = Q21 * Q21; Trans_matrix[1][1] = Q22 * Q22; Trans_matrix[1][2] = Q23 * Q23; Trans_matrix[1][3] = (Q22 * Q23) * sqrt(2); Trans_matrix[1][4] = (Q23 * Q21) * sqrt(2); Trans_matrix[1][5] = (Q21 * Q22) * sqrt(2);
		Trans_matrix[2][0] = Q31 * Q31; Trans_matrix[2][1] = Q32 * Q32; Trans_matrix[2][2] = Q33 * Q33; Trans_matrix[2][3] = (Q32 * Q33) * sqrt(2); Trans_matrix[2][4] = (Q33 * Q31) * sqrt(2); Trans_matrix[2][5] = (Q31 * Q32) * sqrt(2);
		Trans_matrix[3][0] = sqrt(2) * Q21 * Q31; Trans_matrix[3][1] = sqrt(2) * Q22 * Q32; Trans_matrix[3][2] = sqrt(2) * Q23 * Q33; Trans_matrix[3][3] = (Q22 * Q33 + Q32 * Q23); Trans_matrix[3][4] = (Q23 * Q31 + Q33 * Q21); Trans_matrix[3][5] = (Q21 * Q32 + Q31 * Q22);
		Trans_matrix[4][0] = sqrt(2) * Q31 * Q11; Trans_matrix[4][1] = sqrt(2) * Q32 * Q12; Trans_matrix[4][2] = sqrt(2) * Q33 * Q13; Trans_matrix[4][3] = (Q32 * Q13 + Q12 * Q33); Trans_matrix[4][4] = (Q33 * Q11 + Q13 * Q31); Trans_matrix[4][5] = (Q31 * Q12 + Q11 * Q32);
		Trans_matrix[5][0] = sqrt(2) * Q11 * Q21; Trans_matrix[5][1] = sqrt(2) * Q12 * Q22; Trans_matrix[5][2] = sqrt(2) * Q13 * Q23; Trans_matrix[5][3] = (Q12 * Q23 + Q22 * Q13); Trans_matrix[5][4] = (Q13 * Q21 + Q23 * Q11); Trans_matrix[5][5] = (Q11 * Q22 + Q21 * Q12);
	}
	return Trans_matrix;
}
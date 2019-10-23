#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <math.h>

#define PI 3.14159265358979323846  //hmmm

#include "GA.h"

float Objective(unsigned ndv, const float* DV)
{
	float sum = 0;
	for (unsigned v = 0; v < ndv; v++)
	{
		sum += DV[v];
	}
	return sum;
}

float ex1GE(unsigned ndv, const float* DV)
{
	float val = DV[3];
	return val - 6;
}
float ex2GE(unsigned ndv, const float* DV)
{
	return DV[2] - 3;
}
float ex3GE(unsigned ndv, const float* DV)
{
	float sum = 0;
	for (unsigned v = 0; v < ndv; v++)
	{
		sum += DV[v];
	}
	return sum - 11;
}
float ex1EQ(unsigned ndv, const float* DV)
{
	return DV[1] - 1;
}
//FitnessFunc* FitFunc = create_FitFunc(4, 1, 0, 3, MIN, Objective);
//add_eq(FitFunc, ex1EQ);
//add_ge(FitFunc, ex1GE);
//add_ge(FitFunc, ex2GE);
//add_ge(FitFunc, ex3GE);
//GAbool tool = check_fitfuncOK(FitFunc);
//
//printf("Press something to continue\n");
//getchar();
//
//float UB[4] = { 15, 15, 15, 15 };
//float LB[4] = { 0, 0, 0, 0 };
//
////float problem[4] = { 1, 1, 3, 8 };
//
////float val = eval_Fitfunc(FitFunc, 4, problem);
//
//optimPop_Min(4, FitFunc, UB, LB);
//
//printf("\nPress something to continue\n");
//getchar();
//
//destroy_FitFunc(FitFunc);

//p1
float p1_Obj(unsigned ndv, const float* DV)
{
	float b1 = DV[0];
	float b2 = DV[1];
	float weight = 2 * sqrtf(2) * b1 + b2;
	return weight;
}
float p1_LE1(unsigned ndv, const float* DV)
{
	float b1 = DV[0];
	float b2 = DV[1];
	float root2 = sqrtf(2);
	float root2over2 = root2 / 2;
	float b1part = .866025 / b1;
	float b2part = .5 / (b1 + (root2 * b2));
	float parens = b1part + b2part;
	float val = fabs(root2over2 * parens);
	return val - 1;
}
float p1_LE2(unsigned ndv, const float* DV)
{
	float b1 = DV[0];
	float b2 = DV[1];
	float root2 = sqrtf(2);
	float root2over2 = root2 / 2;
	float denom = b1 + (root2 * b2);
	float parens = 1 / denom;
	float val = fabs(root2over2 * parens);
	return val - 1;
}
void p1()
{
	FitnessFunc* FitFunc = create_FitFunc(2, 0, 2, 0, MIN, p1_Obj, GA_FALSE);
	add_le(FitFunc, p1_LE1);
	add_le(FitFunc, p1_LE2);
	GAbool tool = check_fitfuncOK(FitFunc);

	printf("FitFunc check is: %i Press something to continue\n", tool);
	getchar();

	float UB[2] = { 2, 2 };
	float LB[2] = { 0, 0 };

	optimPop_Min(2, FitFunc, UB, LB);  //deja vu

	printf("\nPress something to continue\n");
	getchar();

	destroy_FitFunc(FitFunc);
}

float p2_Obj(unsigned ndv, const float* DV)
{
	float Ro_1 = DV[0];
	float Ri_1 = DV[1];
	float Ro_2 = DV[2];
	float Ri_2 = DV[3];
	float RoRi_1 = Ro_1 - Ri_1;
	float sqrd1 = RoRi_1 * RoRi_1;
	float RoRi_2 = Ro_2 - Ri_2;
	float sqrd2 = RoRi_2 * RoRi_2;
	float b1 = PI * sqrd1;
	float b2 = PI * sqrd2;

	float weight = 2 * sqrtf(2) * b1 + b2;
	return weight;
}
float p2_LE1(unsigned ndv, const float* DV)
{
	float Ro_1 = DV[0];
	float Ri_1 = DV[1];
	float Ro_2 = DV[2];
	float Ri_2 = DV[3];
	float RoRi_1 = Ro_1 - Ri_1;
	float sqrd1 = RoRi_1 * RoRi_1;
	float RoRi_2 = Ro_2 - Ri_2;
	float sqrd2 = RoRi_2 * RoRi_2;
	float b1 = PI * sqrd1;
	float b2 = PI * sqrd2;

	float root2 = sqrtf(2);
	float root2over2 = root2 / 2;
	float b1part = .866025 / b1;
	float b2part = .5 / (b1 + (root2 * b2));
	float parens = b1part + b2part;
	float val = fabs(root2over2 * parens);
	return val - 1;
}
float p2_LE2(unsigned ndv, const float* DV)
{
	float Ro_1 = DV[0];
	float Ri_1 = DV[1];
	float Ro_2 = DV[2];
	float Ri_2 = DV[3];
	float RoRi_1 = Ro_1 - Ri_1;
	float sqrd1 = RoRi_1 * RoRi_1;
	float RoRi_2 = Ro_2 - Ri_2;
	float sqrd2 = RoRi_2 * RoRi_2;
	float b1 = PI * sqrd1;
	float b2 = PI * sqrd2;

	float root2 = sqrtf(2);
	float root2over2 = root2 / 2;
	float denom = b1 + (root2 * b2);
	float parens = 1 / denom;
	float val = fabs(root2over2 * parens);
	return val - 1;
}
float p2_LE3(unsigned ndv, const float* DV)
{
	float Ro_1 = DV[0];
	float Ri_1 = DV[1];
	float RoRi_1 = Ro_1 - Ri_1;
	float sqrd1 = RoRi_1 * RoRi_1;
	float b1 = PI * sqrd1;

	float val = (0.129904f / b1);
	return val - 1;
}
float p2_LE4(unsigned ndv, const float* DV)
{
	float Ro_1 = DV[0];
	float Ri_1 = DV[1];
	float Ro_2 = DV[2];
	float Ri_2 = DV[3];
	float RoRi_1 = Ro_1 - Ri_1;
	float sqrd1 = RoRi_1 * RoRi_1;
	float RoRi_2 = Ro_2 - Ri_2;
	float sqrd2 = RoRi_2 * RoRi_2;
	float b1 = PI * sqrd1;
	float b2 = PI * sqrd2;

	float sqrt2 = sqrtf(2);
	float val = (.075f / (b1 + sqrt2 * b2));
	return val - 1;
}
void p2()
{
	FitnessFunc* FitFunc = create_FitFunc(4, 0, 4, 0, MIN, p2_Obj, GA_FALSE);
	add_le(FitFunc, p2_LE1);
	add_le(FitFunc, p2_LE2);
	add_le(FitFunc, p2_LE3);
	add_le(FitFunc, p2_LE4);
	GAbool tool = check_fitfuncOK(FitFunc);

	printf("FitFunc check is: %i Press something to continue\n", tool);
	getchar();

	float UB[4] = { 2, 2, 2, 2 };
	float LB[4] = { 0, 0, 0, 0 };

	optimPop_Min(4, FitFunc, UB, LB);  //deja vu

	printf("\nPress something to continue\n");
	getchar();

	destroy_FitFunc(FitFunc);
}

float p3_Obj(unsigned ndv, const float* DV)
{
	float b1 = DV[0];
	float b2 = DV[1];
	float b3 = DV[2];
	float sqrt2 = sqrtf(2);
	float val = b1 * sqrt2 + b2 + b3 * sqrt2;
	return 10 * val;
}
float p3_LE1(unsigned ndv, const float* DV)
{
	float b1 = DV[0];
	float b2 = DV[1];
	float root2 = sqrtf(2);
	float root2over2 = root2 / 2;
	float b1part = .866025 / b1;
	float b2part = .5 / (b1 + (root2 * b2));
	float parens = b1part + b2part;
	float val = fabs(root2over2 * parens);
	return val - 1;
}
float p3_LE2(unsigned ndv, const float* DV)
{
	float b1 = DV[0];
	float b2 = DV[1];
	float root2 = sqrtf(2);
	float root2over2 = root2 / 2;
	float denom = b1 + (root2 * b2);
	float parens = 1 / denom;
	float val = fabs(root2over2 * parens);
	return val - 1;
}
float p3_LE3(unsigned ndv, const float* DV)
{
	float b1 = DV[0];
	float b2 = DV[1];
	float root2 = sqrtf(2);
	float root2over2 = root2 / 2;
	float b1part = .866025 / b1;
	float b2part = .5 / (b1 + (root2 * b2));
	float parens = b2part - b1part;
	float val = fabs(root2over2 * parens);
	return val - 1;
}
float p3_LE4(unsigned ndv, const float* DV)
{
	float b1 = DV[0];
	float b2 = DV[1];
	float Beta1 = DV[3];

	float z1part = .866025f / b1;
	float sqrt2 = sqrtf(2);
	float z2part = (.5 / (b1 + sqrt2 * b2));

	float bpart = b1 * (z1part + z2part);
	float left = -1 * sqrt2 * 10000.0f * bpart;

	float betapart = Beta1 * b1 * b1;
	float right = ((PI * PI * 2000.0f) / sqrt2) * betapart;

	return left - right;
}
float p3_LE5(unsigned ndv, const float* DV)
{
	float b1 = DV[0];
	float b2 = DV[1];
	float Beta2 = DV[4];

	float sqrt2 = sqrtf(2);
	float z2part = (.5 / (b1 + sqrt2 * b2));

	float bpart = b2 * z2part;
	float left = -1 * sqrt2 * 20000.0f * bpart;

	float betapart = Beta2 * b2 * b2;
	float right = PI * PI * sqrt2 * betapart;

	return left - right;
}
float p3_LE6(unsigned ndv, const float* DV)
{
	float b1 = DV[0];
	float b2 = DV[1];
	float b3 = DV[2];
	float Beta3 = DV[5];

	float z1part = .866025f / b1;
	float sqrt2 = sqrtf(2);
	float z2part = (.5 / (b1 + sqrt2 * b2));

	float bpart = b3 * (z2part - z1part);
	float left = -1 * sqrt2 * 10000.0f * bpart;

	float betapart = Beta3 * b3 * b3;
	float right = ((PI * PI * 2000.0f) / sqrt2) * betapart;

	return left - right;
}
float p3_LE7(unsigned ndv, const float* DV)
{
	float b1 = DV[0];
	float val = (0.129904f / b1);
	return val - 1;
}
float p3_LE8(unsigned ndv, const float* DV)
{
	float b1 = DV[0];
	float b2 = DV[1];
	float sqrt2 = sqrtf(2);
	float val = (.075f / (b1 + sqrt2 * b2));
	return val - 1;
}
void p3()
{
	FitnessFunc* FitFunc = create_FitFunc(6, 0, 8, 0, MIN, p3_Obj, GA_FALSE);
	add_le(FitFunc, p3_LE1);
	add_le(FitFunc, p3_LE2);
	add_le(FitFunc, p3_LE3);
	add_le(FitFunc, p3_LE4);
	add_le(FitFunc, p3_LE5);
	add_le(FitFunc, p3_LE6);
	add_le(FitFunc, p3_LE7);
	add_le(FitFunc, p3_LE8);
	GAbool tool = check_fitfuncOK(FitFunc);

	printf("FitFunc check is: %i Press something to continue\n", tool);
	getchar();

	float UB[6] = { 2, 2, 2, 2, 2, 2 };
	float LB[6] = { 0, 0, 0, 0, 0, 0 };

	optimPop_Min(6, FitFunc, UB, LB);  //deja vu

	printf("\nPress something to continue\n");
	getchar();

	destroy_FitFunc(FitFunc);
}

float p4_Obj(unsigned ndv, const float* DV)
{
	float X12 = DV[0];
	float X13 = DV[1];
	float X24 = DV[2];
	float X25 = DV[3];
	float X34 = DV[4];
	float X35 = DV[5];
	float X45 = DV[6];
	float min = 8 * X12 + 6 * X13 + 9 * X24 + 5 * X25 + 7 * X34 + 3 * X35 + 7 * X45;
	return min;
}
float p4_LE1(unsigned ndv, const float* DV)
{
	float X12 = DV[0];
	float X13 = DV[1];
	float X24 = DV[2];
	float X25 = DV[3];
	float X34 = DV[4];
	float X35 = DV[5];
	float X45 = DV[6];
	float val = 3 * X12 + 4 * X13 + 2 * X24 + 4 * X25 + 4 * X34 + 6 * X35 + 3 * X45;
	return val - 9;
}
float p4_EQ1(unsigned ndv, const float* DV)
{
	float X12 = DV[0];
	float X13 = DV[1];
	float val = X12 + X13;
	return val - 1;
}
float p4_EQ2(unsigned ndv, const float* DV)
{
	float X12 = DV[0];
	float X24 = DV[2];
	float X25 = DV[3];
	float val = X24 + X25 - X12;
	return val;
}
float p4_EQ3(unsigned ndv, const float* DV)
{
	float X13 = DV[1];
	float X34 = DV[4];
	float X35 = DV[5];
	float val = X34 + X35 - X13;
	return val;
}
float p4_EQ4(unsigned ndv, const float* DV)
{
	float X24 = DV[2];
	float X34 = DV[4];
	float X45 = DV[6];
	float val = X45 - X34 - X24;
	return val;	
}
float p4_EQ5(unsigned ndv, const float* DV)
{
	float X25 = DV[3];
	float X35 = DV[5];
	float X45 = DV[6];
	float val = (-1 * X45) - X35 - X25;
	return val + 1;
}
void p4()
{
	FitnessFunc* FitFunc = create_FitFunc(7, 5, 1, 0, MIN, p4_Obj, GA_TRUE);
	add_le(FitFunc, p4_LE1);
	add_eq(FitFunc, p4_EQ1);
	add_eq(FitFunc, p4_EQ2);
	add_eq(FitFunc, p4_EQ3);
	add_eq(FitFunc, p4_EQ4);
	add_eq(FitFunc, p4_EQ5);
	GAbool tool = check_fitfuncOK(FitFunc);

	printf("FitFunc check is: %i Press something to continue\n", tool);
	getchar();

	float UB[7] = { 1, 1, 1, 1, 1, 1, 1 };
	float LB[7] = { 0, 0, 0, 0, 0, 0, 0 };

	optimPop_Min(7, FitFunc, UB, LB);  //deja vu

	printf("\nPress something to continue\n");
	getchar();

	destroy_FitFunc(FitFunc);
}

float p5_Obj(unsigned ndv, const float* X)
{
	float fint_1 = 5 * X[1] - 4 * X[2] + X[3] - 2 * X[4] - X[24];
	float fint_2 = -4 * X[2] + 50 * X[2] - 2 * X[3] + 3 * X[4] - 5 * X[6];
	float fint_3 = X[3] - 2 * X[2] + 20 * X[3] - 17 * X[4] - 2 * X[8];
	float fint_4 = -2 * X[4] + 3 * X[2] - 17 * X[3] - 178 * X[4] - 8 * X[6] + X[4] * X[4] + 2;
	float fint_5 = 214 * X[5] - 26 * X[9] - X[25] + X[26] - X[30] + X[5] + 8;
	float fint_6 = -5 * X[6] - 8 * X[4] + 63 * X[6] - 19 * X[7] + 12 * X[8] + sqrtf(X[6]) + 7;
	float fint_7 = -19 * X[7] + 136 * X[7] - 14 * X[8] + 17 * X[10] - 22 * X[12];
	float fint_8 = -8 * X[8] - 2 * X[3] - 26 * X[4] + 12 * X[6] - 14 * X[7] + X[8] * X[8] * X[8] + 4;
	float fint_9 = -26 * X[9] + 240 * X[9] - 81 * X[11] - 8 * X[32] + 13 * X[37] + sinf(X[9]) + 5;
	float fint_10 = -14 * X[10] + 17 * X[7] - 82 * X[8] + 492 * X[10] - 19 * X[12];
	float fint_11 = -81 * X[1] + 501 * X[11] - 99 * X[15] - 5 * X[26] + 5 * X[27] + X[11] + 8;
	float fint_12 = -22 * X[12] + 2 * X[8] - 19 * X[10] + 120 * X[12] - 42 * X[13] + sinf(X[12]) + 5;
	float fint_13 = -42 * X[13] + 208 * X[13] - 28 * X[14] + 40 * X[16] - 47 * X[18] + X[12] * X[13] + 3;
	float fint_14 = 2 * X[14] - 19 * X[7] - 99 * X[10] + 30 * X[12] - 28 * X[13] + cosf(X[14]) + 6;
	float fint_15 = -99 * X[15] + 453 * X[15] - 176 * X[17] + 8 * X[21] - 1 * X[26];
	float fint_16 = -28 * X[16] + 40 * X[13] - 177 * X[14] + 767 * X[16] - 33 * X[18];
	float fint_17 = -176 * X[17] + 771 * X[17] - 200 * X[21] - 7 * X[27] + 7 * X[28];
	float fint_18 = X[18] - 47 * X[13] + 4 * X[14] - 33 * X[16] + 177 * X[18] + X[18] + 8;
	float fint_19 = -73 * X[19] + 278 * X[19] - 44 * X[20] + 71 * X[22] + 4 * X[28] + cosf(X[19]) + 7;
	float fint_20 = 4 * X[20] - 33 * X[13] + 9 * X[14] - 200 * X[16] + 55 * X[18] + X[20] * X[20] + 2;
	float fint_21 = 8 * X[21] - 200 * X[17] + 676 * X[21] - 301 * X[23] - 2 * X[27] + X[21] + 8;
	float fint_22 = -44 * X[22] + 71 * X[19] - 302 * X[20] + 1041 * X[22] - 3 * X[28] + X[22] + 8;
	float fint_23 = - 301 * X[23] + 1044 * X[23] - 10 * X[28] + 10 * X[29] - 44 * X[55] + X[23] * X[23] * X[23] + 4;
	float fint_24 = -1 * X[24] + X[2] + X[3] - 2 * X[4] + 10 * X[24] + cosf(X[24]) + 6;
	float fint_25 = X[25] - 1 * X[5] + sinf(X[25]) + 5;
	float fint_26 = X[26] - 1 * X[4] + X[5] + 2 * X[6] + 3 * X[7] + X[25] * X[26] + 3;
	float fint_27 = 3 * X[27] - 2 * X[10] + 5 * X[11] + 4 * X[12] + 4 * X[13];
	float fint_28 = 4 * X[28] + X[15] - 3 * X[16] + 7 * X[17] + 4 * X[18] + cosf(X[28]) + 6;
	float fint_29 = 4 * X[29] + 2 * X[21] - 3 * X[22] + 10 * X[23];
	float fint_30 = -1 * X[30] - 1 * X[32] - 1 * X[35] + X[30] + 8;
	float fint_31 = X[31] - 7 * X[2] - 2 * X[3] + 3 * X[4] + 2 * X[6] + X[31] * X[31] + 4;
	float fint_32 = 7 * X[32] - 8 * X[9] - 1 * X[30] + 118 * X[32] + 7 * X[35] + cosf(X[32]) + 6;
	float fint_33 = X[33] - 2 * X[31] + 20 * X[33] - 17 * X[34] - 2 * X[41];
	float fint_34 = -2 * X[34] + 3 * X[31] - 17 * X[33] + 178 * X[34] - 8 * X[36] + X[34] + 8;
	float fint_35 = -1 * X[35] + 7 * X[32] + 214 * X[35] - 8 * X[37] + X[38] + X[34] * X[35] + 3;
	float fint_36 = 2 * X[36] - 8 * X[4] - 11 * X[6] + 5 * X[7] + 12 * X[8];
	float fint_37 = -8 * X[37] + 14 * X[9] - 14 * X[11] + 2 * X[15] - 10 * X[32] + cosf(X[37]) + 6;
	float fint_38 = X[38] + X[5] + 2 * X[8] + 2 * X[10] - 5 * X[11];
	float fint_39 = 5 * X[39] - 21 * X[7] - 14 * X[8] + 17 * X[10] + 7 * X[12] + cosf(X[39]) + 7;
	float fint_40 = -14 * X[40] + 18 * X[11] - 19 * X[15] - 38 * X[37] - 5 * X[38];
	float fint_41 = -8 * X[41] - 2 * X[33] - 26 * X[34] + 12 * X[36] - 2 * X[38] + sinf(X[41]) + 5;
	float fint_42 = -8 * X[42] - 26 * X[35] + 13 * X[37] - 14 * X[40] + 240 * X[42] + sinf(X[42]) + 5;
	float fint_43 = -14 * X[43] - 2 * X[38] + 17 * X[39] - 82 * X[41] + 492 * X[43];
	float fint_44 = -14 * X[44] - 5 * X[38] + 18 * X[40] - 81 * X[42] + 501 * X[44] + sinf(X[44]) + 5;
	float fint_45 = 7 * X[45] + 2 * X[8] - 19 * X[10] - 23 * X[12] + 12 * X[13] + cosf(X[45]) + 6;
	float fint_46 = 2 * X[46] - 19 * X[11] + 30 * X[15] - 27 * X[17] + 4 * X[21] + cosf(X[46]) + 6;
	float fint_47 = 2 * X[47] + 5 * X[11] + 3 * X[14] + 3 * X[16] - 7 * X[17] + X[47] * X[47] * X[47] + 4;
	float fint_48 = 12 * X[48] - 36 * X[13] - 28 * X[14] + 40 * X[16] + 14 * X[18];
	float fint_49 = -27 * X[49] + 40 * X[17] - 33 * X[21] - 84 * X[46] - 7 * X[47] + X[49] + 8;
	float fint_50 = 2 * X[50] - 19 * X[39] - 99 * X[43] + 30 * X[45] - 3 * X[47] + cosf(X[50]) + 6;
	float fint_51 = 2 * X[51] - 1 * X[38] - 19 * X[40] - 99 * X[44] + 30 * X[46];
	float fint_52 = -28 * X[52] - 3 * X[47] + 40 * X[48] - 177 * X[50] + 767 * X[52];
	float fint_53 = -27 * X[53] - 7 * X[47] + 40 * X[49] - 176 * X[51] + 771 * X[53] + cosf(X[53]) + 6;
	float fint_54 = -1 * X[54] + 14 * X[13] + 4 * X[14] - 33 * X[16] - 36 * X[18];
	float fint_55 = 4 * X[55] - 33 * X[17] + 55 * X[21] - 44 * X[23] + 2 * X[46] + X[55] * X[55] + 2;
	float fint_56 = X[56] + 3 * X[16] + 7 * X[17] + 3 * X[20] + 3 * X[22] + X[56] + 8;
	float fint_57 = 20 * X[57] - 53 * X[19] - 44 * X[20] + 71 + X[22] - 147 * X[54] + X[57] * X[57] * X[57] + 4;
	float fint_58 = -44 * X[58] + 71 * X[23] - 146 * X[55] - 10 * X[56] + 557 * X[58];
	float fint_59 = 2 * X[59] + 3 * X[22] + 10 * X[23] + 2 * X[55] + 10 * X[58] + X[58] * X[59] + 3;
	float fint_60 = 4 * X[60] - 33 * X[48] + 9 * X[50] - 200 * X[52] + 55 * X[54] + X[59] * X[60] + 3;
	float fint_61 = 4 * X[61] - 2 * X[47] - 33 * X[49] + 8 * X[51] - 200 * X[53] + X[61] + 8;
	float fint_62 = - 44 * X[62] - 3 * X[56] + 71 * X[57] - 3 * X[59] - 302 * X[60] + X[62] * X[62] + 2;
	float fint_63 = -44 * X[63] - 10 * X[56] + 71 * X[58] + 10 * X[59] - 301 * X[61] + X[63] * X[63] * X[63] + 4;
	float fint_64 = -1 * X[64] + 1 * X[31] + X[33] - 2 * X[34] + 10 * X[64] + sinf(X[64]) + 5;
	float fint_65 = -1 * X[65] - 1 * X[67] - 1 * X[70] + cosf(X[65]) + 6;
	float fint_66 = X[66] - 7 * X[31] - 2 * X[33] + 3 * X[34] + 2 * X[36] + X[66] + 8;
	float fint_67 = -9 * X[67] + 7 * X[35] + 2 * X[37] - 8 * X[42] - 1 * X[65];
	float fint_68 = X[68] - 2 * X[66] + 20 * X[68] - 17 * X[69] - 2 * X[76] + X[68] * X[68] * X[68] + 4;
	float fint_69 = -2 * X[69] + 3 * X[66] - 17 * X[68] + 178 * X[69] - 8 * X[71];
	float fint_70 = -1 * X[70] + 7 * X[67] + 214 * X[70] - 8 * X[72] + X[73] + X[70] * X[70] * X[70] + 4;
	float fint_71 = 2 * X[71] - 8 * X[34] - 11 * X[36] + 5 * X[39] + 12 * X[41] + X[71] * X[71] * X[71] + 4;
	float fint_72 = 2 * X[72] - 8 * X[35] - 11 * X[37] + 5 * X[40] + 13 * X[42] + X[72] * X[72] + 2;
	float fint_73 = X[73] + X[35] + 2 * X[41] + 2 * X[43] - 5 * X[44];
	float fint_74 = 5 * X[74] - 21 * X[39] - 14 * X[41] + 17 * X[43] + 7 * X[45] + sinf(X[74]) + 5;
	float fint_75 = 5 * X[75] - 22 * X[40] - 14 * X[42] + 18 * X[44] + 7 * X[46] + sinf(X[75]) + 5;
	float fint_76 = -8 * X[76] - 2 * X[68] - 26 * X[69] + 12 * X[71] - 2 * X[73] + X[75] * X[76] + 3;
	float fint_77 = -8 * X[77] - 26 * X[70] + 13 * X[72] - 14 * X[75] + 240 * X[77];
	float fint_78 = -14 * X[78] - 2 * X[73] + 17 * X[74] - 82 * X[76] + 492 * X[78] + X[78] + 8;
	float fint_79 = -14 * X[79] - 5 * X[73] + 18 * X[75] - 81 * X[77] + 501 * X[79] + sqrtf(X[79]) + 7;
	float fint_80 = 7 * X[80] + 2 * X[41] - 19 * X[43] - 23 * X[45] + 12 * X[48] + X[80] + 8;
	float fint_81 = 7 * X[81] + 2 * X[42] - 19 * X[44] - 23 * X[46] + 12 * X[49];
	float fint_82 = 2 * X[82] + 5 * X[44] + 3 * X[50] + 3 * X[52] - 7 * X[53] + X[82] * X[82] * X[82] + 4;
	float fint_83 = 12 * X[83] - 36 * X[48] - 28 * X[50] + 40 * X[52] + 14 * X[54] + X[83] * X[83] * X[83] + 4;
	float fint_84 = 12 * X[84] - 37 * X[49] - 27 * X[51] + 40 * X[53] + 14 * X[55] + X[84] + 8;
	float fint_85 = 2 * X[85] - 19 * X[74] - 99 * X[78] + 30 * X[80] - 3 * X[82] + X[85] * X[85] + 2;
	float fint_86 = 2 * X[86] - 1 * X[73] - 19 * X[75] - 99 * X[79] + 30 * X[81] + X[86] * X[86] * X[86] + 4;
	float fint_87 = -28 * X[87] - 3 * X[82] + 40 * X[83] - 177 * X[85] + 767 * X[87] + X[87] * X[87] * X[87] + 4;
	float fint_88 = -27 * X[88] - 7 * X[82] + 40 * X[84] - 176 * X[86] + 771 * X[88];
	float fint_89 = -1 * X[89] + 14 * X[48] + 4 * X[50] - 33 * X[52] - 36 * X[54];
	float fint_90 = -1 * X[90] + 14 * X[49] + 4 * X[51] - 33 * X[53] - 36 * X[55] + cosf(X[90]) + 6;
	float fint_91 =  X[91] + 3 * X[52] + 7 * X[53] + 3 * X[60] + 3 * X[62];
	float fint_92 = 20 * X[92] - 53 * X[57] - 44 * X[60] + 71 * X[62] - 147 * X[89] + X[91] * X[92] + 3;
	float fint_93 = 20 * X[93] - 53 * X[58] - 44 * X[61] + 71 * X[63] - 146 * X[90] + X[93] * X[93] * X[93] + 4;
	float fint_94 = 2 * X[94] + 3 * X[62] + 10 * X[63] + 2 * X[90] + 10 * X[93];
	float fint_95 = 4 * X[95] - 33 * X[83] + 9 * X[85] - 200 * X[87] + 55 * X[89] + cosf(X[95]) + 6;
	float fint_96 = 4 * X[96] - 2 * X[82] - 33 * X[84] + 8 * X[86] - 200 * X[88];
	float fint_97 = -44 * X[97] - 3 * X[91] + 71 * X[92] - 3 * X[94] - 302 * X[95] + X[96] * X[97] + 3;
	float fint_98 = -44 * X[98] - 10 * X[91] + 71 * X[93] + 10 * X[94] - 301 * X[96] + X[97] * X[98] + 3;
	float fint_99 = 20 * X[99] - 53 * X[92] - 44 * X[95] + 71 * X[97] + 556 * X[99] + X[98] * X[99] + 3;
	float fint_100 = 20 * X[100] - 53 * X[93] - 44 * X[96] + 71 * X[98] + 557 * X[100] + X[100] + 8;
	float fe_1 = 44;
	float fe_2 = -573;
	float fe_3 = 554;
	float fe_4 = -1861;
	float fe_5 = 3882;
	float fe_6 = 1012.359;
	float fe_7 = 2022;
	float fe_8 = 1110;
	float fe_9 = -965.989;
	float fe_10 = 4883;
	float fe_11 = -4003;
	float fe_12 = -2003.46;
	float fe_13 = 2661;
	float fe_14 = -2241.25;
	float fe_15 = 2549;
	float fe_16 = 1577;
	float fe_17 = 2855;
	float fe_18 = 1547;
	float fe_19 = -3041.15;
	float fe_20 = 486;
	float fe_21 = 6652;
	float fe_22 = -14279;
	float fe_23 = -6406;
	float fe_24 = 150.9074;
	float fe_25 = -4.34301;
	float fe_26 = 183;
	float fe_27 = 25;
	float fe_28 = 125.5403;
	float fe_29 = -44;
	float fe_30 = 12;
	float fe_31 = 171;
	float fe_32 = -421.654;
	float fe_33 = -58;
	float fe_34 = 2611;
	float fe_35 = -104;
	float fe_36 = 60;
	float fe_37 = -25.9956;
	float fe_38 = 103;
	float fe_39 = -335.46;
	float fe_40 = -784;
	float fe_41 = -504.009;
	float fe_42 = 4570.15;
	float fe_43 = 251;
	float fe_44 = -5980.41;
	float fe_45 = 294.5403;
	float fe_46 = 317.1367;
	float fe_47 = 7932;
	float fe_48 = -124;
	float fe_49 = -1077;
	float fe_50 = -289.04;
	float fe_51 = 1359;
	float fe_52 = 14338;
	float fe_53 = 11082.41;
	float fe_54 = -253;
	float fe_55 = 1006;
	float fe_56 = 109;
	float fe_57 = -1459;
	float fe_58 = -4870;
	float fe_59 = -92;
	float fe_60 = -4397;
	float fe_61 = -3526;
	float fe_62 = -2061;
	float fe_63 = -5562;
	float fe_64 = -54.0411;
	float fe_65 = -9;
	float fe_66 = 35;
	float fe_67 = -121;
	float fe_68 = -118;
	float fe_69 = 650;
	float fe_70 = 8499;
	float fe_71 = 1736;
	float fe_72 = 138;
	float fe_73 = 71;
	float fe_74 = -76.343;
	float fe_75 = -297.159;
	float fe_76 = -32;
	float fe_77 = 1903;
	float fe_78 = -3318;
	float fe_79 = -257;
	float fe_80 = 88;
	float fe_81 = -174;
	float fe_82 = -70;
	float fe_83 = 150;
	float fe_84 = 792;
	float fe_85 = 93;
	float fe_86 = 5912;
	float fe_87 = -3219;
	float fe_88 = 5539;
	float fe_89 = -441;
	float fe_90 = -1383.91;
	float fe_91 = 254;
	float fe_92 = 72;
	float fe_93 = 2970;
	float fe_94 = 298;
	float fe_95 = 1125.844;
	float fe_96 = -2033;
	float fe_97 = -3460;
	float fe_98 = -3831;
	float fe_99 = 56;
	float fe_100 = -682;
	float f1 = fint_1 - fe_1;
	float f2 = fint_2 - fe_2;
	float f3 = fint_3 - fe_3;
	float f4 = fint_4 - fe_4;
	float f5 = fint_5 - fe_5;
	float f6 = fint_6 - fe_6;
	float f7 = fint_7 - fe_7;
	float f8 = fint_8 - fe_8;
	float f9 = fint_9 - fe_9;
	float f10 = fint_10 - fe_10;
	float f11 = fint_11 - fe_11;
	float f12 = fint_12 - fe_12;
	float f13 = fint_13 - fe_13;
	float f14 = fint_14 - fe_14;
	float f15 = fint_15 - fe_15;
	float f16 = fint_16 - fe_16;
	float f17 = fint_17 - fe_17;
	float f18 = fint_18 - fe_18;
	float f19 = fint_19 - fe_19;
	float f20 = fint_20 - fe_20;
	float f21 = fint_21 - fe_21;
	float f22 = fint_22 - fe_22;
	float f23 = fint_23 - fe_23;
	float f24 = fint_24 - fe_24;
	float f25 = fint_25 - fe_25;
	float f26 = fint_26 - fe_26;
	float f27 = fint_27 - fe_27;
	float f28 = fint_28 - fe_28;
	float f29 = fint_29 - fe_29;
	float f30 = fint_30 - fe_30;
	float f31 = fint_31 - fe_31;
	float f32 = fint_32 - fe_32;
	float f33 = fint_33 - fe_33;
	float f34 = fint_34 - fe_34;
	float f35 = fint_35 - fe_35;
	float f36 = fint_36 - fe_36;
	float f37 = fint_37 - fe_37;
	float f38 = fint_38 - fe_38;
	float f39 = fint_39 - fe_39;
	float f40 = fint_40 - fe_40;
	float f41 = fint_41 - fe_41;
	float f42 = fint_42 - fe_42;
	float f43 = fint_43 - fe_43;
	float f44 = fint_44 - fe_44;
	float f45 = fint_45 - fe_45;
	float f46 = fint_46 - fe_46;
	float f47 = fint_47 - fe_47;
	float f48 = fint_48 - fe_48;
	float f49 = fint_49 - fe_49;
	float f50 = fint_50 - fe_50;
	float f51 = fint_51 - fe_51;
	float f52 = fint_52 - fe_52;
	float f53 = fint_53 - fe_53;
	float f54 = fint_54 - fe_54;
	float f55 = fint_55 - fe_55;
	float f56 = fint_56 - fe_56;
	float f57 = fint_57 - fe_57;
	float f58 = fint_58 - fe_58;
	float f59 = fint_59 - fe_59;
	float f60 = fint_60 - fe_60;
	float f61 = fint_61 - fe_61;
	float f62 = fint_62 - fe_62;
	float f63 = fint_63 - fe_63;
	float f64 = fint_64 - fe_64;
	float f65 = fint_65 - fe_65;
	float f66 = fint_66 - fe_66;
	float f67 = fint_67 - fe_67;
	float f68 = fint_68 - fe_68;
	float f69 = fint_69 - fe_69;
	float f70 = fint_70 - fe_70;
	float f71 = fint_71 - fe_71;
	float f72 = fint_72 - fe_72;
	float f73 = fint_73 - fe_73;
	float f74 = fint_74 - fe_74;
	float f75 = fint_75 - fe_75;
	float f76 = fint_76 - fe_76;
	float f77 = fint_77 - fe_77;
	float f78 = fint_78 - fe_78;
	float f79 = fint_79 - fe_79;
	float f80 = fint_80 - fe_80;
	float f81 = fint_81 - fe_81;
	float f82 = fint_82 - fe_82;
	float f83 = fint_83 - fe_83;
	float f84 = fint_84 - fe_84;
	float f85 = fint_85 - fe_85;
	float f86 = fint_86 - fe_86;
	float f87 = fint_87 - fe_87;
	float f88 = fint_88 - fe_88;
	float f89 = fint_89 - fe_89;
	float f90 = fint_90 - fe_90;
	float f91 = fint_91 - fe_91;
	float f92 = fint_92 - fe_92;
	float f93 = fint_93 - fe_93;
	float f94 = fint_94 - fe_94;
	float f95 = fint_95 - fe_95;
	float f96 = fint_96 - fe_96;
	float f97 = fint_97 - fe_97;
	float f98 = fint_98 - fe_98;
	float f99 = fint_99 - fe_99;
	float f100 = fint_100 - fe_100;
	float val = f1 * f1 + f2 * f2 + f3 * f3 + f4 * f4 + f5 * f5 +
		f6 * f6 + f7 * f7 + f8 * f8 + f9 * f9 + f10 * f10 +
		f11 * f11 + f12 * f12 + f13 * f13 + f14 * f14 + f15 * f15 +
		f16 * f16 + f17 * f17 + f18 * f18 + f19 * f19 + f20 * f20 +
		f21 * f21 + f22 * f22 + f23 * f23 + f24 * f24 + f25 * f25 +
		f26 * f26 + f27 * f27 + f28 * f28 + f29 * f29 + f30 * f30 +
		f31 * f31 + f32 * f32 + f33 * f33 + f34 * f34 + f35 * f35 +
		f36 * f36 + f37 * f37 + f38 * f38 + f39 * f39 + f40 * f40 +
		f41 * f41 + f42 * f42 + f43 * f43 + f44 * f44 + f45 * f45 +
		f46 * f46 + f47 * f47 + f48 * f48 + f49 * f49 + f50 * f50 +
		f51 * f51 + f52 * f52 + f53 * f53 + f54 * f54 + f55 * f55 +
		f56 * f56 + f57 * f57 + f58 * f58 + f59 * f59 + f60 * f60 +
		f61 * f61 + f62 * f62 + f63 * f63 + f64 * f64 + f65 * f65 +
		f66 * f66 + f67 * f67 + f68 * f68 + f69 * f69 + f70 * f70 +
		f71 * f71 + f72 * f72 + f73 * f73 + f74 * f74 + f75 * f75 +
		f76 * f76 + f77 * f77 + f78 * f78 + f79 * f79 + f80 * f80 +
		f81 * f81 + f82 * f82 + f83 * f83 + f84 * f84 + f85 * f85 +
		f86 * f86 + f87 * f87 + f88 * f88 + f89 * f89 + f90 * f90 +
		f91 * f91 + f92 * f92 + f93 * f93 + f94 * f94 + f95 * f95 +
		f96 * f96 + f97 * f97 + f98 * f98 + f99 * f99 + f100 * f100; 
	return val;
}
void p5()
{
	FitnessFunc* FitFunc = create_FitFunc(100, 0, 0, 0, MIN, p4_Obj, GA_FALSE);
	GAbool tool = check_fitfuncOK(FitFunc);

	printf("FitFunc check is: %i Press something to continue\n", tool);
	getchar();

	float UB[100] = { 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
		32, 32, 32, 32, 32, 32, 32, 32, 32, 32
	};
	float LB[100] = { -32, -32, -32, -32, -32, -32, -32, -32, -32, -32,
		-32, -32, -32, -32, -32, -32, -32, -32, -32, -32,
		-32, -32, -32, -32, -32, -32, -32, -32, -32, -32,
		-32, -32, -32, -32, -32, -32, -32, -32, -32, -32,
		-32, -32, -32, -32, -32, -32, -32, -32, -32, -32,
		-32, -32, -32, -32, -32, -32, -32, -32, -32, -32,
		-32, -32, -32, -32, -32, -32, -32, -32, -32, -32,
		-32, -32, -32, -32, -32, -32, -32, -32, -32, -32,
		-32, -32, -32, -32, -32, -32, -32, -32, -32, -32,
		-32, -32, -32, -32, -32, -32, -32, -32, -32, -32
	};

	optimPop_Min(100, FitFunc, UB, LB);  //deja vu

	printf("\nPress something to continue\n");
	getchar();

	destroy_FitFunc(FitFunc);
}
//make sure omp is enabled.  In VS project properties -> C/C++ -> Language -> openMP support to yes
int main()
{
	for (unsigned pop = 0; pop < GA_NUM_POPULATIONS; pop++)
	{
		//p1();
		//p2();
		//p3();
		//p4();
		p5();
	}
	printf("Press something the exit.\n");
	getchar();
	return 0;
}
#ifndef _GA_H_
#define _GA_H_

#define GA_RESOLUTION 8 //do not go over fifteen on my system because the max that rand() will return is 2^15 - 1
#define GA_PENALTY 10 //I don't know...
#define GA_POPULATION 100//seems like a good number
#define GA_NUM_POPULATIONS 4  //be cause of greedy optimization

//type of constraint function pointer
typedef float(*gaf_ptr)(unsigned ndv, const float* DV);
typedef enum {MIN, MAX} MinMAX;
typedef enum {GA_TRUE, GA_FALSE} GAbool;

typedef struct FitnessFunc
{
	unsigned ndv;
	unsigned neq;
	unsigned current_neq; //these is going to be used to check if we have room to add function AND to check if all requested were added.
	gaf_ptr* EQ;
	unsigned nle;
	unsigned current_nle;
	gaf_ptr* LE;
	unsigned nge;
	unsigned current_nge;
	gaf_ptr* GE;
	MinMAX ObjType;
	gaf_ptr ObjF;
}FitnessFunc;

FitnessFunc* create_FitFunc(unsigned ndv, unsigned neq, unsigned nle, unsigned  nge, MinMAX ObjType, const gaf_ptr ObjF, GAbool Binary);
void destroy_FitFunc(FitnessFunc* FitFunc);
void add_eq(FitnessFunc* FitFunc, const gaf_ptr eq_f);
void add_le(FitnessFunc* FitFunc, const gaf_ptr eq_f);
void add_ge(FitnessFunc* FitFunc, const gaf_ptr eq_f);
GAbool check_fitfuncOK(FitnessFunc* FitFunc);

float eval_Fitfunc(const FitnessFunc* FitFunc, unsigned ndv, const float* DV);

void optimPop_Min(unsigned ndv, const FitnessFunc* FitFunc, const float* UB, const float* LB);


#endif // !_GA_H_


#include "FunctionPrototypes.h"

#ifndef GLOBAL_VARIABLES
#define GLOBAL_VARIABLES


#define epsilon 0.001
#define false 0
#define true 1

int debug = 0;
int debugBruteForce = 0;
int imprimeResultado = 0;
// variaveis para controle de memória.
int mallocNumber = 0;
int freeNumber = 0;
FILE *outFile;

void initMallocCounter(){
	mallocNumber = 0;
	freeNumber = 0;
}

/*global variables to use in the program - this was made to remove the time of malloc and free from the program*/
int bMax = 12000;    // capacidade máxima da mochila.
int nMax = 12200;
int kMax = 13000;

double **globalMatrix;

kList globalKList = NULL;
kList* globalKListVectorPointers = NULL;  // the vector used in the sortFunctions
kList* auxGlobalKListVectorPointers = NULL;


matrixElementList globalMatrixElementList = NULL;
matrixElementList* globalMatrixElementListVectorPointers = NULL;
matrixElementList* auxGlobalMatrixElementListVectorPointers = NULL;

int* globalA;
double* globalC;

#endif
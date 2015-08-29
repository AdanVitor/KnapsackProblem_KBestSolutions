

#ifndef FUNCTION_PROTOTYPES
#define FUNCTION_PROTOTYPES

#include "DefinitionsAndStructures.h"


/*functions prototypes */
void printKList(kList list, int n);
node createEmptyNode();
node createNode(int n, int i, int j, double V, int * initialJ); // n: numero de elementos
void removeLeaderNode(kList* L);
void insertElement(kList* L, node Node);
void printMatrix(double **matrix, int rowNumber, int columnNumber);
kList build_initial_best_k_list(double** M, int b, int n, int* a, kList L, int* P, int k, double *c);
kList sortList(kList L, int listSize, kList* finalListPointer);
void printVectorList(kList* vector, int size);
void mergeSort(kList*L, int vectorSize);
void merge(kList* L, int li, int mid, int hi);
void sort(kList* L, int li, int hi);
kList joinLists(kList L, kList L1, int objectsNumber, kList* finalListPointer);
kList findHiddenSolutions(double** M, int b, int n, int* a, kList L, kList finalListPointer, int* P, int k, double *c, int listLength);
void printMatrixElementsList(matrixElementList list);
void addMatrixElementList(matrixElementList* list, matrixElementNode newNode);
void addNextNode(kList *finalResult, kList* listPointer);
void merge(matrixElementList* L, int li, int mid, int hi);
matrixElementList sortLineMatrixList(matrixElementList L, int listSize, matrixElementList *finalListPointer);
void addOrderedInList(matrixElementList hiddenSolution, kList L, kList* finalListPointer, int n, kList descendantPointer, int listContainKSolutions);
void compareSolutions(objectiveValueList forceBruteSolutions, kList solutionsList);
objectiveValueList bruteForceKBestSolutions(int b, int n, int* a, double *c, int k);
void freekList(kList* L);
void printDifBetweenMallocAndFree(char*);
void initMallocCounter();
void freeMatrixSpace(double**, int, int);
double** initialMatrix(int, int);
void forwardEnumeration(double**, int*, double*, int, int);
void printKList(kList, int);
matrixElementNode createMatrixNode(double, int, int, int*);
void printMatrixElementsList(matrixElementList);
void printResultVector(double, int, char);
void initMallocCounter();
double** getAllocatedMatrix();
node createEmptyNode();
void allocateGlobalVariables();
void freeKListNode(kList*);
node createNode();
matrixElementNode createEmptyMatrixNode();
matrixElementNode getMatrixElement();
void freeMatrixNode(matrixElementNode* );
void desalocateGlobalVariables();


/*--------------------*/

#endif 
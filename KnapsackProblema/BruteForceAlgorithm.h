#ifndef BRUTE_FORCE_ALGORITHM
#define BRUTE_FORCE_ALGORITHM

#include "stdlib.h"
#include "DefinitionsAndStructures.h"
#include "GlobalVariables.h"
#include "PrintFunctions.h"
#include "stdafx.h"
#include "windows.h"
#include "Math.h"

//**********************************************************************
/*Functions to make a easy way of getting the k best solutions*/


objectiveValueNode createNewValueElement(double value){
	objectiveValueNode elem = (objectiveValueNode)malloc(sizeof(valueElement));
	mallocNumber++;
	elem->objectiveValue = value;
	elem->previous = NULL;
	elem->prox = NULL;
	return elem;
}

void insertValueElementOrdered(objectiveValueList* list, objectiveValueList* finalValuePointer, double objectiveValue, int k, int* listSize){
	objectiveValueNode newNode = createNewValueElement(objectiveValue);
	if ((*listSize) == 0){
		(*list) = newNode;
		(*finalValuePointer) = (*list);
		(*listSize)++;
		return;
	}
	// casos críticos - inserir no inicio ou no fim da lista
	objectiveValueList listPointer = (*list);
	while (listPointer != NULL && listPointer->objectiveValue >= objectiveValue){
		listPointer = listPointer->prox;
	}
	bool removeSolution = ((*listSize) == k);
	if (removeSolution){
		if (listPointer == NULL){
			return;
		}
		if (listPointer == (*finalValuePointer)){// adding in the final of the list- in the place of the finalValuePointer
			newNode->previous = (*finalValuePointer)->previous;
			if (newNode->previous != NULL){
				newNode->previous->prox = newNode;
			}
			newNode->prox = NULL;
			(*finalValuePointer) = newNode;
			return;
		}
	}
	else{
		(*listSize)++;
		if (listPointer == NULL){ // in this case I insert in the final of the queue
			(*finalValuePointer)->prox = newNode;
			newNode->previous = (*finalValuePointer);
			(*finalValuePointer) = newNode;
			return;
		}
	}
	// now the commom cases of adding in the list;
	objectiveValueList placeAdd = listPointer->previous;
	if (placeAdd == NULL){ // adding in the start of the list;
		newNode->previous = NULL;
		newNode->prox = listPointer;
		listPointer->previous = newNode;
		(*list) = newNode;

	}
	else{
		newNode->prox = listPointer;
		newNode->previous = placeAdd;
		listPointer->previous = newNode;
		placeAdd->prox = newNode;

	}

	if (removeSolution){
		(*finalValuePointer) = (*finalValuePointer)->previous;
		(*finalValuePointer)->prox = NULL;
	}

}


int **newMatrix(int rowsNumber, int columnsNumber){
	int** matrix = (int **)malloc(rowsNumber*sizeof(int*));
	for (int i = 0; i < rowsNumber; i++){
		matrix[i] = (int *)malloc(columnsNumber*sizeof(int));
	}
	return matrix;
}

unsigned long totalPossibleSolutions(int *xMax, int size){
	unsigned long total = 1;
	for (int i = 1; i < size; i++){
		total = total*xMax[i];
	}
	return total;
}

// init a vector with the size 
int* intVectorWithZeros(int size){
	int* vector = (int*)malloc((size + 1)*sizeof(int));
	for (int i = 0; i < size; i++){
		vector[i] = 0;
	}
	return vector;
}

// the vector xMax[i] will store the maximum number of a[i] that fit in the weight b
// remembering that the index start from 1
// o x[i] goes from 0 to Xmax[i] - 1
int* getXMax(int size, int b, int* a){
	int *xMax = intVectorWithZeros(size);
	for (int i = 1; i < size; i++){
		while (xMax[i] * a[i] <= b){
			xMax[i]++;
		}
	}
	return xMax;
}
// return the step of the repet of each value of x[i]
int *getStepVector(int *xMax, int size){
	int *stepVector = intVectorWithZeros(size);
	for (int i = 0; i < size - 1; i++){
		stepVector[i] = xMax[i + 1];
	}
	stepVector[size - 1] = 1;

	for (int i = size - 2; i >= 0; i--){
		stepVector[i] = stepVector[i] * stepVector[i + 1];
	}
	return stepVector;
}


// this function returns the kBestSolutions using a method with brute force
objectiveValueList bruteForceKBestSolutions(int b, int n, int* a, double *c, int k){
	// the vector xMax[i] will store the maximum number of a[i] that fit in the weight b
	// remembering that the index start from 1
	int size = n + 1;
	int* xMax = getXMax(size, b, a);

	printf("\nVector xMax\n");
	printVector(xMax, size);

	int* stepVector = getStepVector(xMax, size);
	int* weights = intVectorWithZeros(size);
	unsigned long solutionsTotalNumber = totalPossibleSolutions(xMax, size);
	//int **solutionMatrix = newMatrix(solutionsTotalNumber, size);// the column 0 is unused in this matrix.

	objectiveValueList list = NULL;
	objectiveValueList finalListPointer = NULL;
	int listSize = 0;
	for (unsigned long i = 0; i < solutionsTotalNumber; i++){
		int step = solutionsTotalNumber;
		int myI = 0;
		for (int j = 1; j < size; j++){
			myI = i%step;
			step = step / xMax[j];
			//solutionMatrix[i][j] = myI / step;
			weights[j] = (myI / step);
		}
		double objectiveValue = 0;
		for (int j = 1; j < size; j++){
			objectiveValue += weights[j] * c[j];
		}
		int weightSum = 0;
		for (int j = 1; j < size; j++){
			weightSum += weights[j] * a[j];
		}
		if (weightSum <= b && weightSum > 0){
			insertValueElementOrdered(&list, &finalListPointer, objectiveValue, k, &listSize);
		}

	}

	//printf("\nSoluction matrix\n");
	//printSolutionMatrix(solutionMatrix, solutionsTotalNumber, size);
	if (debugBruteForce){
		printf("\nSolucoes encontradas\n");
		printBrueteForceKBest(list, k);
	}
	return list;
}

//**********************************************************************



void compareSolutions(objectiveValueList forceBruteSolutions, kList solutionsList){
	while (solutionsList != NULL){
		if (abs(solutionsList->V - forceBruteSolutions->objectiveValue) > epsilon){
			printf("*****ERRO******");
			break;
		}
		solutionsList = solutionsList->next;
		forceBruteSolutions = forceBruteSolutions->prox;
	}
}

#endif


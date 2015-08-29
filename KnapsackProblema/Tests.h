
#include "DefinitionsAndStructures.h"
#include "stdafx.h"
#include "GlobalVariables.h"
#include "FunctionPrototypes.h"

int maxA = 5000;
int printFirstSolutions = 0;
int numberOfRepetitions = 120;


void orderIntVector(int* vector, int size){
	// a simple bubble sort
	int finalPosition = size - 1;
	for (int finalPosition = size - 1; finalPosition >= 1; finalPosition--){
		for (int i = 0; i < finalPosition; i++){
			if (vector[i] > vector[i + 1]){
				int temp = vector[i];
				vector[i] = vector[i + 1];
				vector[i + 1] = temp;
			}
		}
	}
	// checking if the vector is ordered
	for (int i = 0; i < size - 1; i++){
		if (vector[i] > vector[i + 1]){
			printf("ORDENAÇÃO INCORRETA DO VETOR!!!!!!!");
		}
	}

}

int* getRandomA(int size, int maxA){
	int* a = globalA;
	mallocNumber += size;
	// remember that I don't use the index 0 of the vector
	//srand(time(NULL));
	for (int i = 1; i < size; i++){
		a[i] = rand() % maxA + 1;
		//a[i] = i;
	}
	// now I have to order the vector
	orderIntVector(a + 1, size - 1);
	// fazer um assert aqui que o vetor ta ordenado
	return a;

}


void orderDoubleVector(double* vector, int size){
	// a simple bubble sort
	int finalPosition = size - 1;
	for (int finalPosition = size - 1; finalPosition >= 1; finalPosition--){
		for (int i = 0; i < finalPosition; i++){
			if (vector[i] > vector[i + 1]){
				double temp = vector[i];
				vector[i] = vector[i + 1];
				vector[i + 1] = temp;
			}
		}
	}
	// checking if the vector is ordered
	for (int i = 0; i < size - 1; i++){
		if (vector[i] > vector[i + 1]){
			printf("ORDENAÇÃO INCORRETA DO VETOR!!!!!!!");
		}
	}
}


double* getRandomC(int size, int maxC){
	double* c = globalC;
	mallocNumber += size;
	// remember that I don't use the index 0 of the vector
	//srand(time(NULL));
	for (int i = 1; i < size; i++){
		//c[i] = rand() % maxC + 1;
		c[i] = rand() % (maxC) + maxC - maxC/2;
		//c[i] = i;
	}
	// now I have to order the vector
	//orderDoubleVector(c + 1, size - 1);
	// fazer um assert aqui que o vetor ta ordenado
	return c;

}

double* allocateTimeVector(int size){
	double* vector = (double*)malloc(size*sizeof(double));
	for (int i = 0; i < size; i++){
		vector[i] = 0;
	}
	return vector;
}

double getTimeInSeconds(long time1, long time2){
	return 1.0*(time2 - time1) / 1000;
}

void updateTimeVectors(double* totalTime, double* forwardTime, double* backwardTime, long t0, long t1, long t2, int position){
	totalTime[position] += getTimeInSeconds(t0, t2);
	forwardTime[position] += getTimeInSeconds(t0, t1);
	backwardTime[position] += getTimeInSeconds(t1, t2);
}

void getTimeVectorsMean(double* totalTime, double* forwardTime, double* backwardTime, int numberOfRepetitions, int position){
	totalTime[position] = totalTime[position] / numberOfRepetitions;
	forwardTime[position] = forwardTime[position] / numberOfRepetitions;
	backwardTime[position] = backwardTime[position] / numberOfRepetitions;
}




void testCase1(){
	outFile = fopen("outFileTeste1.m", "w");
	bMax = 69000;
	nMax = bMax/20;
	kMax = bMax/3;

	maxA = bMax / 2;

	allocateGlobalVariables();

	int n = nMax;
	int* a = getRandomA(n + 1, maxA);
	int kVectorSize = 20;
	kList L = NULL;
	int* kVector = (int*)malloc(kVectorSize*sizeof(int));
	for (int j = 0; j < kVectorSize; j++){
		kVector[j] = (kMax/kVectorSize) * (j +1);
	}
	double* totalTime = allocateTimeVector(kVectorSize);
	double* forwardTime = allocateTimeVector(kVectorSize);
	double* backwardTime = allocateTimeVector(kVectorSize);
	long time0, time1, time2;

	int b = bMax;

	double* c = getRandomC(n + 1, b / 3);

	int k;
	fprintf(outFile, "\n %%{ ****** Efect of varying K *************** %%}");
	for (int i = 0; i < kVectorSize; i++){
		for (int j = 0; j < numberOfRepetitions; j++){
			k = kVector[i];

			time0 = GetTickCount();

			double **M = initialMatrix(b, n);
			forwardEnumeration(M, a, c, b, n);
			L = NULL;
			if (imprimeResultado){
				printMatrix(M, b + 1, n + 1);
			}
			time1 = GetTickCount();

			L = build_initial_best_k_list(M, b, n, a, L, NULL, k, c);

			time2 = GetTickCount();

			/*
			objectiveValueList forceBrute = bruteForceKBestSolutions(b, n, a, c, k);
			compareSolutions(forceBrute, L);
			*/
			updateTimeVectors(totalTime, forwardTime, backwardTime, time0, time1, time2, i);

			if (j == numberOfRepetitions - 1){
				getTimeVectorsMean(totalTime, forwardTime, backwardTime, numberOfRepetitions, i);
			}

			//freeMatrixSpace(M, b + 1, n + 1);
			if (i != kVectorSize - 1 || j != numberOfRepetitions - 1){
				freekList(&L);
			}
		}
		printf("\n mallocNumber - freeNumber: %d \n", mallocNumber - freeNumber);
		initMallocCounter();
	}
	fprintf(outFile, "\n %% Execucao  para n = %d , b = %d", n, b);
	printResults(forwardTime, backwardTime, totalTime, kVector, kVectorSize , "kValues" , 1 , "k");
	freekList(&L);

	desalocateGlobalVariables();
	fclose(outFile);
}

void testCase2(){
	outFile = fopen("outFileTeste2.m", "w");

	kMax = 5900;
	nMax = kMax;
	bMax = 10*nMax;
	maxA = bMax/2;

	allocateGlobalVariables();

	fprintf(outFile, "\n %%{ ****** Efect of varying n *************** %%}");
	int k = kMax, b = bMax;
	int size = 20;
	kList L = NULL;
	int* nVector = (int*)malloc(size * sizeof(int));
	for (int j = 0; j < size; j++){
		nVector[j] = (j+1) * kMax/size;
	}
	double* totalTime = allocateTimeVector(size);
	double* forwardTime = allocateTimeVector(size);
	double* backwardTime = allocateTimeVector(size);
	long time0, time1, time2;

	bool debugForward = false;
	bool debugBackPropagation = false;

	for (int i = 0; i < size; i++){
		for (int j = 0; j < numberOfRepetitions; j++){

			int n = nVector[i];
			int* a = getRandomA(n + 1, maxA);
			double* c = getRandomC(n + 1, b / 3);

			time0 = GetTickCount();

			double **M = initialMatrix(b, n);
			forwardEnumeration(M, a, c, b, n);
			L = NULL;
			if (imprimeResultado){
				printMatrix(M, b + 1, n + 1);
			}

			time1 = GetTickCount();

			if (!debugForward){
				L = build_initial_best_k_list(M, b, n, a, L, NULL, k, c);
			}

			time2 = GetTickCount();

			/*
			objectiveValueList forceBruteSolutions = bruteForceKBestSolutions(b, n, a, c, k);
			compareSolutions(forceBruteSolutions, L);
			*/

			updateTimeVectors(totalTime, forwardTime, backwardTime, time0, time1, time2, i);

			if (j == numberOfRepetitions - 1){
				getTimeVectorsMean(totalTime, forwardTime, backwardTime, numberOfRepetitions, i);
			}
			//freeMatrixSpace(M, b + 1, n + 1);
			freeNumber += n + 1;
			freeNumber += n + 1;
			if (i != size - 1 || j != numberOfRepetitions - 1){
				freekList(&L);
			}

		}
		printf("\n mallocNumber - freeNumber: %d \n", mallocNumber - freeNumber);
		initMallocCounter();
	}

	fprintf(outFile, "\n %% Execucao  para k = %d , b = %d", k, b);
	if (printFirstSolutions){
		printFirstElements(L, 10);
	}
	freekList(&L);
	printResults(forwardTime, backwardTime, totalTime, nVector, size , "nValues" , 2 , "n");
	desalocateGlobalVariables();
	
	fclose(outFile);
}
void testCase3(){
	outFile = fopen("outFileTeste3.m", "w");
	fprintf(outFile, "\n %%{ ****** Efect of varying b *************** %%}");

	bMax = 100000;
	kMax = bMax/16;
	nMax = kMax / 2;
	maxA = bMax / 2;

	allocateGlobalVariables();



	int k = kMax, n = nMax;
	int bVectorSize = 20;
	kList L = NULL;
	int* bVector = (int*)malloc(bVectorSize*sizeof(int));
	for (int j = 0; j < bVectorSize; j++){
		bVector[j] = (bMax/bVectorSize) * (j +1);
	}
	double* variyingNTemp = (double*)malloc(bVectorSize * sizeof(double));

	double* totalTime = allocateTimeVector(bVectorSize);
	double* forwardTime = allocateTimeVector(bVectorSize);
	double* backwardTime = allocateTimeVector(bVectorSize);
	long time0, time1, time2;

	int* a = getRandomA(n + 1, maxA);


	double* c = NULL;
	for (int i = 0; i < bVectorSize; i++){
		for (int j = 0; j < numberOfRepetitions; j++){
			int b = bVector[i];
			c = getRandomC(n + 1, b / 3);

			time0 = GetTickCount();

			double **M = initialMatrix(b, n);
			forwardEnumeration(M, a, c, b, n);
			L = NULL;
			if (imprimeResultado){
				printMatrix(M, b + 1, n + 1);
			}

			time1 = GetTickCount();

			L = build_initial_best_k_list(M, b, n, a, L, NULL, k, c);

			time2 = GetTickCount();

			/*
			objectiveValueList forceBruteSolutions = bruteForceKBestSolutions(b, n, a, c, k);
			compareSolutions(forceBruteSolutions, L);
			*/
			updateTimeVectors(totalTime, forwardTime, backwardTime, time0, time1, time2, i);

			if (j == numberOfRepetitions - 1){
				getTimeVectorsMean(totalTime, forwardTime, backwardTime, numberOfRepetitions, i);
			}

			//freeMatrixSpace(M, b + 1, n + 1);
			freeNumber += n + 1;
			if (i != bVectorSize - 1 || j != numberOfRepetitions - 1){
				freekList(&L);
			}
		}
		printf("\n mallocNumber - freeNumber: %d \n", mallocNumber - freeNumber);
		initMallocCounter();

	}
	
	printResults(forwardTime, backwardTime, totalTime, bVector, bVectorSize , "bValues" , 3 , "b" );
	freekList(&L);
	fprintf(outFile, "\n\n %% Execucao  para k = %d , n = %d", k, n);

	desalocateGlobalVariables();
	fclose(outFile);
	


}

void simpleTestCase(){

	bMax = 15;
	kMax = 200;
	nMax = 10;
	maxA = 40;

	allocateGlobalVariables();
	/*Later to recover this part of a file*/
	int b = 15;
	int n = 5;
	/*vector a : weights of the elements, in ascending order , a:positive integers.*/
	/*vector c: gains of the elements, c: non-negative real numbers.*/
	/*This values a[0] and c[0] are not used - there are just to start of the index 1*/

	// testing some a vectors

	int a[6] = { 0, 3, 4, 5, 6, 7 };
	/*if (debug){
	int a[6] = { 0, 2, 2, 2, 2, 2 };
	}
	int a[6] = { 0, 2, 2, 2, 2, 2 };

	//

	*/
	/*------------------------------------*/
	double c[6] = { 0, 4, 3, 5, 7, 8 };
	int k = 100;
	double **M = initialMatrix(b, n);
	forwardEnumeration(M, a, c, b, n);
	kList L = NULL;
	printMatrix(M, b + 1, n + 1);
	L = build_initial_best_k_list(M, b, n, a, L, NULL, k, c);
	//printFirstElements(L, k);
	objectiveValueList forceBruteSolutions = bruteForceKBestSolutions(b, n, a, c, k);
	compareSolutions(forceBruteSolutions, L);

	getchar();


}
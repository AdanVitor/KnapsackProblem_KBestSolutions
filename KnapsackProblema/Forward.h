
#include "stdlib.h"
#include "GlobalVariables.h"
#include <omp.h>

void serialforwardEnumeration(double ** matrix, int *a, double *c, int b, int n);



// ##### Essa função vai ser bem tranquila de paralelizar - so ver se realmente compensa usar GPU devido a cópia de memória 
//(### talvez essa copia de memoria seja feita em paralelo - pesquisar melhor isso
//, etc...
// Um caso bem tranquilo aqui vai ser usar OPENMP - já aumentaria a velocidade em duas vezes no caso do meu processador.

double** initialMatrix(int b, int n){
	double **matrix;
	/* I will declare a (b+1) *(n+1) matrix, with
	the line 0 representing the terms a1,a2,a3, ....
	and the column 0 representing the supernodes (0,1,2,...,b)
	*/
	matrix = globalMatrix;

	/*the first line will be 0 , 1, 2, ... , n corresponding a SN 0 , and a1,a2,a3,a4, ....*/
	for (int j = 0; j < (n + 1); j++){
		matrix[0][j] = j;
	}
	/* The first column will be 0 ,1 ,2 , ... , b corresponding to the SN = 0 , 1 ,2 ,3 ..., b*/
	for (int i = 0; i < (b + 1); i++){
		matrix[i][0] = i;
	}

	/*Finally initializing the matrix with object values = -1*/
    #pragma omp parallel for
	for (int i = 1; i <= b; i++){
		for (int j = 1; j <= n; j++){
			matrix[i][j] = -1;
		}
	}
	return matrix;
}

struct ThreadInfo{
	int minValidColumn;
	bool isDependent;
};


/*This function mount the Knapsack table*/
void forwardEnumeration(double ** matrix, int *a, double *c, int b, int n){
	/* Initial ramification */

    #pragma omp parallel for
	for (int j = 1; j <= n; j++){
		if (a[j] <= b){ // for the case that a element of a[i] is bigger than b.
			matrix[a[j]][j] = c[j];
		}
	}

	/*Ramification of supernodes*/

	// o que seria paralelizavel seria esse for de fora

	// First step of parallel - create the vector of dependencies
	int const numThreads = omp_get_max_threads();
	ThreadInfo* threadsInfo = (ThreadInfo*)malloc(numThreads*sizeof(ThreadInfo));
	int maxColumn = n + 1;


	//printf("\nNumero de threads: %d", numThreads);

	// init the threads Info
	for (int i = 0; i < numThreads; i++){
		threadsInfo[i].isDependent = FALSE;
		threadsInfo[i].minValidColumn = maxColumn;
	}

	// the number of threads that were not executed in the previous paralell for
	int t = a[1];
	int maxLine = b - a[1] + 1;



	while (t < maxLine){
		
		// to the new threads I will find the minColumns
		int numLinesToAnalyse = min(numThreads, maxLine - t);

        #pragma omp parallel for
		for (int i = 0 ; i < numLinesToAnalyse; i++){
			int m;
			int threadLine = t + i;
			for (m = 1; m <= n; m++){
				if (matrix[threadLine][m] >= 0){
					break;
				}
			}
			threadsInfo[i].minValidColumn = m;
			threadsInfo[i].isDependent = false;
		}


		// when the number of threads is less than the number of lines to analyse
		if (numLinesToAnalyse < numThreads){
			for (int i = numLinesToAnalyse; i < numThreads; i++){
				threadsInfo[i].minValidColumn = maxColumn;
				threadsInfo[i].isDependent = false;
			}
		}

		

        // now setting the dependencies
		for (int i = 0; i < numThreads; i++){
			if (threadsInfo[i].minValidColumn < maxColumn){
				int threadIndex = i + a[threadsInfo[i].minValidColumn];
				if (threadIndex < numThreads){
					threadsInfo[threadIndex].isDependent = true;
				}
			}
		}

		// now finding the number of threads that will be executed in paralell
		int workThreads;
		for (workThreads = 0; workThreads < numThreads; workThreads++){
			if (threadsInfo[workThreads].isDependent){
				break;
			}
		}
		
		

        #pragma omp parallel for
		for (int w = 0; w < workThreads; w++){
			int m = threadsInfo[w].minValidColumn;
			int threadLine = t + w;
			if (m < maxColumn){
				double max = matrix[threadLine][m];
				for (int i = m; i <= n; i++){
					if (threadLine + a[i] <= b){
						if (matrix[threadLine][i] > max){
							max = matrix[threadLine][i];
						}
						matrix[threadLine + a[i]][i] = max + c[i];
					}
					else{
						break;
					}
				}
			}

		}
		t += workThreads;
	}
	free(threadsInfo);
	//serialforwardEnumeration(matrix, a, c, b, n);
}

void compareValues(double ** matrix, int i, int j, double valueToBeEqual){
	if (matrix[i][j] != valueToBeEqual){
		printf("Erro!!!!!!");
		EXIT_FAILURE;
	}
	else{
		matrix[i][j] = valueToBeEqual;
	}
}

/*This function mount the Knapsack table*/
void serialforwardEnumeration(double ** matrix, int *a, double *c, int b, int n){
	/* Initial ramification */
	//###### Esse for é facilmente paralelizável, mais uma vez ver se compensa passar para GPU (primeiro ver se
	// se copia é feita em paralelo) por causa da passagem para a GPU
	for (int j = 1; j <= n; j++){
		if (a[j] > b){ // for the case that a element of a[i] is bigger than b.
			break;
		}
		compareValues(matrix, a[j], j, c[j]);
		
	}

	/*Ramification of supernodes*/

	for (int t = a[1]; t <= b - a[1]; t++){
		/*verifying that the line is not empty. i: column*/
		int m = 1;
		for (m = 1; m <= n; m++){
			if (matrix[t][m] >= 0){
				break;
			}
		}
		//##### Esse for de baixo talvez seja paralelizável
		/*Ramification */
		if (m != n + 1){
			double max = matrix[t][m];
			for (int i = m; i <= n; i++){
				if (t + a[i] <= b){
					if (matrix[t][i] > max){
						max = matrix[t][i];
					}
					compareValues(matrix, t + a[i], i, max + c[i]);
				}
				else{
					break;
				}
			}
		}
	}
}


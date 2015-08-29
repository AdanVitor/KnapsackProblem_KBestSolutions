
#include "stdlib.h"
#include "GlobalVariables.h"



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
	for (int i = 1; i <= b; i++){
		for (int j = 1; j <= n; j++){
			matrix[i][j] = -1;
		}
	}
	return matrix;
}


/*This function mount the Knapsack table*/
void forwardEnumeration(double ** matrix, int *a, double *c, int b, int n){
	/* Initial ramification */
	//###### Esse for é facilmente paralelizável, mais uma vez ver se compensa passar para GPU (primeiro ver se
	// se copia é feita em paralelo) por causa da passagem para a GPU
	for (int j = 1; j <= n; j++){
		if (a[j] > b){ // for the case that a element of a[i] is bigger than b.
			break;
		}
		matrix[a[j]][j] = c[j];
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
					matrix[t + a[i]][i] = max + c[i];
				}
				else{
					break;
				}
			}
		}
	}
}
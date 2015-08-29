#include "FunctionPrototypes.h"
#include "DefinitionsAndStructures.h"
#include "windows.h"
#include "GlobalVariables.h"
#include "stdio.h"




kList build_initial_best_k_list(double** M, int b, int n, int* a, kList L, int* P, int k, double *c){

	/*idea - first implement the recover of the K solutions, than test*/
	int p, i, j, il, jl, p1;
	L = createEmptyNode();
	kList finalListLPointer = L; // this pointer will point to final of the list. /*will point to the last element of the list*/
	/*first iteration to verify that exist k solution in the table*/
	/*THIS LIST HAVE A LEADER POINT, FOR WHILE - the final list doesn't have the leader point*/
	int counter = 0;
	i = b + 1;
	boolean moreleft = false;
	boolean fim = false;
	while (i > a[1]){
		i = i - 1;
		j = n + 1;
		while (j > 1){
			j = j - 1;
			if (M[i][j] >= 0){
				insertElement(&finalListLPointer, createNode(n, i, j, M[i][j], NULL));
				counter++;
				if (counter == k){
					il = i;
					jl = j;
					moreleft = true;
					i = 0;
					j = 0;
				}
			}
		}
	}
	removeLeaderNode(&L);
	L = sortList(L, counter, &finalListLPointer);
	p = counter;

	//testes
	if (imprimeResultado){
		printf("\n\n Lista inicial \n");
		printKList(L, n);
	}

	//printf("\ntestando %f", finalListLPointer->V);


	// Now the second part of the algorithm


	if ((p == k) && (il > a[1] || jl > 1)){
		fim = true;
	}
	while (fim){
		kList L1 = createEmptyNode(); //for while the list will heave a leader node
		kList finalLastL1Pointer = L1;
		counter = 0;
		i = il + 1;
		fim = false;
		while (i > a[1]){
			i = i - 1;
			j = n + 1;
			if (moreleft){
				j = jl;
				moreleft = false;
			}
			while (j > 1){
				j = j - 1;
				if (M[i][j] > finalListLPointer->V){
					insertElement(&finalLastL1Pointer, createNode(n, i, j, M[i][j], NULL));
					counter++;
					if (counter == k){
						il = i;
						jl = j;
						moreleft = true;
						i = 0;
						j = 0;
					}
				}

			}
		}
		if (!moreleft){
			il = i;
			jl = j;
		}
		// test to the case of no one element in this list - see that it will be work this removeLeaderNode
		removeLeaderNode(&L1);
		p1 = counter;
		if (L1 != NULL){  // I have to see this case because the list L1 may have none element - check this  
			L1 = sortList(L1, counter, &finalLastL1Pointer);
			if (L1->V > finalListLPointer->V){
				L = joinLists(L, L1, k, &finalListLPointer);  //  Atention - in this function joinList I don't do the free in the list - to do that
			}
			else {
				freekList(&L1);
			}
			if (il > a[1] || jl > 1) {
				fim = true;
			}
		}
		else{
			fim = false;
		}
	}

	/*printf("\n\n Lista final:");
	printKList(L, n);
	printf("\n Testando elemento final: %f", finalListLPointer->V); */

	// Starting the backtracking

	/*Recovering the solutions*/

	//printDifBetweenMallocAndFree("build_initial_best_k_list: sem findHidden");
	return findHiddenSolutions(M, b, n, a, L, finalListLPointer, P, k, c, p);

}





kList findHiddenSolutions(double** M, int b, int n, int* a, kList L, kList finalListPointer, int* P, int k, double *c, int listLength){


	kList listPointer = L;
	int listContainKSolutions = (listLength == k);

	// While the list not contains the k solutions I just add the hidden solution
	while (!listContainKSolutions || (listContainKSolutions && (abs(listPointer->V - finalListPointer->V)) > epsilon)){
		if (debug){
			printf("\n\n------------------------------------------\n\n");
			printf("\n\n Lista final parcial \n");
			printKList(L, n);
		}

		// In this implementation I always work with only one level of recursion
		int new_line_index = listPointer->line - a[listPointer->column];
		/* ja acrescentando o a que ta se retirando */

		double aValue = c[listPointer->column];
		int column = listPointer->column;
		int initialColumn = column;

		matrixElementList lineMatrixList;
		matrixElementList temp;
		matrixElementList finalElementList;
		int elementsNumber = 0;



		if (new_line_index >= a[1]){
			while (M[new_line_index][column] < 0){
				column--;
			}

			lineMatrixList = createMatrixNode(aValue + M[new_line_index][column], new_line_index, column, &elementsNumber);
			finalElementList = lineMatrixList;
			column--;



			while (column >= 1){
				if (M[new_line_index][column] < 0){
					column--;
				}
				else{
					addMatrixElementList(&finalElementList, createMatrixNode(aValue + M[new_line_index][column], new_line_index, column, &elementsNumber));
					column--;
				}
			}

			//printDifBetweenMallocAndFree("depois de criar");

			
			
			lineMatrixList = sortLineMatrixList(lineMatrixList, elementsNumber, &finalElementList);

			
			

			// updating the element that was already in the linked list and are being explored
			listPointer->X[initialColumn]++;  // the first index of X is 1 to keep the standard
			listPointer->line = lineMatrixList->line;
			listPointer->column = lineMatrixList->column;

			if (debug){
				printf("\n\n Lista ordenada gerada pelo elemento\n com value: %f , line: %d, coluna: %d \n", listPointer->V, listPointer->line, initialColumn);
				printMatrixElementsList(lineMatrixList);
			}

			// Now analysing which elements of this list will be added in the k best list
			temp = lineMatrixList;
			lineMatrixList = lineMatrixList->next; // the first element of this list is already in the k list because it is the best solution 
			freeMatrixNode(&temp);

			//initMallocCounter();
			while (lineMatrixList != NULL){
				if (!listContainKSolutions || lineMatrixList->objectiveValue > finalListPointer->V){
					//printTamanhoLista(firtElement_LineMatrixList , "antes do addOrdered");
					addOrderedInList(lineMatrixList, L, &finalListPointer, n, listPointer, listContainKSolutions);
					if (!listContainKSolutions){

						listContainKSolutions = ((++listLength) == k);
					}
					if (debug){
						printf("\n Menor valor presente na lista das k melhores %f\n", finalListPointer->V);
						printf("\n Adicionado com objective value: %f \n", lineMatrixList->objectiveValue);
						printf("\n\n Lista final parcial resultante \n");
						printKList(L, n);
					}
				}
				temp = lineMatrixList;
				lineMatrixList = lineMatrixList->next;
				freeMatrixNode(&temp);
				freeNumber++;

			}
			//printDifBetweenMallocAndFree("depois do while");




		}


		listPointer = listPointer->next;

		if (listPointer == NULL){
			break;
		}
	}



	if (imprimeResultado){
		printf("\n\n Novas melhores %d solucoes \n", k);
		printKList(L, n);
	}



	/* Put this code in another function
	- Now finishing the backTrack in each solution and then find the solution vector X*/


	kList pointer = L;
	int column, line;
	double max;
	while (pointer != NULL){
		line = pointer->line;
		column = pointer->column;

		pointer->X[column]++;
		line = line - a[column];

		while (line >= a[1]){
			max = M[line][column];
			for (int j = column; j >= 1; j--){
				if (M[line][j] > max){
					max = M[line][j];
					column = j;
				}
			}
			pointer->X[column]++;
			line = line - a[column];
		}
		pointer = pointer->next;
	}
	if (imprimeResultado){
		printf("\n\n ----- Lista final: %d melhores solucoes ------ \n", k);
		printKList(L, n);
	}


	return L;


}


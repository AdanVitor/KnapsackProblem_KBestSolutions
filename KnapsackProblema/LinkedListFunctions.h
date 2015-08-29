#include "DefinitionsAndStructures.h"
#include "stdafx.h"
#include "GlobalVariables.h"
#include "stdlib.h"
#include "FreeAndMallocFunctions.h"
#include "PrintFunctions.h"

// function that inserts a element in linked list.
void insertElement(kList* L, node Node){
	Node->previous = (*L);
	if ((*L) != NULL){
		Node->next = (*L)->next;
		(*L)->next = Node;
	}
	else{
		Node->next = NULL;
	}
	(*L) = Node;
}



void addNextNode(kList *finalResult, kList* listPointer){
	(*finalResult)->next = (*listPointer);
	(*listPointer)->previous = (*finalResult);
	(*listPointer) = (*listPointer)->next;
	(*finalResult) = (*finalResult)->next;
}


void addOrderedInList(matrixElementList hiddenSolution, kList L, kList* finalListPointer, int n, kList descendantPointer, int listContainKSolutions){
	kList pointer = descendantPointer;

	while (pointer->V > hiddenSolution->objectiveValue){
		pointer = pointer->next;
	}
	if (debug){
		printf("\n Valor do pointer que apontara pro novo valor %f \n", (pointer->previous)->V);
		printf("\n Valor inicial: %f , Valor previous: %f", pointer->V, pointer->previous->V);
	}
	// MELHORAR ESSE ALGORITMO  - NAO PRECISA DESSE IF A TODO MOMENTO POINTER == NULL E listContainKSolutions - essa possibilidade de pointer == NULL so acontece para listContinKSolutions
	// talvez fazer um método sobrecarregado - esse metodo para quando listContainKSolutions e outro para o caso de listContainKSolutions = true;
	if (pointer == NULL){
		insertElement(finalListPointer, createNode(n, hiddenSolution->line, hiddenSolution->column, hiddenSolution->objectiveValue, descendantPointer->X));
	}
	else{
		insertElement(&(pointer->previous), createNode(n, hiddenSolution->line, hiddenSolution->column, hiddenSolution->objectiveValue, descendantPointer->X));
	}
	if (listContainKSolutions){
		kList temp = (*finalListPointer);
		(*finalListPointer) = (temp->previous);
		(*finalListPointer)->next = NULL;
		freeKListNode(&temp);
	}
	if (debug){
		printf("\n Valor adicionado %f", hiddenSolution->objectiveValue);
		printf("\n\n Lista final parcial resultante \n");
		printKList(L, n);
		printf("\n Valor do previous do ponteiro final: %f \n", (*finalListPointer)->previous->V);
		printf("\n\n ----Saindo do addOrderedInList \n");
	}

	/*dar um free nesse hidden solution*/

}




kList joinLists(kList L, kList L1, int objectsNumber, kList* finalListPointer){
	kList resultList = createEmptyNode();
	kList finalResultListPointer = resultList;
	kList pointerL = L;
	kList pointerL1 = L1;
	for (int i = 0; i < objectsNumber; i++){
		if (pointerL == NULL){
			addNextNode(&finalResultListPointer, &pointerL1);
		}
		else if (pointerL1 == NULL){
			addNextNode(&finalResultListPointer, &pointerL);
		}
		else if (pointerL->V > pointerL1->V){
			addNextNode(&finalResultListPointer, &pointerL);
		}
		else{
			addNextNode(&finalResultListPointer, &pointerL1);
		}
	}
	// removing the elements that weren't added.
	freeRemainingNodes(&pointerL);
	freeRemainingNodes(&pointerL1);

	removeLeaderNode(&resultList);
	finalResultListPointer->next = NULL;
	(*finalListPointer) = finalResultListPointer;
	return resultList;
}

void addMatrixElementList(matrixElementList* list, matrixElementNode newNode){
	(*list)->next = newNode;
	(*list) = (*list)->next;
}





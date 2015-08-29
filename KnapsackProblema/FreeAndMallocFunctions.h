#ifndef DEFINITIONS_AND_STRUCTURES
#define DEFINITIONS_AND_STRUCTURES


#include "DefinitionsAndStructures.h"
#include "stdio.h"
#include "stdlib.h"
#include "GlobalVariables.h"
#include "FunctionPrototypes.h"

void allocateGlobalVariables(){
	globalMatrix = (double **)malloc((bMax + 1)*sizeof(double*));
	for (int i = 0; i < (bMax + 1); i++){
		globalMatrix[i] = (double *)malloc((nMax + 1)*sizeof(double));
	}

    // allocate the nodes of Klist
	int allocatedNodes = 4 * kMax;
	int allocatedMatrixElements = 2*nMax;

	globalA = (int*)malloc((nMax + 1)*sizeof(int));
	globalC = (double*)malloc((nMax + 1)*sizeof(double));

	globalKList = createNode();
	node initial = globalKList;

	for (int i = 0; i < allocatedNodes; i++){
		initial->next = createNode();
		initial = initial->next;
	}

	// allocate the nodes of matrixElement
	globalMatrixElementList = createEmptyMatrixNode();
	matrixElementList initialMatrixElement = globalMatrixElementList;

	for (int i = 0; i < allocatedMatrixElements; i++){
		initialMatrixElement->next = createEmptyMatrixNode();
		initialMatrixElement = initialMatrixElement->next;
	}


	// allocating the pointer vector of kList - used in the sortFunctions
	globalKListVectorPointers = (kList*)malloc((allocatedNodes)*sizeof(kList));
	auxGlobalKListVectorPointers = (kList*)malloc((allocatedNodes)*sizeof(kList));

	// the pointer vector of matrixElementList
	globalMatrixElementListVectorPointers = (matrixElementList*)malloc(allocatedMatrixElements*sizeof(matrixElement));
	auxGlobalMatrixElementListVectorPointers = (matrixElementList*)malloc(allocatedMatrixElements*sizeof(matrixElement));
}

void desalocateGlobalVariables(){
	for (int i = 0; i < (bMax + 1); i++){
		free(globalMatrix[i]);
	}
	free(globalA);
	free(globalC);
	
	// desallocating the nodes of Klist
	node kListPointer = globalKList;
	node aux;
	while (kListPointer != NULL){
		aux = kListPointer;
		kListPointer = kListPointer->next;
		free(aux->X);
		free(aux);
	}

	//desallocating the nodes of matrixElement
	matrixElementList matrixElementPointer = globalMatrixElementList;
	matrixElementList auxElemPointer;
	while (matrixElementPointer != NULL){
		auxElemPointer = matrixElementPointer;
		matrixElementPointer = matrixElementPointer->next;
		free(auxElemPointer);
	}


	// desallocating the pointer vector of kList - used in the sortFunctions
	free(globalKListVectorPointers); 
	free(auxGlobalKListVectorPointers); 

	// desallocatiing vector of matrixElementList
	free(globalMatrixElementListVectorPointers); 
	free(auxGlobalMatrixElementListVectorPointers); 


}

node createNode(){
	node L = (node)malloc(sizeof(kListElemen));
	mallocNumber++;
	L->next = NULL;
	L->previous = NULL;
	L->X = (int*)malloc((nMax + 1)*sizeof(int));
	return L;
}

matrixElementNode createEmptyMatrixNode(){
	matrixElementPointer elem = (matrixElementPointer)malloc(sizeof(matrixElement));
	elem->next = NULL;
	return elem;
}

matrixElementNode getMatrixElement(){
	matrixElementNode element = globalMatrixElementList;
	globalMatrixElementList = globalMatrixElementList->next;
	return element;

}




node createEmptyNode(){
	node Node = globalKList;
	globalKList = globalKList->next;
	Node->next = NULL;
	Node->previous = NULL;
	return Node;
}

node createNode(int n, int i, int j, double V, int * initialX){
	node temp = createEmptyNode();
	temp->column = j;
	temp->line = i;
	temp->V = V;
	if (initialX == NULL){
		for (int i = 0; i < n + 1; i++){
			(temp->X)[i] = 0;
		}
	}
	else{
		for (int i = 0; i < n + 1; i++){
			(temp->X)[i] = initialX[i];
		}
	}

	temp->C = 0;
	return temp;
}

void returnNode(node* Node){
	(*Node)->next = globalKList;
	globalKList = (*Node);
}


void freekList(kList* L){
	while ((*L) != NULL){
		kList temp = (*L);
		(*L) = (*L)->next;
		returnNode(&temp);
		freeNumber++;
	}
}

void freeRemainingNodes(kList* L){
	while ((*L) != NULL){
		kList aux = (*L);
		(*L) = (*L)->next;
		returnNode(&aux);
		freeNumber++;
	}
}

void freeKListNode(kList* L){
	kList temp = (*L);
	returnNode(&temp);
	freeNumber++;
}


void removeLeaderNode(kList* L){
	node leader = *L;
	(*L) = (*L)->next;
	if ((*L) != NULL){
		(*L)->previous = NULL;
	}
	returnNode(&leader);
	freeNumber++;
}


matrixElementNode createMatrixNode(double value, int line, int column, int* elementsNumber){
	matrixElementPointer elem = getMatrixElement();
	mallocNumber++;
	elem->objectiveValue = value;
	elem->line = line;
	elem->column = column;
	elem->next = NULL;
	(*elementsNumber)++;
	return elem;
}

void freeMatrixNode(matrixElementNode* elementNode){
	(*elementNode)->next = globalMatrixElementList;
	globalMatrixElementList = (*elementNode);
}
/*
void freeMatrixSpace(double** M, int rowsNumber, int columnsNumber){
	for (int i = 0; i < rowsNumber; i++){
		free(M[i]);
	}
	free(M);
}
*/

#endif



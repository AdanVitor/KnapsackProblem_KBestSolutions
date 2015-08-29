

#include "DefinitionsAndStructures.h"

void sort(kList* L, int li, int hi){
	if (hi <= li){
		return;
	}
	int mid = (li + hi) / 2;
	sort(L, li, mid);
	sort(L, mid + 1, hi);
	merge(L, li, mid, hi);
}

void merge(kList* L, int li, int mid, int hi){
	kList* auxVector = auxGlobalKListVectorPointers;
	mallocNumber += hi - li + 1;

	int i = li;
	int j = mid + 1;
	for (int k = 0; k <= (hi - li); k++){
		if (i > mid) auxVector[k] = L[j++];
		else if (j > hi) auxVector[k] = L[i++];
		else if (L[i]->V > L[j]->V) auxVector[k] = L[i++];
		else auxVector[k] = L[j++];
	}

	/*copying the auxVector*/
	int k = 0;
	for (int i = li; i <= hi; i++){
		L[i] = auxVector[k++];
	}
	freeNumber += hi - li + 1;
}

void mergeSort(kList*L, int vectorSize){
	int hi = vectorSize - 1;
	int mid = hi / 2;
	sort(L, 0, mid);
	sort(L, mid + 1, hi);
	merge(L, 0, mid, hi);
}

kList sortList(kList L, int listSize, kList *finalListPointer){
	//first creating a vector of pointers to auxiliate the process
	kList* pointerVector = globalKListVectorPointers;
	mallocNumber += listSize;
	// pointing the pointers of the vector to the list's elements
	node aux = L;
	for (int i = 0; i < listSize; i++){
		pointerVector[i] = aux;
		aux = aux->next;
	}
	//printVectorList(pointerVector, listSize);

	//sort the vector using mergeSort
	mergeSort(pointerVector, listSize);

	/*changing the pointers of the list to the vector*/
	int i = 0;
	pointerVector[0]->previous = NULL;
	for (i = 0; i < listSize - 1; i++){
		pointerVector[i]->next = pointerVector[i + 1];
		pointerVector[i + 1]->previous = pointerVector[i];
	}
	pointerVector[i]->next = NULL;
	L = pointerVector[0];
	(*finalListPointer) = pointerVector[listSize - 1];
	// liberando a memória do vetor de vetor de ponteiros
	freeNumber += listSize;
	return L;

}


void sort(matrixElementList* L, int li, int hi){
	if (hi <= li){
		return;
	}
	int mid = (li + hi) / 2;
	sort(L, li, mid);
	sort(L, mid + 1, hi);
	merge(L, li, mid, hi);
}

void merge(matrixElementList* L, int li, int mid, int hi){
	matrixElementList* auxVector = auxGlobalMatrixElementListVectorPointers;
	mallocNumber += hi - li + 1;

	int i = li;
	int j = mid + 1;
	for (int k = 0; k <= (hi - li); k++){
		if (i > mid) auxVector[k] = L[j++];
		else if (j > hi) auxVector[k] = L[i++];
		else if (L[i]->objectiveValue > L[j]->objectiveValue) auxVector[k] = L[i++];
		else auxVector[k] = L[j++];
	}

	/*copying the auxVector*/
	int k = 0;
	for (int i = li; i <= hi; i++){
		L[i] = auxVector[k++];
	}
	freeNumber += hi - li + 1;
}

void mergeSort(matrixElementList* L, int vectorSize){
	int hi = vectorSize - 1;
	int mid = hi / 2;
	sort(L, 0, mid);
	sort(L, mid + 1, hi);
	merge(L, 0, mid, hi);
}

matrixElementList sortLineMatrixList(matrixElementList L, int listSize, matrixElementList *finalListPointer){
	//first creating a vector of pointers to auxiliate the process
	matrixElementList* pointerVector;
	pointerVector = globalMatrixElementListVectorPointers;
	mallocNumber += listSize;
	// pointing the pointers of the vector to the list's elements
	matrixElementNode aux = L;
	for (int i = 0; i < listSize; i++){
		pointerVector[i] = aux;
		aux = aux->next;
	}
	//printVectorList(pointerVector, listSize);

	//sort the vector using mergeSort
	mergeSort(pointerVector, listSize);

	/*changing the pointers of the list to the vector*/
	int i = 0;
	for (i = 0; i < listSize - 1; i++){
		pointerVector[i]->next = pointerVector[i + 1];
	}
	pointerVector[i]->next = NULL;
	L = pointerVector[0];
	(*finalListPointer) = pointerVector[listSize - 1];
	freeNumber += listSize;
	return L;
}


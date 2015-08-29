
#ifndef PRINT_FUNCTIONS
#define PRINT_FUNCTIONS

#include "GlobalVariables.h"

void printResultVector(double *times, int size, char* message){
	fprintf(outFile, "\n %s ", message);
	for (int i = 0; i < size; i++){
		fprintf(outFile, "%.2f ", times[i]);
	}
	fprintf(outFile, " ]; ");
}


void printDifBetweenMallocAndFree(char* message){
	printf("Diferenca  %s method: malloc - free = %d\n", message, mallocNumber - freeNumber);
}

void printMatrixElementsList(matrixElementList list){
	printf("\n matrixElementList");
	printf("\n");
	while (list != NULL){
		printf("\nElem com valor %2.0f , localizacao: %d , %d ", list->objectiveValue, list->line, list->column);
		list = list->next;
	}
}

void printKList(kList list, int n){
	bool debug = false;
	printf("\n");
	while (list != NULL){
		if (debug){
			printf("\nValor objetivo %2.0f , localizacao: %2d , %2d ", list->V, list->line, list->column);
		}
		else{
			printf("\n%2.0f", list->V, list->line, list->column);
		}
		printf(" ------");
		for (int i = 1; i <= n; i++){
			printf("  %d", list->X[i]);
		}
		list = list->next;
	}
}

void printVectorList(kList* vector, int size){
	for (int i = 0; i < size; i++){
		printf("\nElem %2.0f , localizacao: %d , %d ", vector[i]->V, vector[i]->line, vector[i]->column);
	}
}

void printFirstElements(kList list, int elementsNumber){
	bool debug = false;
	fprintf(outFile, "\n %%{ Obtendo as %d melhores solucoes\n", elementsNumber);
	for (int i = 0; i < elementsNumber; i++){
		fprintf(outFile, "\nValor objetivo %2.0f , localizacao: %2d , %2d ", list->V, list->line, list->column);
		list = list->next;
	}
	fprintf(outFile, "\n %%}");
}

void printIntVector(int* vector, int size){
	for (int i = 0; i < size; i++){
		fprintf(outFile, "%d ", vector[i]);
	}
}

void printResults(double* forwardTime, double* backwardTime, double* totalTime, int* varyingVector, int size , char* axisVectorName , int testNumber , char* variableName){
	printResultVector(forwardTime, size, "forwardTimes = [");
	printResultVector(backwardTime, size, "backwardTimes = [");
	printResultVector(totalTime, size, "totalTimes = [");

	fprintf(outFile, "\n %s = [" , axisVectorName);
	printIntVector(varyingVector, size);
	fprintf(outFile, " ] ;\n\n");
	fprintf(outFile, "\n figure (%d); "
		"\n plot(%s, forwardTimes, 'b'); "
		"\n hold on; "
		"\n plot(%s, backwardTimes, 'r'); "
		"\n hold on; "
		"\n plot(%s, totalTimes , 'g'); "
		"\n hold off; "
		"\n legend('Tempo forward', 'Tempo Backward', 'Tempo Total'); "
		"\n title('Effect of varying %s') ;"
		"\n xlabel('Valores de  %s') ;"
		"\n ylabel('Tempo execução'); \n\n\n "
		, testNumber, axisVectorName, axisVectorName, axisVectorName , variableName, variableName);
	   
	// print the matlab functions of print
	

	printf("\n mallocNumber - freeNumber: %d ", mallocNumber - freeNumber);
}

void printMatrix(double **matrix, int rowNumber, int columnNumber){
	for (int i = 0; i < rowNumber; i++){
		printf("\n");
		for (int j = 0; j < columnNumber; j++){
			printf("%3.0f ", matrix[i][j]);
		}
	}
}


void printTamanhoLista(matrixElementList list, char* message){
	int count = 0;
	while (list != NULL){
		list = list->next;
		count++;
	}
	printf("\n***tamanho da lista %s = %d", message, count);
}


void printSolutionMatrix(int **matrix, int rowsNumber, int columnsNumber){
	for (int i = 0; i < rowsNumber; i++){
		for (int j = 1; j < columnsNumber; j++){
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

void printVector(int* vector, int size){
	for (int i = 0; i < size; i++){
		printf("%d ", vector[i]);
	}
}


void printBrueteForceKBest(objectiveValueList list, int k){
	while (list != NULL){
		printf("\n%.2f ", list->objectiveValue);
		list = list->prox;
	}
	printf("\n");
}

#endif



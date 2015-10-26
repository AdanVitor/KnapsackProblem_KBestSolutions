// KnapsackProblema.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include "Math.h"
#include "windows.h"
#include "time.h"
#include "stdio.h"
#include "Headers.h"



void generateTestCase( ){
	
// defining a seed
srand(1000);
testCase1();
printf("\nTerminou teste Case 1");

testCase2();
printf("\nTerminou teste Case 2");

testCase3();
printf("\nTerminou teste Case 3");


getchar();

}


void testOpenMP(){
	// This statement should only print once
	printf("Starting Program!\n");

#pragma omp parallel
	{
		// This statement will run on each thread.
		// If there are 4 threads, this will execute 4 times in total
		printf("Running on multiple threads\n");
	}

	// We're out of the parallelized secion.
	// Therefor, this should execute only once
	printf("Finished!\n");
}


void main(){

	// testOpenMP();

	int NumProc = omp_get_num_procs()/2;
	omp_set_num_threads(NumProc);

	boolean testPdfOn = false;
	if (!testPdfOn){
		generateTestCase();
	}
	else{
		imprimeResultado = true;
		simpleTestCase();
	}

	

}







#ifndef DEFINITIONS
#define DEFINITIONS

//L(i) is the best solution in the list 
typedef struct kListElement kListElemen;
typedef kListElemen *node;
typedef kListElemen *kList;

struct kListElement{
	int* X; // the vector solution - tem os indices em ordem crescente a1, a2, a3, ... etc...
	double V; // V: the objective function value
	int column, line, C; //J,T the original line and matrix Mbxn where the solution was identified, C: an 0-1 control variabel that indicates wheter the vector solution L(i).X has already been recovered or not.
	node next;
	node previous;
};

typedef struct matrixElement matrixElement;
typedef matrixElement* matrixElementPointer;
typedef matrixElement* matrixElementsList;
typedef matrixElement* matrixElementNode;
typedef matrixElement* matrixElementList;

struct matrixElement{
	int line, column;
	double objectiveValue;
	matrixElementPointer next;
};

typedef struct valueElement valueElement;
typedef valueElement* objectiveValueNode;
typedef valueElement* objectiveValueList;

struct valueElement{
	objectiveValueNode previous, prox;
	double objectiveValue;
};

#endif
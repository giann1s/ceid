#include <search.h>

typedef struct fraction{
	int ar;
	int par;
}Fraction;

typedef struct expression{
	char operator;
	Fraction op1;
	Fraction op2;
}Expression;

Expression readExpression(void); // reads an expression of the following form + 1/5 3/15

void sortInc4String(char *base,int numOfElements, int strWidth);
void sortDec4String(char *base,int numOfElements, int strWidth);

void sortInc4Int(int *base,int numOfElements, int width);
void sortDec4Int(int *base,int numOfElements, int width);


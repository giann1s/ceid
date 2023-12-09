typedef struct fraction{
	int ar;
	int par;
}Fraction;

typedef struct expression{
	char operator;
	Fraction op1;
	Fraction op2;
}Expression;

Expression readExpression(void);


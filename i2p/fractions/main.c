#include <stdio.h>
#include "i2p.h"

int gcd(int num1, int num2);

int main() {
    int i, exp;

    char input[100];
    char oper;
	int num1, den1, num2, den2, terms_gcd;

	int numerator, denominator;

	printf("How many expressions do you want to insert?: ");
    scanf("%d", &exp);

    for (i = 0; i<exp; i++) {
        readExpression(&oper, &num1, &den1, &num2, &den2);

        switch (oper) {
        	case '+':
        		numerator = num1 * den2 + num2*den1;
        		denominator = den1 * den2;
				break;
			case '-':
        		numerator = num1 * den2 - num2*den1;
        		denominator = den1 * den2;
				break;
			case '*':
				numerator = num1 * num2;
				denominator = den1 * den2;
				break;
			case '/':
				numerator = num1 * den2;
				denominator = num2 * den1;
				break;
		}

		terms_gcd = gcd(numerator, denominator);

		numerator /= terms_gcd;
		denominator /= terms_gcd;

		printf("%d / %d\n", numerator, denominator);
    }

    return 0;
}

int gcd(int num1, int num2) {
	int i;
	int gcd = 1;
	int smallest_int = num1 < num2 ? num1 : num2;
	
	for (i = 2; i <= smallest_int; i++) {
		if (num1%i == 0 && num2%i == 0) {
			gcd = i;
		}
	}

	return gcd;
}

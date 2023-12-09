/*
Πάρε από τον χρήστη τον αριθμό των εκφράσεων
Για κάθε μία από αυτές
	Πάρε την έκφραση από τον χρήστη
	Κάνε την αντίστοιχη πράξη στα κλάσματα
	Βρες τον μέγιστο κοινό διαιρέτη του αριθμητή και του παρονομαστή
	Απλοποίησε το κλάσμα διαιρώντας τους με τον ΜΚΔ
*/

#include <stdio.h>
#include "i2p.h"

int gcd(int num1, int num2);

int main() {
    int i, exp;
    int terms_gcd;

    Fraction result_frac;
    Expression in_expression;

    printf("How many expressions do you want to insert?: ");
    scanf("%d", &exp);

    for (i = 0; i < exp; i++) {
        
        in_expression = readExpression();

        switch (in_expression.operator) {
            case '+':
                result_frac.ar = in_expression.op1.ar * in_expression.op2.par + in_expression.op2.ar * in_expression.op1.par;
                result_frac.par = in_expression.op1.par * in_expression.op2.par;
                break;
            case '-':
                result_frac.ar = in_expression.op1.ar * in_expression.op2.par - in_expression.op2.ar * in_expression.op1.par;
                result_frac.par = in_expression.op1.par * in_expression.op2.par;
                break;
            case '*':
                result_frac.ar = in_expression.op1.ar * in_expression.op2.ar;
                result_frac.par = in_expression.op1.par * in_expression.op2.par;
                break;
            case '/':
                result_frac.ar = in_expression.op1.ar * in_expression.op2.par;
                result_frac.par = in_expression.op2.ar * in_expression.op1.par;
                break;
        }

        terms_gcd = gcd(result_frac.ar, result_frac.par);

        result_frac.ar /= terms_gcd;
        result_frac.par /= terms_gcd;

        printf("%d / %d\n", result_frac.ar, result_frac.par);
    }

    return 0;
}

int gcd(int num1, int num2) {
    int remainder;

    while (num2 != 0) {  // Use Euclid's algorithm
        remainder = num1 % num2;
        num1 = num2;
        num2 = remainder;
    }

    return num1;
}

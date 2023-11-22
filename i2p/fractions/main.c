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

    char input[100];
    char oper;
    int num1, den1, num2, den2, terms_gcd;

    int numerator, denominator;

    printf("How many expressions do you want to insert?: ");
    scanf("%d", &exp);

    for (i = 0; i < exp; i++) {
        readExpression(&oper, &num1, &den1, &num2, &den2);

        switch (oper) {
            case '+':
                numerator = num1 * den2 + num2 * den1;
                denominator = den1 * den2;
                break;
            case '-':
                numerator = num1 * den2 - num2 * den1;
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
    int remainder;

    while (num2 != 0) {  // Use Euclid's algorithm
        remainder = num1 % num2;
        num1 = num2;
        num2 = remainder;
    }

    return num1;
}

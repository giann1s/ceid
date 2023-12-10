#include <stdio.h>

int main() {
    register int i, number, digit, sum;

    printf("Four-digit armstrong numbers: ");
    for (i=1000; i<10000; i++) {
        number = i;
        sum = 0;

        while (number != 0) {
            digit = number % 10;
            number /=10;
            sum += digit * digit * digit * digit;
        }

        if (sum == i) printf("%d ", i);
    }

    printf("\n");

    return 0;
}

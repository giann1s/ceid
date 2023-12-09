#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_armstrong(int number);

int main() {
    int i;

    printf("Four-digit armstrong numbers: ");

    for (i=1000; i<10000; i++) {
        if (is_armstrong(i)) {
            printf("%d ", i);
        }
    }

    printf("\n");

    return 0;
}

bool is_armstrong(int number) {
    int digits = 0, original_num = number, sum = 0;

    while (number != 0) {
        digits++;
        number /= 10;
    }

    number = original_num;

    while (number != 0) {
        sum += pow(number % 10, digits);
        number /= 10;
    }

    return sum == original_num;
}

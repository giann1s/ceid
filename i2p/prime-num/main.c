#include <stdio.h>

void divisors(int num, int array[]);

int main() {
    int num, array_size;

    do {
        printf("Insert an integer greater than one: ");
        scanf("%d",  &num);
    }
    while (num < 2);

    int divs[num / 2 + 1];

    divisors(num, divs);

    if (divs[0] == 2) {
        printf("The number is prime\n");
    }
    else {
        printf("The number isn't prime\nDivisors: ");
        for (int i = 1; i <= divs[0]; i++) {
            printf("%d ", divs[i]);
        }
        printf("\n");
    }

    return 0;
}

void divisors(int num, int array[]) {
    array[0] = 1;   // 1st element of the array is the number of divisors

    for (int i = 1; i < num / 2 + 1; i++) {
        if (num % i == 0) {
            array[array[0]] = i;
            array[0]++;
        }
    }

    array[array[0]] = num;
}

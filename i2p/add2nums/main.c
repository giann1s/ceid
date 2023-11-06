#include <stdio.h>

int main() {
    int num1, num2, sum;

    printf("Type the first number: ");
    scanf("%d", &num1);

    printf("Type the second number: ");
    scanf("%d", &num2);

    sum = num1 + num2;

    printf("The sum is %d\n", sum);

    return 0;  
}

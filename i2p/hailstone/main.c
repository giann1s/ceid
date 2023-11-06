#include <stdio.h>

void display_hailstone(int num);

int main(void) {
    int input;

    printf("Enter the a positive integer to calculate its hailstone sequence: ");
    scanf("%d", &input);

    display_hailstone(input);

    return 0;
}

void display_hailstone(int num) {

    printf("Sequence: %d ", num);

    while(num != 1) {
        if(num%2 == 0) {
            num = num / 2;
        }
        else {
            num = 3 * num + 1;
        }

        printf("%d ", num);
    }

    printf("\n");
}

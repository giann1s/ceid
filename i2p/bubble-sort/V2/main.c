#include <stdio.h>

void bubble_sort(int integers[], int size);
void move_bubble_up(int integers[], int size);

int main() {
    int i;
    int integers[12] = {3, 0, 2, 7,  5,  6,  9, 1, 8, 4, 9, 8};

    printf("Array: ");
    for (i=0; i<12; i++) printf("\t%d", integers[i]);
    printf("\n\n");

    bubble_sort(integers, 12);

    printf("\nResult:");
    for (i=0; i<12; i++) printf("\t%d", integers[i]);
    printf("\n");

    return 0;
}

void bubble_sort(int integers[], int size) {
    int i;

    for (i=0; i<size-1; i++) {
        printf("== Pass %d ==\n", i+1);
        move_bubble_up(integers, size-i);
        printf("\n");
    }
}

void move_bubble_up(int integers[], int size) {
    int i, j, temp;

    for (i = 0; i < size-1; i++) {
        if (integers[i] > integers[i+1]) {
            temp = integers[i];
            integers[i] = integers[i+1];
            integers[i+1] = temp;
            
            printf("Iteration %d:", i+1);
            for (j=0; j<size; j++) printf("\t%d", integers[j]);
            printf("\n");
        }
    }
}

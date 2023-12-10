#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void bubble_sort(int *integers[], int size);
void move_bubble_up(int *integers[], int size);
bool is_sorted(int *integers[], int size);

int main() {
    int i;
    int data[10] = {3,5,4,7,2,8,1,0,9,6};
    int *integers[10];

    for (i=0; i<10; i++) {
        integers[i] = malloc(sizeof(int));
        *integers[i] = data[i];
    }

    printf("Array: ");
    for (i=0; i<10; i++) printf("\t%d", *integers[i]);
    printf("\n\n");

    bubble_sort(integers, 10);

    printf("Result:");
    for (i=0; i<10; i++) printf("\t%d", *integers[i]);
    printf("\n");

    for (i=0; i<10; i++) {
        free(integers[i]);
    }

    return 0;
}

void bubble_sort(int *integers[], int size) {
    int i;

    if (size != 1) {
        for (i=0; i<size-1 && ! is_sorted(integers, size); i++) {
            move_bubble_up(integers, size);
            bubble_sort(integers, size-i);
        }
    }
}

void move_bubble_up(int *integers[], int size) {
    int i, j, temp;

    for (i = 0; i < size-1; i++) {
        if (*integers[i] > *integers[i+1]) {
            temp = *integers[i];
            *integers[i] = *integers[i+1];
            *integers[i+1] = temp;
        }
    }
}

bool is_sorted(int *integers[], int size) {
    int i;
    bool sorted = true;

    for (i = 1; (i<size) && sorted; i++) {
        if (*integers[i] < *integers[i-1]) {
            sorted = false;
        }
    }

    return sorted;
}

#include <stdio.h>

void bubble_sort(int integers[], int size);
void move_bubble_up(int integers[], int size);

int main() {
    int i;
    int integers[10] = {3,5,4,7,2,8,1,0,9,6};

    printf("Array: ");
    for (i=0; i<10; i++) printf("\t%d", integers[i]);
    printf("\n\n");

    bubble_sort(integers, 10);

    printf("\nResult:");
    for (i=0; i<10; i++) printf("\t%d", integers[i]);
    printf("\n");

    return 0;
}

void bubble_sort(int integers[], int size) {
    move_bubble_up(integers, size);
}

void move_bubble_up(int integers[], int size) {
    int i, j, temp;

    for (i = 0; i < size-1; i++) {
        if (integers[i] > integers[i+1]) {
            temp = integers[i];
            integers[i] = integers[i+1];
            integers[i+1] = temp;
        }

        printf("Pass %d:", i+1);
        for (j=0; j<size; j++) printf("\t%d", integers[j]);
        printf("\n");
    }
}

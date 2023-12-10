#include <stdio.h>
#include <stdbool.h>

void bubble_sort(int integers[], int size);
void move_bubble_up(int integers[], int size);
bool is_sorted(int integers[], int size);

int main() {
    int i;
    int integers[6] = {1,0,4,3,5,2};

    printf("Array: ");
    for (i=0; i<6; i++) printf("\t%d", integers[i]);
    printf("\n\n");

    bubble_sort(integers, 6);

    printf("Result:");
    for (i=0; i<6; i++) printf("\t%d", integers[i]);
    printf("\n");

    return 0;
}

void bubble_sort(int integers[], int size) {
    if (size != 1 && ! is_sorted(integers, size)) {
        move_bubble_up(integers, size);
        bubble_sort(integers, size-1);
    }
}

void move_bubble_up(int integers[], int size) {
    int i, j, temp;

    for (i = 0; i < size-1; i++) {
        if (integers[i] > integers[i+1]) {
            temp = integers[i];
            integers[i] = integers[i+1];
            integers[i+1] = temp;
        }
    }
}

bool is_sorted(int integers[], int size) {
    int i;
    bool sorted = true;

    for (i = 1; (i<size) && sorted; i++) {
        if (integers[i] < integers[i-1]) {
            sorted = false;
        }
    }

    return sorted;
}

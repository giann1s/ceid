#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "i2p.h"

#define N 15

/*
Δημιούργησε μια λίστα Ν ακερέιων
Ταξινόμησε την λίστα με αύξουσα σειρά
Εμφάνησε την λίστα
Αντέστρεψε την λίστα
Εμφάνησε την λίστα
*/

void bubble_sort(int integers[], int size);
// void reverse_integers(int integers[], int size);

int main() {
    int i, integers[N];
    bool swapped = true;

    srand(time(NULL));
    rand();
    for (i = 0; i < N; i++) {
        integers[i] = rand();
    }

    //V1 sortInc4Int(integers, sizeof(integers)/sizeof(integers[0]), sizeof(integers[0]));
    
    bubble_sort(integers, N);

    printf("Ascending: ");
    for (i = 0; i < N; i++) {
        printf("%d ", integers[i]);
    }
    printf("\n");

    reverse_integers(integers, sizeof(integers)/sizeof(integers[0]));

    printf("Descending: ");
    for (i = 0; i < N; i++) {
        printf("%d ", integers[i]);
    }

    return 0;
}

void bubble_sort(int integers[], int size) {
    int i, temp;
    bool swapped = true;

    while (swapped == true) {
        swapped = false;

        for (i = 0; i < size ; i++) {
            if (integers[i] > integers[i+1]) {
                temp = integers[i];
                integers[i] = integers[i+1];
                integers[i+1] = temp;

                swapped = true;
            }
        }
    }
}

void reverse_integers(int integers[], int size) {
    int i, temp;

    for (i = 0; i < size/2; i++) {
        temp = integers[i];
        integers[i] = integers[size-i-1];
        integers[size-i-1] = temp;
    }
}

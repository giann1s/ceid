#include <stdio.h>
#include <string.h>

void bubble_sort(int max_length, char strings[][max_length], int size);
void move_bubble_up(int max_length, char strings[][max_length], int size);

int main() {
    int i;
    char strings[11][4] = {"cde", "abc", "cef","abb", "aab", "klm","kab", "gbc", "gab", "aaa", "abc"};

    printf("\nStrings:");
    for (i=0; i<11; i++) printf("\t%s", strings[i]);
    printf("\n\n");

    bubble_sort(4, strings, 11);

    printf("\nResult:");
    for (i=0; i<11; i++) printf("\t%s", strings[i]);
    printf("\n");

    return 0;
}

void bubble_sort(int max_length, char strings[][max_length], int size) {
    int i;

    for (i=0; i<size-1; i++) {
        printf("== Pass %d ==\n", i+1);
        move_bubble_up(max_length, strings, size-i);
        printf("\n");
    }
}

void move_bubble_up(int max_length, char strings[][max_length], int size) {
    int i, j, swap = -1;    // -1: not decided, 0: no swap, 1: swap
    char temp[max_length];

    for (i = 0; i < size-1; i++) {
        for (j=0; j<max_length && swap == -1; j++) {
            if (strings[i][j] > strings[i+1][j]) swap = 1;
            else if (strings[i][j] != strings[i+1][j]) swap = 0;
        }

        if (swap == 1) {
            strcpy(temp, strings[i]);
            strcpy(strings[i], strings[i+1]);
            strcpy(strings[i+1], temp);
            
            printf("Iteration %d:", i+1);
            for (j=0; j<size; j++) printf("\t%s", strings[j]);
            printf("\n");
        }
        swap = -1;
    }
}

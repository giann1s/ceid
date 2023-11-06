#include <stdio.h>

int next_fibonacci(int pnum, int cnum);
void print_int_array(int array[], int size);

int main(void) {
    int nums = 0;

    printf("How many fibonacci numbers to calculate?: ");
    scanf("%d", &nums);

    int seq[nums];
    seq[0] = 0;
    seq[1] = 1;

    for (int i = 2; i < nums; i++) {
        seq[i] = next_fibonacci(seq[i - 1], seq[i - 2]);
    }

    print_int_array(seq, nums);

    return 0;
}

int next_fibonacci(int pnum, int cnum) {
    int next_num = pnum + cnum;
    return next_num;
}

void print_int_array(int array[], int size) {
    printf("Sequence: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

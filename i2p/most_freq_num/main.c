#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int *sort_integers(int array[], int size);

int most_freq_int(int array[], int size);

int main() {
    int nums_stored = 0;
    int num = 0;

    do {
        printf("How many numbers do you want to insert (>1) ?: ");
        scanf("%d", &nums_stored);
    } while (nums_stored < 2);

    int nums[nums_stored];

    printf("Insert the numbers one by one\n");
    for (int i = 0; i < nums_stored; i++) {
        scanf("%d", &nums[i]);
    }

    memcpy(nums, sort_integers(nums, nums_stored), sizeof(nums));

    num = most_freq_int(nums, nums_stored);

    printf("Most frequent number: %d\n", num);

    return 0;
}

int *sort_integers(int array[], int size) {
    bool sorted = false;
    int cnum;
    int i = 1;

    while (sorted == false) {
        if (array[i] < array[i-1]) {
            cnum = array[i];
            array[i] = array[i-1];
            array[i-1] = cnum;

            i = 1;
            continue;
        }
        i++;

        if (i == size) {
            sorted = true;
        }
    }

    return array;
}

int most_freq_int(int array[], int size) {
    int num = array[0];
    int max_count = 0;
    int count = 1;

    for (int i = 1; i < size; i++) {
        if (array[i] == array[i - 1]) {
            count++;

            if (count > max_count) {
                max_count = count;
                num = array[i - 1];
            }
        }
        else {
            count = 1;
        }
    }

    return num;
}

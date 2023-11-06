#include <stdio.h>

int max_int(int array[], int size);

int min_int(int array[], int size);

int main() {
    int option, nums;

    do {
        printf("Select\n1. Display Min\n2. Display Max\n");
        scanf("%d", &option);

    } while (option != 1 && option != 2);

    printf("How many numbers do you want to type?: ");
    scanf("%d", &nums);

    int nums_array[nums];

    for (int i=0; i<nums; i++) {
        scanf("%d", &nums_array[i]);
    }


    // V2
    if (option == 1) {
        printf("Min %d\n", min_int(nums_array, nums));
    }
    else {
        printf("Max: %d\n", max_int(nums_array, nums));
    }

}

int max_int(int array[], int size) {
    int max = array[0];

    for (int i=1; i<size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    return max;
}

int min_int(int array[], int size) {
    int min = array[0];

    for (int i=1; i<size; i++) {
        if (array[i] < min) {
            min = array[i];
        }
    }

    return min;
}

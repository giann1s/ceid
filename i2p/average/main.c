#include <stdio.h>

float average(int array[], int size);

int main() {
	int nums_stored;
	int i;
	float aver = 0;

    printf("How many numbers do you want to insert?: ");
    scanf("%d", &nums_stored);

    if (nums_stored < 2) {
        printf("The number must be at least 2\n");
        return 1;
    }

    int nums[nums_stored];

    printf("Insert the numbers one by one\n");
    
    for (int i = 0; i < nums_stored; i++) {
        scanf("%d", &nums[i]);
    }

    aver = average(nums, nums_stored);

	printf("The average is: %f\n", aver);
}

float average(int array[], int size) {
	float average = 0;
	int i;
	for (i = 0; i < size; i++) {
		average += array[i];
	}

	average = (float) average / size;
	return average;
}

#include <stdio.h>

int main() {
    char str[] = "Hello World!";
    int size = sizeof(str)/sizeof(str[0]);

    for (int i = 0; i < size - 1; i++) {
        printf("%c\n", str[i]);
    }

    return 0;
}

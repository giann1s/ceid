#include <stdio.h>
#include <string.h>

int main() {
    int size;
    char name[100];

    printf("Type the name: ");
    scanf("%s", name);
    printf("\n");

    size=strlen(name);

    //1
    printf("%s\n", name);
    printf("\n");

    //2
    for (int i=0; i<size;i++) {
        printf("%c\n", name[i]);
    }
    printf("\n");

    //3
    for (int i=0; i<size;i++) {
        printf("%s\n", name+i);
    }
    printf("\n");

    //4
    for (int i=size; i>0;i--) {
        for (int j=0; j<i;j++) {
            printf("%c", name[j]);
        }
        printf("\n");
    }
    printf("\n");
}

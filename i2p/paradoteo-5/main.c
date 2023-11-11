#include <stdio.h>
#include <string.h>

void display_menu();

int get_user_option();

void get_name(char name[]);

void str_reverse(char array[], int size);

void print2(char name[]);
void print3(char name[], int size);
void print4(char name[], int size);
void print5(char name[], int size);
void print6(char name[], int size);
void print7(char name[], int size);

int main() {
    int size, option;
    char name[100] = "";

    do {
        option = get_user_option();
        size = strlen(name);

        switch (option) {
            case 0:
                break;
            case 1:
                get_name(name);
                break;
            case 2:
                print2(name);
                break;
            case 3:
                print3(name, size);
                break;
            case 4:
                print4(name, size);
                break;
            case 5:
                print5(name, size);
                break;
            case 6:
                print6(name, size);
                break;
            case 7:
                print7(name, size);
                break;
        }
        printf("\n");

    } while (option != 0);

    return 0;
}

void display_menu() {
    char menu[] =
    "0. Exit\n"
    "1. Insert name\n"
    "2. Print name with \%s\n"
    "3. Print name with \%c\n"
    "4. Print each character in a seperate row\n"
    "5. Print name by removing one more letter in each row (starting with first)\n"
    "6. Print name by removing one more letter in each row (starting with last)\n"
    "7. Print name reversed using option 6\n";
    printf("%s", menu);

    printf("Type option number: ");
}

int get_user_option() {
    int option = -1;

    do {
        display_menu();
        
        scanf("%d", &option);
        printf("\n");
    }
    while (option % 1 != 0 || option < 0 || option > 7);

    return option;
}

void get_name(char name[]) {
    printf("Type the name: ");
    scanf("%s", name);
}

void str_reverse(char array[], int size) {
    char temp;

    for (int i=0; i<size/2; i++) {
        temp = array[i];
        array[i]=array[size-i-1];
        array[size-i-1]=temp;
    }
}

void print2(char name[]) {
    printf("%s\n", name);
}

void print3(char name[], int size) {
    int i=0;
    while (name[i] != '\0') {
        printf("%c", name[i++]);
    }
    printf("\n");
}

void print4(char name[], int size) {
    for (int i=0; i<size; i++) {
        printf("%c\n", name[i]);
    }
}

void print5(char name[], int size) {
    for (int i=0; i<size; i++) {
        printf("%s\n", name+i);
    }
}

void print6(char name[], int size) {
    for (int i=size; i>0; i--) {
        for (int j=0; j<i;j++) {
            printf("%c", name[j]);
        }
        printf("\n");
    }
}

void print7(char name[], int size) {
    char name_copy[size+1];

    for (int i = 0; i<size; i++) {
        name_copy[i]=name[i];
    }
    name_copy[size]='\0';
    str_reverse(name_copy, size);

    print6(name_copy, size);
}

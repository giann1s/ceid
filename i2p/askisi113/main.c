#define ADD 1
#define SUB 2
#define MUL 3
#define DIV 4

#include <stdio.h>
#include <string.h>

void display_menu();

int get_user_option();

double get_num(int num);

void do_operation(int operation, double num1, double num2);

int main() {
    int option = -1;
    double num1, num2;

    do {
        option = get_user_option();

        if (option == 0) {
            return 0;
        }

        num1 = get_num(1);
        num2 = get_num(2);
        do_operation(option, num1, num2);

    } while (option != 0);

    return 0;
}

void display_menu() {
    char menu[] =
    "Select the desired operation\n"
    "0. Exit\n"
    "1. Addition (+)\n"
    "2. Subtraciton (-)\n"
    "3. Multimplication (*)\n"
    "4. Division (/)\n";
    printf("%s", menu);
}

int get_user_option() {
    int option = -1;

    do {
        display_menu();
        
        scanf("%d", &option);
    }
    while (option % 1 != 0 || option < 0 || option > 4);

    return option;
}

double get_num(int index) {
    double num;

    printf("Type the  number %d: ", index);
    scanf("%lf", &num);

    return num;
}

void do_operation(int operation, double num1, double num2) {

    switch (operation) {
    case ADD:
        printf("The result is: %f", num1 + num2);
        break;
    case SUB:
        printf("The result is: %f", num1 - num2);
        break;
    case MUL:
        printf("The result is: %f", num1 * num2);
        break;
    case DIV:
        if (num2 != 0) {
            printf("%f", num1 / num2);
        }
        else
            printf("Invalid Operation!");
        break;
    default:
        break;
    }
    printf("\n\n");
}

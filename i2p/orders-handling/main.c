#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define small_bottle_cost 0.008
#define big_bottle_cost 0.02

// Positive integers are used
// for selecting specific order
// (status_idx in function display_orders)
#define ANY_STATUS -1
#define PENDING -2
#define READY -3
#define CLOSED -4

#define PLACE 1
#define CLOSE 2

#define MAX_DATA_LINE_LEN 150
#define FULL_NAME "%[a-zA-Z ]"
#define DATE "%[0-9/]"

typedef struct order {
    int status;

    char customer_name[22];

    char creation_date[11];
    char date[11];
    char execution_date[11];

    int small_bottles;
    int big_bottles;

    float initial_price;
    float discount;
} Order;

int get_choice();
Order get_order();
void display_orders(Order orders[], int num, int status);
void export_orders(char filename[], Order orders[], int orders_num, int status);
void import_orders(char filename[], Order orders[], int *orders_num);
void modify_order(Order orders[], int orders_num, int action);

int main() {
    int orders_num=0, choice = -1;
    Order orders[10];

    do {
        choice = get_choice();

        switch (choice) {
            case 0:
                break;
            case 1:
                orders[orders_num] = get_order();
                orders_num++;
                break;
            case 2:
                display_orders(orders, orders_num, ANY_STATUS);
                break;
            case 3:
                display_orders(orders, orders_num, PENDING);
                break;
            case 4:
                export_orders("pending_orders.yaml", orders, orders_num, PENDING);
                break;
            case 5:
                import_orders("pending_orders.yaml", orders, &orders_num);
                break;
            case 6:
                modify_order(orders, orders_num, PLACE);
                break;
            case 7:
                display_orders(orders, orders_num, READY);
                break;
            case 8:
                modify_order(orders, orders_num, CLOSE);
                break;
            case 9:
                display_orders(orders, orders_num, CLOSED);
                break;
            case 10:
                export_orders("closed_orders.yaml", orders, orders_num, CLOSED);
                break;
            case 11:
                import_orders("closed_orders.yaml", orders, &orders_num);
                break;
        }

    } while (choice != 0);

    return 0;
}

int get_choice() {
    int option;

    char menu[] =
    " 0 - Exit\n"
    " 1 - Create an order\n"
    " 2 - View orders\n"
    " 3 - View pending orders\n"
    " 4 - Export pending orders to file\n"
    " 5 - Import pending orders from file\n"
    " 6 - Place a pending order\n"
    " 7 - View ready orders\n"
    " 8 - Close an order\n"
    " 9 - View closed orders\n"
    "10 - Export closed orders to file\n"
    "11 - Import closed orders from file\n";

    printf("%s\n", menu);
    printf("Enter option number: ");
    scanf("%d", &option);
    getchar();
    printf("\n");

    return option;
}

Order get_order() {
    Order order;

    order.status = PENDING;

    printf("Insert customer full-name: ");
    scanf("%[^\n]%*c", order.customer_name);

    printf("Insert creation date: ");
    scanf("%s", order.creation_date);
    getchar();

    printf("Insert date: ");
    scanf("%s", order.date);
    getchar();

    strcpy(order.execution_date, "");

    printf("Insert the number of small bottles: ");
    scanf("%d", &order.small_bottles);
    getchar();

    printf("Insert the number of big bottles: ");
    scanf("%d", &order.big_bottles);
    getchar();

    printf("\n");

    order.initial_price = 0;
    order.discount = 0;

    return order;
}

void display_orders(Order orders[], int orders_num, int status_idx) {
    int i=0;
    char initial_price_str[15], final_price_str[15], discount_str[8];
    Order *order;

    if (status_idx >= 0) {  // View specific order
        i = status_idx;
        orders_num = status_idx + 1;
    }

    for (; i<orders_num; i++) {
        order = &orders[i];

        sprintf(initial_price_str, "%.2f\u20AC", order->initial_price);
        sprintf(final_price_str, "%.2f\u20AC", order->initial_price * (1 - order->discount));
        sprintf(discount_str, "%3.0f%%", order->discount * 100);

        if (order->status == PENDING) {
            strcpy(initial_price_str, "N/A  ");
            strcpy(final_price_str, "N/A  ");
            strcpy(discount_str, "N/A");
        }
        else if (order->status == READY) {
            strcpy(final_price_str, "N/A  ");
            strcpy(discount_str, "N/A");
        }

        if (status_idx == ANY_STATUS || order->status == status_idx || status_idx >= 0)
            printf("%d %-21s %5d %5d %11s %11s %11s %11s%s %11s%s %4s %8s\n",
                i+1,
                order->customer_name,
                order->small_bottles,
                order->big_bottles,
                order->creation_date,
                order->date,
                order->execution_date,
                initial_price_str, (order->status != PENDING) ? "  " : "",
                final_price_str, (order->status == CLOSED) ? "  " : "",
                discount_str,
                order->status == PENDING ? "PENDING" : (order->status == READY ? "READY" : "CLOSED"));
    }
    printf("\n");
}

void export_orders(char filename[], Order orders[], int orders_num, int status) {
    int idx;
    Order *order;

    FILE *file_handler = fopen(filename, "w+");

    for (idx=0; idx<orders_num; idx++) {

        order = &orders[idx];

        if (order->status == status || status == ANY_STATUS) {
            fprintf(file_handler,
                "%d:\n"
                "  status: %d\n"
                "  customer_name: %s\n"
                "  creation_date: %s\n"
                "  date: %s\n"
                "  execution_date: %s\n"
                "  small_bottles: %d\n"
                "  big_bottles: %d\n"
                "  initial_price: %f\n"
                "  discount: %f\n",
                idx,
                order->status,
                order->customer_name,
                order->creation_date,
                order->date,
                order->execution_date,
                order->small_bottles,
                order->big_bottles,
                order->initial_price,
                order->discount);
        }
    }

    fclose(file_handler);

    printf("Orders Exported\n\n");
}

void import_orders(char filename[], Order orders[], int *orders_num) {
    char buffer[MAX_DATA_LINE_LEN];
    char key[20], value[20];
    int indent = 0;
    Order *order;

    FILE *file_handler = fopen(filename, "r");

    if (file_handler != 0) {
        while (fgets(buffer, MAX_DATA_LINE_LEN, file_handler) != NULL) {

            while (buffer[indent] == ' ') {
                indent++;
            }

            if (buffer[0] != '\n') {
                if (indent == 0) {
                    (*orders_num)++;
                }
                else if (indent == 2) {
                    order = &orders[*orders_num-1];

                    sscanf(buffer, "  %20[^:]: %[a-zA-Z0-9-/. ]", key, value);

                    if (strcmp(key, "status") == 0) {
                        sscanf(value, "%d", &order->status);
                    }
                    else if (strcmp(key, "customer_name") == 0) {
                        sscanf(value, FULL_NAME, &order->customer_name);
                    }
                    else if (strcmp(key, "creation_date") == 0) {
                        sscanf(value, DATE, &order->creation_date);
                    }
                    else if (strcmp(key, "date") == 0) {
                        sscanf(value, DATE, &order->date);
                    }
                    else if (strcmp(key, "execution_date") == 0) {
                        sscanf(value, DATE, &order->execution_date);
                    }
                    else if (strcmp(key, "small_bottles") == 0) {
                        sscanf(value, "%d", &order->small_bottles);
                    }
                    else if (strcmp(key, "big_bottles") == 0) {
                        sscanf(value, "%d", &order->big_bottles);
                    }
                    else if (strcmp(key, "initial_price") == 0) {
                        sscanf(value, "%f", &order->initial_price);
                    }
                    else if (strcmp(key, "discount") == 0) {
                        sscanf(value, "%f", &order->discount);
                    }
                }
            }

            indent = 0;
        }
        fclose(file_handler);

        printf("Orders Imported\n\n");
    }
    else {
        printf("%s not found!\n\n", filename);
    }
}

void modify_order(Order orders[], int orders_num, int action) {

    // First come first served

    // Pending:                     Ready:
    // 1. Calculate initial price   1. Calculate discount
    // 2. PENDING -> READY          2. READY -> CLOSED

    int order_idx = 0, target_status = (action == PLACE) ? PENDING : READY;
    Order *order;

    while(orders[order_idx].status != target_status && order_idx<orders_num) {
        order_idx++;
    }
    order = &orders[order_idx];

    if (order_idx == orders_num) {
        printf("No order found for this action\n");
    }
    else if (action == PLACE) {
        order->initial_price =
            order->small_bottles * small_bottle_cost +
            order->big_bottles * big_bottle_cost;
        order->status = READY;

        display_orders(orders, orders_num, order_idx);
    }
    else if (action == CLOSE) {
        if (order->initial_price > 600) {
            order->discount = 0.2;
        }
        else if (order->initial_price > 200 ||
                (order->small_bottles + order->big_bottles) > 3000)
        {
            order->discount = 0.08;
        }

        order->status = CLOSED;

        display_orders(orders, orders_num, order_idx);
    }

    printf("\n");
}

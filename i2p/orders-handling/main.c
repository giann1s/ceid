#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT 0

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

Order get_order(int *last_pending);

void display_orders(Order orders[], int last_closed, int last_ready, int last_pending, int status_idx);

void export_orders(char filename[], Order orders[], int last_closed, int last_ready, int last_pending, int status);
void import_orders(char filename[], Order orders[], int *last_closed, int *last_ready, int *last_pending);

int place_order(Order orders[], int last_ready, int last_pending);
int close_order(Order orders[], int last_closed, int last_ready);

int main() {
    int choice, last_closed = -1, last_ready = -1, last_pending = -1;
    Order orders[10];

    while ((choice = get_choice()) != EXIT) {

        switch (choice) {
            case 1:
                orders[last_pending + 1] = get_order(&last_pending);
                break;
            case 2:
                display_orders(orders, last_closed, last_ready, last_pending, ANY_STATUS);
                break;
            case 3:
                display_orders(orders, last_closed, last_ready, last_pending, PENDING);
                break;
            case 4:
                export_orders("pending_orders.yaml", orders, last_closed, last_ready, last_pending, PENDING);
                break;
            case 5:
                import_orders("pending_orders.yaml", orders, &last_closed, &last_ready, &last_pending);
                break;
            case 6:
                last_ready = place_order(orders, last_ready, last_pending);
                break;
            case 7:
                display_orders(orders, last_closed, last_ready, last_pending, READY);
                break;
            case 8:
                last_closed = close_order(orders, last_closed, last_ready);
                break;
            case 9:
                display_orders(orders, last_closed, last_ready, last_pending, CLOSED);
                break;
            case 10:
                export_orders("closed_orders.yaml", orders, last_closed, last_ready, last_pending, CLOSED);
                break;
            case 11:
                import_orders("closed_orders.yaml", orders, &last_closed, &last_ready, &last_pending);
                break;
        }
    };

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

Order get_order(int *last_pending) {
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

    (*last_pending)++;

    return order;
}

void display_orders(Order orders[], int last_closed, int last_ready, int last_pending, int status_idx) {
    int idx, start_end[2];
    char initial_price_str[15], final_price_str[15], discount_str[8];

    Order *order;

    switch (status_idx) {
        case ANY_STATUS:
            start_end[0] = 0;
            start_end[1] = last_pending;
            break;
        case CLOSED:
            start_end[0] = 0;
            start_end[1] = last_closed;
            break;
        case READY:
            start_end[0] = last_closed + 1;
            start_end[1] = last_ready;
            break;
        case PENDING:
            start_end[0] = last_ready + 1;
            start_end[1] = last_pending;
            break;
        default:
            start_end[0] = start_end[1] = status_idx;
            break;
    }

    if (status_idx >= 0 || start_end[1] - start_end[0] >= 0) {

        printf("   %-21s | %-10s | %-10s | %-10s | %-10s | %-10s | %-s | %-s | %-s | %-8s |\n",
        "Name", "Bottles (s)", "Bottles (b)", "Creation", "Date", "Execution","Price (initial)", "Price (final)", "Discount", "Status");

        for (idx = start_end[0]; idx <= start_end[1]; idx++) {
            order = &orders[idx];

            sprintf(initial_price_str, "%6.2f", order->initial_price);
            sprintf(final_price_str, "%6.2f", order->initial_price * (1 - order->discount));
            sprintf(discount_str, "%3.0f%%", order->discount * 100);

            if (order->status == PENDING) {
                strcpy(initial_price_str, "N/A");
                strcpy(final_price_str, "N/A");
                strcpy(discount_str, "N/A");
            }
            else if (order->status == READY) {
                strcpy(final_price_str, "N/A");
                strcpy(discount_str, "N/A");
            }

            if (status_idx == ANY_STATUS || order->status == status_idx || status_idx >= 0)
                printf("%2d %-21s | %11d | %11d | %-10s | %-10s | %-10s | %15s | %13s | %8s | %8s |\n",
                    idx+1,
                    order->customer_name,
                    order->small_bottles,
                    order->big_bottles,
                    order->creation_date,
                    order->date,
                    order->execution_date,
                    initial_price_str,
                    final_price_str,
                    discount_str,
                    order->status == PENDING ? "PENDING" : (order->status == READY ? "READY" : "CLOSED"));
        }
    }

    printf("\n");
}

void export_orders(char filename[], Order orders[], int last_closed, int last_ready, int last_pending, int status) {
    int idx, start_end[2];
    Order *order;

    FILE *file_handler = fopen(filename, "w+");

    switch (status) {
        case ANY_STATUS:
            start_end[0] = 0;
            start_end[1] = last_pending;
            break;
        case CLOSED:
            start_end[0] = 0;
            start_end[1] = last_closed;
            break;
        case READY:
            start_end[0] = last_closed + 1;
            start_end[1] = last_ready;
            break;
        case PENDING:
            start_end[0] = last_ready + 1;
            start_end[1] = last_pending;
            break;
    }

    for (idx=start_end[0]; idx<=start_end[1]; idx++) {

        order = &orders[idx];

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
            (idx + 1) - start_end[0],
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

    fclose(file_handler);

    printf("Orders Exported\n\n");
}

void import_orders(char filename[], Order orders[], int *last_closed, int *last_ready, int *last_pending) {
    char buffer[MAX_DATA_LINE_LEN];
    char key[20], value[20];
    int idx = -1, indent = 0;
    Order *order;

    FILE *file_handler = fopen(filename, "r");

    if (file_handler != 0) {

        (*last_closed) = (*last_ready) = (*last_pending) = -1;

        while (fgets(buffer, MAX_DATA_LINE_LEN, file_handler) != NULL) {

            // Check indentation
            while (buffer[indent] == ' ') {
                indent++;
            }

            if (buffer[0] != '\n') {

                if (indent == 0) {
                    idx++;
                }
                else if (indent == 2) {
                    order = &orders[idx];

                    sscanf(buffer, "  %20[^:]: %[a-zA-Z0-9-/. ]", key, value);

                    if (strcmp(key, "status") == 0) {
                        sscanf(value, "%d", &order->status);

                        switch (order->status) {
                            case CLOSED:
                                (*last_closed)++;
                                (*last_ready)++;
                                (*last_pending)++;
                                break;
                            case READY:
                                (*last_ready)++;
                                (*last_pending)++;
                                break;
                            case PENDING:
                                (*last_pending)++;
                                break;
                        }
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

int place_order(Order orders[], int last_ready, int last_pending) {

    Order *order;

    if (last_ready < last_pending) {
        order = &orders[++last_ready];

        order->initial_price =
            order->small_bottles * small_bottle_cost +
            order->big_bottles * big_bottle_cost;
        order->status = READY;
    }
    else {
        printf("No pending order found!\n\n");
    }

    return last_ready;
}

int close_order(Order orders[], int last_closed, int last_ready) {

    Order *order;

    if (last_closed < last_ready) {
        order = &orders[++last_closed];

        if (order->initial_price > 600) {
            order->discount = 0.2;
        }
        else if (order->initial_price > 200 ||
                (order->small_bottles + order->big_bottles) > 3000)
        {
            order->discount = 0.08;
        }

        order->status = CLOSED;
    }
    else {
        printf("No ready order found!\n\n");
    }

    return last_closed;
}

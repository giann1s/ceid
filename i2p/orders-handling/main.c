#include <stdio.h>
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
#define DATA_NUM 9  // number of Order struct members

typedef struct order {
    int status;

    char customer_name[22];

    char creation_date[11];
    char date[11];
    char execution_date[11];

    int small_bottles;
    int big_bottles;

    float initial_price;
    float discount_percentage;
} Order;

int get_choice();
Order get_order();
void display_orders(Order orders[], int num, int status);
void export_orders(char filename[], Order orders[], int orders_num, int status);
void import_orders(char filename[], Order orders[], int *orders_num, int status);
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
                export_orders("pending_orders.dat", orders, orders_num, PENDING);
                break;
            case 5:
                import_orders("pending_orders.dat", orders, &orders_num, PENDING);
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
                export_orders("closed_orders.dat", orders, orders_num, CLOSED);
                break;
            case 11:
                import_orders("closed_orders.dat", orders, &orders_num, CLOSED);
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
    order.discount_percentage = 0;

    return order;
}

void display_orders(Order orders[], int orders_num, int status_idx) {
    int i=0;
    char initial_price_str[15];
    char final_price_str[15];
    char discount_str[8];

    if (status_idx >= 0) {  // View specific order
        i = status_idx;
        orders_num = status_idx + 1;
    }

    for (; i<orders_num; i++) {
        sprintf(initial_price_str, "%.2f\u20AC", orders[i].initial_price);
        sprintf(final_price_str, "%.2f\u20AC", orders[i].initial_price * (1 - orders[i].discount_percentage));
        sprintf(discount_str, "%3.0f%%", orders[i].discount_percentage * 100);

        if (orders[i].status == PENDING) {
            strcpy(initial_price_str, "N/A  ");
            strcpy(final_price_str, "N/A  ");
            strcpy(discount_str, "N/A");
        }
        else if (orders[i].status == READY) {
            strcpy(final_price_str, "N/A  ");
            strcpy(discount_str, "N/A");
        }

        if (status_idx == ANY_STATUS || orders[i].status == status_idx || status_idx >= 0)
            printf("%d %-21s %5d %5d %11s %11s %11s %11s%s %11s%s %4s %8s\n",
                i+1,
                orders[i].customer_name,
                orders[i].small_bottles,
                orders[i].big_bottles,
                orders[i].creation_date,
                orders[i].date,
                orders[i].execution_date,
                initial_price_str, (orders[i].status != PENDING) ? "  " : "",
                final_price_str, (orders[i].status == CLOSED) ? "  " : "",
                discount_str,
                orders[i].status == PENDING ? "PENDING" : (orders[i].status == READY ? "READY" : "CLOSED"));
    }
    printf("\n");
}

void export_orders(char filename[], Order orders[], int orders_num, int status) {
    int idx;

    FILE *file_handler = fopen(filename, "w");

    for (idx=0; idx<orders_num; idx++) {
        if (orders[idx].status == status || status == ANY_STATUS) {
            fprintf(file_handler, "%d;%s;%s;%s;%s;%d;%d;%f;%f\n",
                orders[idx].status,
                orders[idx].customer_name,
                orders[idx].creation_date,
                orders[idx].date,
                orders[idx].execution_date,
                orders[idx].small_bottles,
                orders[idx].big_bottles,
                orders[idx].initial_price,
                orders[idx].discount_percentage);
        }
    }

    fclose(file_handler);

    printf("Orders Exported\n\n");
}

void import_orders(char filename[], Order orders[], int *orders_num, int status) {
    char buffer[MAX_DATA_LINE_LEN];

    FILE *file_handler = fopen(filename, "r");

    while (fgets(buffer, 150, file_handler) != NULL) {  // Read file

        sscanf(buffer, "%d;%[a-zA-Z ];%[0-9/];%[0-9/];%[0-9/];%d;%d;%f;%f",
            &orders[*orders_num].status,
            orders[*orders_num].customer_name,
            orders[*orders_num].creation_date,
            orders[*orders_num].date,
            &orders[*orders_num].execution_date,
            &orders[*orders_num].small_bottles,
            &orders[*orders_num].big_bottles,
            &orders[*orders_num].initial_price,
            &orders[*orders_num].discount_percentage);
        
        (*orders_num)++;
    }

    fclose(file_handler);

    printf("Orders Imported\n\n");
}

void modify_order(Order orders[], int orders_num, int action) {

    // First come first served

    // Pending:                     Ready:
    // 1. Calculate initial price   1. Calculate discount
    // 2. PENDING -> READY          2. READY -> CLOSED

    int order_idx = 0, target_status = (action == PLACE) ? PENDING : READY;

    while(orders[order_idx].status != target_status && order_idx<orders_num) {
        order_idx++;
    }

    if (order_idx == orders_num) {
        printf("No order found for this action\n");
    }
    else if (action == PLACE) {
        orders[order_idx].initial_price =
            orders[order_idx].small_bottles * small_bottle_cost +
            orders[order_idx].big_bottles * big_bottle_cost;
        orders[order_idx].status = READY;
        
        display_orders(orders, orders_num, order_idx);
    }
    else if (action == CLOSE) {
        if (orders[order_idx].initial_price > 600) {
            orders[order_idx].discount_percentage = 0.2;
        }
        else if (orders[order_idx].initial_price > 200 || (orders[order_idx].small_bottles + orders[order_idx].big_bottles) > 3000) {
            orders[order_idx].discount_percentage = 0.08;
        }

        orders[order_idx].status = CLOSED;

        display_orders(orders, orders_num, order_idx);
    }

    printf("\n");
}

#include <stdio.h>
#include <string.h>

#define small_bottle_cost 0.008
#define big_bottle_cost 0.02

// Positive integers are used
// for selecting specific order
// (status_idx in function display_orders)
#define PENDING -1
#define READY -2
#define CLOSED -3
#define ANY_STATUS -4

#define PLACE 1
#define CLOSE 2

typedef struct order {
    int status;

    char customer_name[20];

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
void export_orders();
void import_orders();
void modify_order(Order orders[], int orders_num, int action);

int main() {
    int orders_num=0, choice = -1;
    Order orders[10];

    /* =============== For testing ================= */
    orders[0].status=PENDING;
    strcpy(orders[0].customer_name, "Nikos Papadopoulos");
    strcpy(orders[0].creation_date, "15/12/2023");
    strcpy(orders[0].date, "18/12/2023");
    strcpy(orders[0].execution_date, "25/12/2023");
    orders[0].small_bottles=20;
    orders[0].big_bottles=4000;
    orders[0].initial_price = 302;
    orders[0].discount_percentage = 0.08;

    orders[1].status=READY;
    strcpy(orders[1].customer_name, "Panagiotis");
    strcpy(orders[1].creation_date, "15/12/2023");
    strcpy(orders[1].date, "18/12/2023");
    strcpy(orders[1].execution_date, "24/12/2023");
    orders[1].small_bottles=400;
    orders[1].big_bottles=600;
    orders[1].initial_price = 602;
    orders[1].discount_percentage = 0.2;

    orders[2].status=CLOSED;
    strcpy(orders[2].customer_name, "Dimitris Xantzis");
    strcpy(orders[2].creation_date, "15/12/2023");
    strcpy(orders[2].date, "18/12/2023");
    strcpy(orders[2].execution_date, "23/12/2023");
    orders[2].small_bottles=1000;
    orders[2].big_bottles=3000;
    orders[2].initial_price = 1002;
    orders[2].discount_percentage = 0.2;

    orders_num+=3;
    /* ========================================== */

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
                export_orders();
                break;
            case 5:
                import_orders();
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
                export_orders();
                break;
            case 11:
                import_orders();
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
    printf("\n");

    return option;
}

Order get_order() {
    Order order;

    order.status = PENDING;

    printf("Insert customer full-name: ");
    scanf("%s", &order.customer_name);

    printf("Insert creation date: ");
    scanf("%s", &order.creation_date);

    printf("Insert date: ");
    scanf("%s", &order.date);

    strcpy(order.execution_date, "");

    printf("Insert the number of small bottles: ");
    scanf("%d", &order.small_bottles);

    printf("Insert the number of big bottles: ");
    scanf("%d", &order.big_bottles);

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
        sprintf(discount_str, "%3.0f%%", orders[i].discount_percentage);

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
            printf("%d %-19s %5d %5d %11s %11s %11s %11s%s %11s%s %4s %8s\n",
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

void export_orders() {
    printf("Orders Exported\n\n");
}

void import_orders() {
    printf("Orders Imported\n\n");
}

void modify_order(Order orders[], int orders_num, int action) {
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

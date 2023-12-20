void export_orders(char filename[], Order orders[], int orders_num, int status) {
    int idx;
    Order *order;

    FILE *file_handler = fopen(filename, "w");

    for (idx=0; idx<orders_num; idx++) {

        order = &orders[idx];

        if (order->status == status || status == ANY_STATUS) {
            fprintf(file_handler, "%d;%s;%s;%s;%s;%d;%d;%f;%f\n",
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
    Order *order;

    FILE *file_handler = fopen(filename, "r");

    while (fgets(buffer, MAX_DATA_LINE_LEN, file_handler) != NULL) {

        order = &orders[*orders_num];

        sscanf(buffer, "%d;%[a-zA-Z ];%[0-9/];%[0-9/];%[0-9/];%d;%d;%f;%f",
            &order->status,
            order->customer_name,
            order->creation_date,
            order->date,
            &order->execution_date,
            &order->small_bottles,
            &order->big_bottles,
            &order->initial_price,
            &order->discount);

        (*orders_num)++;
    }

    fclose(file_handler);

    printf("Orders Imported\n\n");
}

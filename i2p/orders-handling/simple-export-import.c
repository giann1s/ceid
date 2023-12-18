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
                orders[idx].discount);
        }
    }

    fclose(file_handler);

    printf("Orders Exported\n\n");
}

void import_orders(char filename[], Order orders[], int *orders_num, int status) {
    char buffer[MAX_DATA_LINE_LEN];

    FILE *file_handler = fopen(filename, "r");

    while (fgets(buffer, MAX_DATA_LINE_LEN, file_handler) != NULL) {

        sscanf(buffer, "%d;%[a-zA-Z ];%[0-9/];%[0-9/];%[0-9/];%d;%d;%f;%f",
            &orders[*orders_num].status,
            orders[*orders_num].customer_name,
            orders[*orders_num].creation_date,
            orders[*orders_num].date,
            &orders[*orders_num].execution_date,
            &orders[*orders_num].small_bottles,
            &orders[*orders_num].big_bottles,
            &orders[*orders_num].initial_price,
            &orders[*orders_num].discount);
        
        (*orders_num)++;
    }

    fclose(file_handler);

    printf("Orders Imported\n\n");
}

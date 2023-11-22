/*
Για όσο η επιλογη δεν ειναι 0
    Τύπωσε το μενού και πάρε την επιλογή από τον χρήστη
    Αν ειναι 1 πάρε τις λέξεις από τον χρήστη
    Αν είναι 2 τυπωσε τις λέξεις αν ο χρήστης έχει δώσει κάποιες
    Αν είναι 3 δώσε τα στατιστικά
    Αν είναι 4 δώσε τα στατιστικά για συγκεκριμένο χαρακτήρα που θα δώσει ο χρήστης
*/

#define MAX_LENGTH 30

#include <stdio.h>
#include <string.h>

int get_user_option(char menu[],int options);
int get_words(char words[][MAX_LENGTH], int max_words);
void print_words(char words[][MAX_LENGTH], int max_words);
void display_stats(char words[][MAX_LENGTH], int max_words);
void display_char_stats(char words[][MAX_LENGTH], int words_num);

int main() {
    int i, option = -1, options = 4, max_words = 30;

    int words_num = 0;
    char words[30][MAX_LENGTH];

    for (i = 0; i < max_words; i++)
        words[i][0]='\0';

    char menu[] =
    "0. Exit\n"
    "1. Insert words\n"
    "2. Print words\n"
    "3. View statistics\n"
    "4. View statistics for specific character\n";

    do {
        option = get_user_option(menu, options);

        switch (option) {
            case 0:
                break;
            case 1:
                words_num = get_words(words, max_words);
                break;
            case 2:
                print_words(words, max_words);
                break;
            case 3:
                display_stats(words, words_num);
                break;
            case 4:
                display_char_stats(words, words_num);
                break;
        }
        printf("\n");

    } while (option != 0);

    return 0;
}

int get_user_option(char menu[], int options) {
    int option = -1;

    do {
        printf("%s", menu);
        printf("Type option number: ");
        scanf("%d", &option);
        printf("\n");
    }
    while (option < 0 || option > options);

    return option;
}

int get_words(char words[][MAX_LENGTH], int max_words) {
    int i, words_num;

    printf("How many words do you want to insert?: ");
    scanf("%d", &words_num);

    for (i = 0; i < max_words; i++)
        words[i][0]='\0';
    
    for (i = 0; i < words_num && i < max_words; i++) {
        printf("Insert word %d: ", i + 1);
        scanf("%s", words[i]);
    }

    return words_num;
}

void print_words(char words[][MAX_LENGTH], int max_words) {
    int i;

    for (i = 0; i < max_words; i++) {
        if (words[i][0] != '\0') {
            printf("%s", words[i]);
            printf("\n");
        }
    }
}

void display_stats(char words[][MAX_LENGTH], int words_num) {
    int i, len, average_len = 0, max_len = 0, min_len = MAX_LENGTH;

    if (words_num != 0) {
        for (i = 0; i < words_num; i++) {
            len = strlen(words[i]);
            average_len += len;

            if (len > max_len)
                max_len = len;
            if (len < min_len)
                min_len = len;
        }

        printf("Max length: %d\nMin length: %d\nAverage length: %.2f\n", max_len, min_len, (float) average_len / words_num);
    }
    else
        printf("No words available\n");
}

void display_char_stats(char words[][MAX_LENGTH], int words_num) {
    char character;
    int i, j, len, occurrences = 0, current_occ = 0, max_occ = 0, min_occ = MAX_LENGTH, max_idx = 0, min_idx = 0;

    if (words_num != 0) {
        printf("Insert a character: ");
        scanf(" %c", &character);

        for (i = 0; i < words_num; i++) {
            len = strlen(words[i]);

            for (j = 0; j < len; j++) {
                if (words[i][j] == character) {
                    current_occ++;
                    occurrences++;
                }
            }

            if (current_occ > max_occ) {
                max_occ = current_occ;
                max_idx = i;
            }
            if (current_occ < min_occ) {
                min_occ = current_occ;
                min_idx = i;
            }

            current_occ = 0;
        }

        printf("Occurrences: %d\nAverage occurrences/word: %.2f\nMax occurrences: %d (first in %s)\nMin occurrences: %d (first in %s)\n",
            occurrences, (float) occurrences / words_num, max_occ, words[max_idx], min_occ, words[min_idx]);
    }
    else
        printf("No words available\n");
}

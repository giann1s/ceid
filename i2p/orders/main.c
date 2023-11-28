/*
Πάρε τον αριθμό των μικρών και μεγάλων μπουκαλιών από τον χρήστη
Υπολόγησε την συνολική τιμή πολλαπλασιάζοντας το κάθε είδος μπουκαλιού με την αντίστοιχη τιμή
Αν η τιμή υπερβαίνει τα 600€ μείωσε την τιμή κατά 20%
Αλλιώς αν η τιμή υπερβαίνει τα 200€ ή τα μπουκάλια είναι πάνω από 3000 μέιωσε την κατά 8%
Εμφάνησε την τελική τιμή
*/

#include <stdio.h>

#define sBottle_price 0.008
#define bBottle_price 0.02

int main() {
    int sBottles, bBottles;
    float price;

    printf("Insert the number of small bottles: ");
    scanf("%d", &sBottles);

    printf("Insert the number of big bottles: ");
    scanf("%d", &bBottles);

    price = (sBottles * sBottle_price) + (bBottles * bBottle_price);

    if (price > 600) {
        price *= 0.8;
    }
    else if (price > 200 || (sBottles + bBottles) > 3000) {
        price *= 0.92;
    }

    printf("The total price is %.2f\u20AC\n", price);

    return 0;
}
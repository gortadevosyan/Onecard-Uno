#include <stdio.h>
#include "structures.h"
#include "cardfunctions.h"

void swap(int ind1, int ind2, pile *decks)
{
    card a = decks->cards[ind2];
    decks->cards[ind2] = decks->cards[ind1];
    decks->cards[ind1] = a;
}
void shuffle_deck(pile *decks)
{
    // I will generate a random number R in the range 1:N where N is the leght of the array
    //  then I will swap the R-th element of the deck with the latest, N-- and repeat the process
    //  so my function will also need the length of the shuffling deck
    int n = decks->num; // alternate it whenever needed;
    while (n > 0)
    {
        int c = 0;
        srand((unsigned int)time(NULL));
        c = rand() % n + 1;
        swap(c, n, decks);
        n--;
    }
}
int cardmin(pile *decks, int ind)
{
    card min = decks->cards[ind];
    int retind = ind;
    for (int i = ind + 1; i <= decks->num; i++)
    {
        if (decks->cards[i].suit < min.suit)
        {
            min = decks->cards[i];
            retind = i;
        }
        else if (decks->cards[i].suit == min.suit)
        {
            if (decks->cards[i].rank < min.rank)
            {
                min = decks->cards[i];
                retind = i;
            }
        }
    }
    return retind;
}
void sort_pile(pile *decks)
{
    for (int i = 1; i <= decks->num; i++)
    {
        int ind = cardmin(decks, i);
        swap(i, ind, decks);
    }
}

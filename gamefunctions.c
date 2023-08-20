#include "gamefunctions.h"
#include "printfunctions.h"
#include <stdio.h>
#include <stdlib.h>
void deck_initialize(pile *pilename, int numofdecks)
{
    pilename->cards = realloc(pilename->cards, (long unsigned int)(52 * numofdecks + 2) * sizeof(card));
    if (pilename->cards == NULL)
    {
        printf("ERROR OCCURED| deck_initialize line 7");
        return;
    }
    for (int i = 0; i < numofdecks; i++)
    {
        for (int j = 1; j <= 4; j++)
        {
            for (int g = 2; g <= 14; g++)
            {
                pilename->cards[i * 52 + (j - 1) * 13 + (g - 1)].suit = j;
                pilename->cards[i * 52 + (j - 1) * 13 + (g - 1)].rank = g;
                pilename->num++;
            }
        }
    }
    // shuffle_deck(pilename);//change the name to shuffle_pile
}

// a function that moves a card from pile1 ind to pile2 end
void movecard(pile *pile1, pile *pile2, int ind)
{
    int len1 = pile1->num;
    int len2 = pile2->num;
    card temp;
    temp.rank = 0;
    temp.suit = 0;
    if (ind > 0 && ind <= pile1->num)
        temp = pile1->cards[ind];
    pile1->num--;
    for (int i = ind; i < len1; i++)
    {
        pile1->cards[i] = pile1->cards[i + 1];
    }
    card *p = NULL;
    if (len2 + 2 > 0)
    {
        p = realloc(pile2->cards, sizeof(card) + (long long unsigned int)(len2 + 2) * sizeof(card));
        if (p == NULL)
        {
            free(pile2->cards);
            printf("ERROR OCCURRED| movecard line 30\n");
            return;
        }
        // else if((long long unsigned int)p!=(long long unsigned int)(pile2->cards))
        //    free(pile2->cards);
        pile2->cards = p;
    }
    p = NULL;
    if (len1 - 1 > 0)
    {
        p = realloc(pile1->cards, sizeof(card) + (long long unsigned int)(len1) * sizeof(card));
        if (p == NULL)
        {
            free(pile1->cards);
            printf("ERROR OCCURRED| movecard line 36\n");
            return;
        }
        // else if( (long long unsigned int)p!=(long long unsigned int)(pile1->cards)){
        //     free(pile1->cards);
        // }
        pile1->cards = p;
    }
    p = NULL;
    free(p);
    pile2->cards[len2 + 1] = temp;
    pile2->num++;
}

// gives cards to players

void cards2players(pile *pile1, pile *players, int n, int c)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            movecard(pile1, &players[i], 1);
        }
    }
}

// determines the order
int determineorder(pile *deck, pile *curcard, int n, FILE *fp)
{
    int minr = 15, minind = 1, mins = 4;
    for (int i = 1; i <= n; i++)
    {
        printf("player %d: ", i);
        fprintf(fp, "player %d: ", i);
        print_card(&(deck->cards[1]), stdout);
        printf("\n");
        print_card(&(deck->cards[1]), fp);
        fprintf(fp, "\n");
        if (deck->cards[1].rank < minr)
        {
            minr = deck->cards[1].rank;
            minind = i;
        }
        else if (deck->cards[1].rank == minr)
        { // if there are two cards with the same rank the suit decides the smallest
            if (deck->cards[1].suit < mins)
            {
                mins = deck->cards[1].suit;
                minr = deck->cards[1].rank;
                minind = i;
            }
        }
        // add_card(players[i], deck.cards[i].suit, deck.cards[i].rank);
        movecard(deck, curcard, 1);
    }
    return minind;
}
void clearscreen(){
    #ifdef _WIN32
    //printf("You have Windows Operating System");
    system("cls"); 
    #endif
    #ifdef __APPLE__
    clrscr();
    #endif
    #ifdef __linux__
    //system(“clear”); didn't pass the build check
    printf("\033[2J\033[H"); 
    #endif 
}
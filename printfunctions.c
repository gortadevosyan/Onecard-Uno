#include "printfunctions.h"

void print_player(pile *name, FILE *fp)
{
    for (int i = 1; i <= name->num; i++)
    {
        print_card(&(name->cards[i]), fp);
        if (i < name->num)
            fprintf(fp, ", ");
    }
    fprintf(fp, "\n");
}
void print_card(card *cardname, FILE *fp)
{
    print_suit(cardname->suit, fp);
    print_rank(cardname->rank, fp);
}
void print_suit(int suit, FILE *fp)
{
    switch (suit)
    {
    case 1:
        fprintf(fp, "SPADES ");
        break;
    case 2:
        fprintf(fp, "HEARTS ");
        break;
    case 3:
        fprintf(fp, "DIAMONDS ");
        break;
    case 4:
        fprintf(fp, "CLUBS ");
        break;
    }
}
void print_rank(int rank, FILE *fp)
{
    if (rank > 10)
    {
        switch (rank)
        {
        case 11:
            fprintf(fp, "J ");
            break;
        case 12:
            fprintf(fp, "Q ");
            break;
        case 13:
            fprintf(fp, "K ");
            break;
        case 14:
            fprintf(fp, "A ");
            break;
        }
    }
    else fprintf(fp, "%d ", rank);
}
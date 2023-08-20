#include "onecard.h"
int run_round(int j, int n, int r, int d, int c, int m, int firstplayer, pile *deck, pile *curcard,
              FILE *fp, int *penalty, pile *players)
{
    int curplayerind = firstplayer;
    int curcardind = 0;
    card lcard = deck->cards[1];
    int isfinished = 0;
    int cardcollect = 0, dir = 1; // direction is changes to -1 after Queen was played,
                                  // carcollect+2|3 if 2 or 3 were played
    movecard(deck, curcard, 1);
    printf("the first card is: ");
    fprintf(fp, "the first card is: ");
    print_card(&lcard, stdout);
    print_card(&lcard, fp);
    printf("\n");
    fprintf(fp, "\n");
    while (1)
    {
        curplayerind = (curplayerind + n) % n; // calculates the index of the current player
        if (curplayerind == 0)
            curplayerind = n;
        if (isfinished)
        { // checks if the round should end or not
            penalty[curplayerind] -= cardcollect;
            firstplayer = curplayerind - dir;
            break;
        }
        // clear screen
        printf("last card was: ");
        fprintf(fp, "last card was: ");
        print_card(&lcard, stdout);
        print_card(&lcard, fp);
        printf("\nplayer %d cards: ", curplayerind);
        fprintf(fp, "\nplayer %d cards: ", curplayerind);
        print_player(&players[curplayerind], stdout);
        print_player(&players[curplayerind], fp);
        printf(
            "please input the index of the card you want to play(0 to take a card from the "
            "stockpile(%d card to take)): \n",
            cardcollect);
        fprintf(fp,
                "please input the index of the card you want to play(0 to take a card from the "
                "stockpile(%d card to take)): \n",
                cardcollect);
        if (m == 1)
        {
            for (int i = 1; i <= players[curplayerind].num; i++)
            {
                if (players[curplayerind].cards[i].suit == lcard.suit ||
                    players[curplayerind].cards[i].rank == lcard.rank)
                {
                    printf("player %d playes card in the index %d\n", curplayerind, i);
                    fprintf(fp, "player %d playes card in the index %d\n", curplayerind, i);
                    curcardind = i;
                    break;
                }
                curcardind = 0;
            }
        }
        else
            scanf("%d", &curcardind);
        while (curcardind > players[curplayerind].num)
        {
            printf("please enter a valid index");
            fprintf(fp, "user entered invalid number, trying again...");
            scanf("%d", &curcardind);
        }
        if (curcardind == 0)
        {
            printf("collecting cards...\n");
            fprintf(fp, "collecting cards...\n");
            if (deck->num < cardcollect)
            {
                printf("stock pile is exhausted, shuflling the discard pile...\n");
                fprintf(fp, "stock pile is exhausted, shuflling the discard pile...\n");
                for (int i = 0; i < curcard->num - 1; i++)
                    movecard(curcard, deck, 1);
                shuffle_deck(deck);
            }
            if (cardcollect == 0)
                movecard(deck, &players[curplayerind], 1);
            else
            {
                for (int i = 1; i <= cardcollect; i++)
                    movecard(deck, &players[curplayerind], 1);
            }
            cardcollect = 0;
            sort_pile(&players[curplayerind]);
            printf("player %d cards are: ", curplayerind);
            fprintf(fp, "player %d cards are: ", curplayerind);
            print_player(&players[curplayerind], stdout);
            print_player(&players[curplayerind], fp);
            curplayerind += dir;
        }
        else if (players[curplayerind].cards[curcardind].rank == lcard.rank ||
                 players[curplayerind].cards[curcardind].suit == lcard.suit)
        {
            lcard.rank = players[curplayerind].cards[curcardind].rank;
            lcard.suit = players[curplayerind].cards[curcardind].suit;
            movecard(&players[curplayerind], curcard, curcardind);
            if (players[curplayerind].num == 0)
            {
                printf("player %d won round %d\n", curplayerind, j);
                fprintf(fp, "player %d won round %d\n", curplayerind, j);
                isfinished = 1;
                break; // the next player should take all the penalty cards
            }
            if (lcard.rank == 2)
                cardcollect += 2;
            else if (lcard.rank == 3)
                cardcollect += 3;
            else if (lcard.rank == 12)
                dir *= -1;
            else if (lcard.rank == 11)
                curplayerind += dir;
            curplayerind += dir;
        }
        else
        {
            printf("Please play a valid card");
            fprintf(fp, "Please play a valid card");
            printf(
                "please input the index of the card you want to play(0 to take a card from the "
                "stockpile(%d card to take)): \n",
                cardcollect);
            fprintf(fp,
                    "please input the index of the card you want to play(0 to take a card from "
                    "the stockpile(%d card to take)): \n",
                    cardcollect);
            scanf("%d", &curcardind);
        }
        if (m == 0)
            clearscreen();
    }
    for (int i = 1; i <= n; i++)
    {
        penalty[i] -= players[i].num; // calculating the penalty
        for (int g = 0; g <= players[i].num; g++)
        {
            players[i].cards[g].suit = 0;
            players[i].cards[g].rank = 0;
        }
        players[i].num = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        printf("player %d penalty score is: %d\n", i, penalty[i]);
        fprintf(fp, "player %d penalty score is: %d\n", i, penalty[i]);
    }
    if (j == r)
    {                    // identifying and printing the winners
        int min = -8500; // randomly small number
        for (int i = 1; i <= n; i++)
        {
            if (penalty[i] > min)
                min = penalty[i];
        }
        for (int i = 1; i <= n; i++)
        {
            if (penalty[i] == min)
            {
                printf("player %d won the game with penalty score %d\n", i, min);
                fprintf(fp, "player %d won the game with penalty score %d\n", i, min);
            }
        }
        printf("closing the program...");
        fprintf(fp, "closing the program...");
        return 1;
    }
    deck->num = 0;
    deck_initialize(deck, d);
    printf("#deck initialized\n");
    printf("#shuffling the deck...\n");
    printf("#shuffled deck\n");
    shuffle_deck(deck);
    print_player(deck, stdout);
    print_player(deck, fp);
    printf("\n");
    fprintf(fp, "\n");
    for (int i = 0; i < curcard->num; i++)
    {
        curcard->cards[i].rank = 0;
        curcard->cards[i].suit = 0;
    }
    curcard->num = 0;
    curcard->cards = realloc(curcard->cards, (long unsigned int)(n + 2) * sizeof(card));
    if (curcard->cards == NULL)
        printf("ERROR OCCURED| onecard line 192");
    cards2players(deck, players, n, c);
    for (int i = 1; i <= n; i++)
    {
        sort_pile(&players[i]);
        if (m == 1)
        {
            printf("player %d cards: ", i);
            print_player(&players[i], stdout);
        }
        fprintf(fp, "player %d cards: ", i);
        print_player(&players[i], fp);
    }
    return 0;
}

void onecard(int n, int r, int d, int c, int m, char *filename)
{
    FILE *fp = fopen(filename, "w");
    pile *players = NULL;
    pile curcard;
    curcard.num = 0;
    pile deck;
    deck.num = 0;
    players = calloc((long unsigned int)(c + 2), sizeof(pile));
    if (players == NULL)
    {
        free(players);
        fclose(fp);
        printf("ERROR OCCURRED| onecard line 6");
        return;
    }
    for (int i = 1; i <= n + 2; i++)
    {
        players[i].num = 0;
        players[i].cards = calloc((long unsigned int)(c + 2), sizeof(pile));
        if (players[i].cards == NULL)
        {
            printf("ERROR OCCURED| onecard line 12");
            free(players);
            free(players[i].cards);
            fclose(fp);
            return;
        }
    }
    deck.cards = calloc((long unsigned int)(52 * d + 2), sizeof(card));
    if (deck.cards == NULL)
    {
        printf("ERROR OCCURED| onecard line 13");
        free(players);
        free(deck.cards);
        fclose(fp);
        return;
    }
    curcard.cards = calloc((long unsigned int)(n + 2),
                           sizeof(card)); // is the pile of cards currently on the table
    if (curcard.cards == NULL)
    {
        printf("ERROR OCCURED| onecard line 19");
        free(curcard.cards);
        free(players);
        free(deck.cards);
        fclose(fp);
        return;
    }
    int *penalty = calloc((long unsigned int)(n + 2), sizeof(int));
    if (penalty == NULL)
    {
        free(penalty);
        free(curcard.cards);
        free(players);
        free(deck.cards);
        fclose(fp);
        printf("ERROR OCURRED| onecard line 51");
        return;
    } // calculates the penalty of each player
    deck_initialize(&deck, d);
    shuffle_deck(&deck);
    if (m == 1)
    { // print only in demo mode
        printf("#the deck has %d cards\n", deck.num);
        printf("#shuffled deck: \n");
        print_player(&deck, stdout);
    }
    fprintf(fp, "#the deck has %d cards\n", deck.num);
    fprintf(fp, "#deck initialized:\n");
    fprintf(fp, "#shuffled deck: \n");
    print_player(&deck, fp);
    printf("#Order:\n");
    fprintf(fp, "#Order: \n");
    int firstplayer = determineorder(&deck, &curcard, n, fp);
    printf("player %d is the first to go: \n", firstplayer);
    fprintf(fp, "player %d is the first to go: \n", firstplayer);
    cards2players(&deck, players, n, c);
    for (int i = 1; i <= n; i++)
        sort_pile(&players[i]);
    if (m == 1)
    {
        printf("#game initalized\n");
        for (int i = 1; i <= n; i++)
        {
            printf("#player %d cards: ", i);
            print_player(&players[i], stdout);
        }
        printf("\n");
        printf("#deck before the game:\n");
        print_player(&deck, stdout);
    }
    fprintf(fp, "#game initalized\n");
    for (int i = 1; i <= n; i++)
    {
        fprintf(fp, "#player %d cards: ", i);
        print_player(&players[i], fp);
    }
    fprintf(fp, "\n");
    fprintf(fp, "#deck before the game:\n");
    print_player(&deck, fp);
    for (int j = 1; j <= r; j++)
    {
        if (run_round(j, n, r, d, c, m, firstplayer, &deck, &curcard, fp, penalty, players))
        {
            break;
        }
    }
    for (int i = 0; i <= n + 2; i++)
        free(players[i].cards);
    free(players);
    free(penalty);
    free(curcard.cards);
    free(deck.cards);
    fclose(fp);
}
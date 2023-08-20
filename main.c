#include <stdio.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <getopt.h>
#include "structures.h"
#include "cardfunctions.h"
#include "printfunctions.h"
#include "gamefunctions.h"
#include "onecard.h"
#include <assert.h>
#define SPADES 1
#define HEARTS 2
#define DIAMONDS 3
#define CLUBS 4
#define ACE 14
#define KING 13
#define QUEEN 12
#define JACK 11
#include <stdio.h>
#include "structures.h"
#include "cardfunctions.h"
#include "onecard.h"

int main(int argc, char *argv[])
{
    int n = 4, r = 3, d = 2, c = 5; // default values n rounds decks c
    char filename[200]="onecard.log"; //the log file will be written in the "filename".log file
    int m = 0; // 0 if it's the regular multiplayer, 1 if it's demo
    int option_index = 0, opt = 0;
    struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"log", optional_argument, NULL, 'l'},
        {"player-number=", required_argument, NULL, 'n'},
        {"initial-cards=", required_argument, NULL, 'c'},
        {"decks=", required_argument, NULL, 'd'},
        {"rounds=", required_argument, NULL, 'r'},
        {"auto", no_argument, NULL, 'a'},
        {NULL, 0, NULL, 0}};
    while ((opt = getopt_long(argc, argv, "hl:n:c:d:r:a", long_options, &option_index)) != -1)
    {
        switch (opt)
        {
        case 'h':
            printf("-h|--help print this help message\n"
                   "--log filename write the logs in filename (default: onecard.log)\n"
                   "-n n|--player-number=n n players, n must be larger than 2 (default: 4)\n"
                   "-c c|--initial-cards=c deal c cards per player, c must be at least 2 (default: 5)\n"
                   "-d d|--decks=d use d decks 52 cards each, d must be at least 2 (default: 2)\n"
                   "-r r|--rounds=r play r rounds, r must be at least 1 (default: 1)\n"
                   "-a|--auto run in demo mode\n");
            break;
        case 'l':
            strcpy(filename, optarg);
            printf("write the logs in: %s (default: onecard.log)\n", optarg);
            break;
        case 'n':
            if (optarg != NULL)
                n = atoi(optarg);
            printf("number of players: %d\n", n);
            break;
        case 'c':
            c = atoi(optarg);
            printf("number of the cards: %d\n", c);
            break;
        case 'd':
            d = atoi(optarg);
            printf("the number of the decks: %d\n", d);
            break;
        case 'r':
            r = atoi(optarg);
            printf("the number of the rounds: %d\n", r);
            break;
        case 'a':
            m = 1;
            printf("run in demo mode\n");
            break;
        default:
            printf("Invalid.\n");
        }
    }
    onecard(n, r, d, c, m, filename);
}

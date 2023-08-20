#ifndef PRINTFUNCTIONS
#define PRINTFUNCTIONS
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
void print_player(pile *playername, FILE *fp);
void print_card(card *cardname, FILE *fp); //int suit, int rank);
void print_suit(int suit, FILE *fp);
void print_rank(int rank, FILE *fp);
#endif
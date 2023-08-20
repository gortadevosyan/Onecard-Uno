#ifndef CARDFUNCTIONS
#define CARDFUNCTIONS
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
void shuffle_deck(pile *decks);
void swap(int c, int N, pile *decks);
void sort_pile(pile *decks);
int cardmin(pile *decks, int ind);
#endif
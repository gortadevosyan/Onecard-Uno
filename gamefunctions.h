#ifndef GAMEFUNCTIONS
#define GAMEFUNCTIONS
#include "structures.h"
#include "cardfunctions.h"
void deck_initialize(pile *pilename, int number_of_decks);
void movecard(pile *pile1, pile *pile2, int ind);
int determineorder(pile *pile1, pile *pile2, int number_of_players, FILE *fp);
void cards2players(pile *pile1, pile *pile2, int number_of_players, int number_of_cards);
void clearscreen();
#endif
#ifndef ONECARD_H
#define ONECARD_H
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
void onecard(int n, int r, int d, int c, int m, char *filename);
#endif
#ifndef STRUCTURES
#define STRUCTURES
typedef struct _card{
    int rank;
    int suit;
    //char s;//keep the suit in string type also
} card;

typedef struct _pile{
    card *cards; 
    int num;
} pile;
#endif
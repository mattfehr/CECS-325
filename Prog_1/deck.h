// Matthew Fehr
// CECS 325-02
// Prog 1 – One Card WAR
// 2/15/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#ifndef xDECK_H
#define xDECK_H
#include <vector>
#include "card.h"
using namespace std;

class Deck
{
    private:
        vector<Card> storage;
    public:
        Deck(); // constructor which creates a deck of 52 cards
        Card deal(); // deal a card
        void display(); // show all the cards in the deck
        void shuffle(); // shuffle the cards in the deck
};

#endif
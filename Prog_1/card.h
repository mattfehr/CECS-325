// Matthew Fehr
// CECS 325-02
// Prog 1 – One Card WAR
// 2/15/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#ifndef xCARD_H
#define xCARD_H
using namespace std;

class Card
{
    private:
        char rank;
        char suit;
    public:
        Card(char, char); // constructor to create a card, setting the suit and rank
        void display(); // display the card example: AC, 10S, KD
        int compare(Card); // return 1 for win, 0 for tie, -1 for lose   
};

#endif

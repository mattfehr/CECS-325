// Matthew Fehr
// CECS 325-02
// Prog 1 – One Card WAR
// 2/15/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include "deck.h"
#include "card.h"
#include <cstdlib>
#include <ctime>
using namespace std;

Deck::Deck()
{
    char ranks[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    char suits[4] = {'C', 'S', 'D', 'H'};
    for (int i=0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            storage.push_back(Card(ranks[j], suits[i]));
        }
    }
}
Card Deck::deal()
{
    Card card = storage.front();
    storage.erase(storage.begin());
    return card;
}

void Deck::display()
{
    storage[0].display();
    for (int i = 1; i < 13; i++) {
        cout << ", ";
        storage[i].display();
    }
    cout << '\n';
    storage[13].display();
    for (int i = 14; i < 26; i++) {
        cout << ", ";
        storage[i].display();
    }
    cout << '\n';
    storage[26].display();
    for (int i = 27; i < 39; i++) {
        cout << ", ";
        storage[i].display();
    }
    cout << '\n';
    storage[39].display();
    for (int i = 40; i < 52; i++) {
        cout << ", ";
        storage[i].display();
    }
    cout << '\n';
}

void Deck::shuffle()
{
    // srand(time(0));
    // for (int i = 0; i < 52; i++) {
    //     int swap = rand() % 52;
    //     Card temp = storage[i];
    //     storage[i] = storage[swap];
    //     storage[swap] = temp; 
    // }

    srand(time(0));
    for (int i = 0; i < 100000; i++) {
        int i1 = rand() % 52;
        int i2 = rand() % 52;
        Card temp = storage[i1];
        storage[i1] = storage[i2];
        storage[i2] = temp;
    }
}


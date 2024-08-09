// Matthew Fehr
// CECS 325-02
// Prog 1 – One Card WAR
// 2/15/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include "card.h"
#include <map>
using namespace std;

Card::Card(char r, char s)
{
    rank = r;
    suit = s;
}

void Card::display()
{
    if (rank == 'T') {
        cout << "10" << suit; 
    } else {
        cout << rank << suit;
    }
}

int Card::compare(Card other)
{
    map<char, int> val_map;
    val_map['A'] = 1;
    val_map['2'] = 2;
    val_map['3'] = 3;
    val_map['4'] = 4;
    val_map['5'] = 5;
    val_map['6'] = 6;
    val_map['7'] = 7;
    val_map['8'] = 8;
    val_map['9'] = 9;
    val_map['T'] = 10;
    val_map['J'] = 11;
    val_map['Q'] = 12;
    val_map['K'] = 13;

    if (val_map[rank] > val_map[other.rank]) {
        return 1;
    } else if (val_map[rank] == val_map[other.rank]) {
        return 0;
    } else {
        return -1;
    }
}


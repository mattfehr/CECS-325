// Matthew Fehr
// CECS 325-02
// Prog 1 – One Card WAR
// 2/15/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include "card.h"
#include "deck.h"
#include <string>
using namespace std;

int main()
{
    //create players and trackers
    string player1;
    string player2;
    cout << "Enter the name of the first player: ";
    getline(cin, player1);
    //cin >> player1;
    cout << "Enter the name of the second player: ";
    //cin >> player2;
    getline(cin,player2);
    int p1Wins = 0;
    int p2Wins = 0;
    int p1Losses = 0;
    int p2Losses = 0;
    int ties = 0;

    //create deck and shuffle
    Deck deck = Deck();
    cout << "\n Original Deck \n";
    deck.display(); 
    deck.shuffle();
    cout << " \n Shuffled Deck \n";
    deck.display();
    cout << '\n';

    //play games
    for (int game=1;game<27;game++) {
        //get games and deal cards
        cout << "Game " << game << '\n';
        cout << "--------\n";
        cout << "        " << player1 << "=>";
        Card card1 = deck.deal();
        card1.display();
        cout << '\n';
        cout << "        " << player2 << "=>";
        Card card2 = deck.deal();
        card2.display();
        cout << '\n';

        //compare cards and select winner
        int win = card1.compare(card2);
        if (win == 1) {
            cout << player1 << "=> Winner\n\n";
            p1Wins++;
            p2Losses++;
        } else if (win == -1) {
            cout << player2 << "=> Winner \n\n";
            p2Wins++;
            p1Losses++;
        } else {
            cout << "Tie game\n\n";
            ties++;
        }
    }

    //display final stats
    cout << "------Final Stats------\n";
    cout << "       " << player1 << " vs. " << player2 << '\n';
    cout << "Wins   " << p1Wins << "          " << p2Wins << '\n';
    cout << "Losses " << p1Losses << "          " << p2Losses << '\n';
    cout << "Ties   " << ties << "           " << ties << endl;

    return 0;
}
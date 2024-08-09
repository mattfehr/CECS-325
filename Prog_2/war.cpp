// Matthew Fehr
// CECS 325-02
// Prog 2 – More WAR
// 2/27/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;

// headers
class Card
{
    private:
        char rank;
        char suit;
    public:
        Card(); // default constructor – needed tor array in Deck class
        Card(char, char); // constructor to create a card, setting the suit and rank
        void display(); // display the card example: AC, 10S, KD
        int compare(Card); // return 1 for win, 0 for tie, -1 for lose   
};

class Deck
{
    private:
        Card storage[52];
        int curr_card = 0;
    public:
        Deck(); // constructor which creates a deck of 52 cards
        Card deal(); // deal a card
        void display(); // show all the cards in the deck
        void shuffle(); // shuffle the cards in the deck
        bool isEmpty(); // return true if deck is empty
};

//Card Class
Card::Card()
{
    rank = '$';
    suit = '$';
}
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

//Deck class
Deck::Deck()
{
    char ranks[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
    char suits[4] = {'C', 'S', 'D', 'H'};
    int card = 0;
    for (int i=0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            storage[card] = Card(ranks[j], suits[i]);
            card += 1;
        }
    }
}
bool Deck::isEmpty()
{
    if (curr_card >= 52) {
        return true;
    } else {
        return false;
    }
}
Card Deck::deal()
{
    //error - empty deck
    if (isEmpty()) {
        throw "Error - Deck is empty";
    } else {
        Card card =  storage[curr_card];
        curr_card += 1;
        return card;
    }
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
    srand(time(0));
    for (int i = 0; i < 100000; i++) {
        int i1 = rand() % 52;
        int i2 = rand() % 52;
        Card temp = storage[i1];
        storage[i1] = storage[i2];
        storage[i2] = temp;
    }
}

//Driver
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

    //get number of games
    int games;
    cout << "How many games will they play? ";
    cin >> games;

    //create deck and shuffle
    Deck deck = Deck();
    cout << "\n Original Deck \n";
    deck.display(); 
    deck.shuffle();
    cout << "\n Shuffled Deck \n";
    deck.display();
    cout << '\n';

    //play games
    Card card1; 
    Card card2;
    for (int game=1;game<games+1;game++) {
        //get games and deal cards
        try {
            Card card1 = deck.deal(); //exception
            Card card2 = deck.deal();
            cout << "Game " << game << '\n';
            cout << "--------\n";
            cout << "        " << player1 << "=>";
            card1.display();
            cout << '\n';
            cout << "        " << player2 << "=>";
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
        } catch (const char* msg){
            cerr << msg << '\n';
            break;
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

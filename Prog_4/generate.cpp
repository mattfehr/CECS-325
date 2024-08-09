// Matthew Fehr
// CECS 325-02
// Prog 4 – Sorting Contest using pthreads
// 3/28/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[]) //argc is nuber of arguments passed, *argv[] is the list of those characters
{
    //if there isnt enough arguments, print message and terminate
    if (argc != 4) {
        cout << "Incorrect number of arguments. Please enter 3\n";
        cout << "Parameter 1: total amount of numbers you will generate\n";
        cout << "Parameter 2: minimum possible value of the generated numbers\n";
        cout << "Parameter 3: maximum possible valye of the generated numbers \n";
        cout << "Example: generate 100 -10 10 --> generates 100 numbers between -10 and 10\n";
        exit(EXIT_SUCCESS);
    }

    //store the arguments
    int count = stoi(argv[1]);
    int min = stoi(argv[2]);
    int max = stoi(argv[3]);

    // error if min is greater than max
    if (min > max) {
        cout << "Please ensure min is less than max\n";
        exit(EXIT_SUCCESS);
    }

    // print the arguments inputted
    cout << "Command: " << argv[0] << '\n';
    cout << "Total amount of numbers: " << count << '\n';
    cout << "Min value: " << min << '\n';
    cout << "Max value: " << max << '\n';
    cout << "Generating " << count << " numbers between " << min << " and " << max << "...\n";

    ofstream fout; //output file stream object 
    fout.open("numbers.dat", ios::out | ios::trunc); //open and associated file with fout and allow it to be written into and clear it each run
    srand(time(0));
    for (int i=0; i < count; i++) {
        fout << (rand() % (max-min+1) + min) << '\n'; //write random numbers into the file
    }
    fout.close(); //close the file
    cout << "Complete\n";

    return 0;
}
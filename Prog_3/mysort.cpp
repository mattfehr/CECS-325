// Matthew Fehr
// CECS 325-02
// Prog 3 – Sorting Contest
// 3/12/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void bubble(int A[], int size) {
    int temp;
    for (int i=0; i < size-1; i++) {
        for (int j =0; j < size-i-1; j++) {
            if (A[j] > A[j+1]) {
                temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
            }
        }  
    }
};

int main(int argc, char *argv[])
{
    //open numbers.dat into object fin
    ifstream fin;
    fin.open(argv[1], ios::in);

    //get amount of numbers from numbers.dat - get size
    int size = 0;
    string line;
    while (getline(fin, line)) {
        size++;
    }
    fin.close();

    //create array and add the numbers to it
    ifstream fin2;
    fin2.open(argv[1], ios::in);
    int nums[size];
    int i = 0;
    for (string line; getline(fin2, line);) {
        nums[i] = stoi(line);
        i++;
    }
    fin2.close();

    //run bubble sort
    bubble(nums, size);

    //save data into mysort.out
    ofstream fout;
    fout.open(argv[2], ios::out | ios::trunc); //delete previous content
    for (int num: nums) {
        fout << num << '\n';
    }
    fout.close();

    return 0;
}
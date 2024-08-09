// Matthew Fehr
// CECS 325-02
// Prog 4 – Sorting Contest using pthreads
// 3/28/2024
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

struct sortStuff {
    int *start;
    int size;
};

void *bridge (void *ptr) {
    sortStuff *arg = (sortStuff *) ptr; //change from void pointer to sortStuff pointer
    bubble(arg->start, arg->size);
    return NULL;
}

int *merge(int a1[], int a2[], int size) {
    int *result = new int[size*2];
    int i1 = 0;
    int i2 = 0;
    int ir = 0;
    while (i1 < size && i2 < size) {
        if (a1[i1] <= a2[i2]) {
            result[ir] = a1[i1];
            i1++;
        } else {
            result[ir] = a2[i2];
            i2++;
        }
        ir++; 
    }
    while (i1 < size) {
        result[ir] = a1[i1];
        i1++;
        ir++;
    }
    while (i2 < size) {
        result[ir] = a2[i2];
        i2++;
        ir++;
    }
    return result;
}

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
    int *numbers = new int[1000000]; // dynamic memory
    int i = 0;
    for (string line; getline(fin2, line);) {
        numbers[i] = stoi(line);
        i++;
    }
    fin2.close();

    //sort
    pthread_t t0, t1, t2, t3, t4, t5, t6, t7;

    sortStuff ss0;
    ss0.start = &numbers[0]; // start at the beginning of the array
    ss0.size = 125000; // sort the first 125000 numbers only

    sortStuff ss1;
    ss1.start = &numbers[125000]; // start at 125,000th numbe in array
    ss1.size = 125000; // sort 125000 numbers only

    sortStuff ss2;
    ss2.start = &numbers[250000]; // start at the 250,000th number
    ss2.size = 125000; // sort the first 125000 numbers only

    sortStuff ss3;
    ss3.start = &numbers[375000]; // start at the 375,000th number
    ss3.size = 125000; // sort 125000 numbers only

    sortStuff ss4;
    ss4.start = &numbers[500000]; // start at the 500,000th number
    ss4.size = 125000; // sort the first 125000 numbers only

    sortStuff ss5;
    ss5.start = &numbers[625000]; // start at 625,000th numbe in array
    ss5.size = 125000; // sort 125000 numbers only

    sortStuff ss6;
    ss6.start = &numbers[750000]; // start at the 750,000th number
    ss6.size = 125000; // sort the first 125000 numbers only

    sortStuff ss7;
    ss7.start = &numbers[875000]; // start at 875,000th numbe in array
    ss7.size = 125000; // sort 125000 numbers only

    pthread_create(&t0, NULL, bridge, (void*) &ss0);
    pthread_create(&t1, NULL, bridge, (void*) &ss1);
    pthread_create(&t2, NULL, bridge, (void*) &ss2);
    pthread_create(&t3, NULL, bridge, (void*) &ss3);
    pthread_create(&t4, NULL, bridge, (void*) &ss4);
    pthread_create(&t5, NULL, bridge, (void*) &ss5);
    pthread_create(&t6, NULL, bridge, (void*) &ss6);
    pthread_create(&t7, NULL, bridge, (void*) &ss7);

    //waits for thread to finish
    pthread_join(t0, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
    pthread_join(t6, NULL);
    pthread_join(t7, NULL);

    //merge
    //int *ZeroAndOne = new int[250000];
    int *ZeroAndOne = merge(ss0.start, ss1.start, 125000);
    //int *TwoAndThree = new int[250000];
    int *TwoAndThree = merge(ss2.start, ss3.start, 125000);
    //int *FourAndFive = new int[250000];
    int *FourAndFive = merge(ss4.start, ss5.start, 125000);
    //int *SixAndSeven = new int[250000];
    int *SixAndSeven = merge(ss6.start, ss7.start, 125000);

    //int *ZeroThroughThree = new int[500000];
    int *ZeroThroughThree = merge(ZeroAndOne, TwoAndThree, 250000);
    //int *FourThroughSeven = new int[500000];
    int *FourThroughSeven = merge(FourAndFive, SixAndSeven, 250000);
    delete[] ZeroAndOne;
    delete[] TwoAndThree;
    delete[] FourAndFive;
    delete[] SixAndSeven;

    //int *final_merge = new int[100000];
    int *final_merge = merge(ZeroThroughThree, FourThroughSeven, 500000);
    delete[] ZeroThroughThree;
    delete[] FourThroughSeven;

    //save data into mysort.out
    ofstream fout;
    fout.open(argv[2], ios::out | ios::trunc); //delete previous content
    for (int i=0; i < 1000000; i++) {
        fout << final_merge[i] << '\n';
    }
    fout.close();
    delete[] final_merge;
    delete[] numbers;

    return 0;
}
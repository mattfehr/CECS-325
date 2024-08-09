// Matthew Fehr
// CECS 325-02
// Prog 5 – Bucket List
// 4/23/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

int globalSwapCount = 0;

class Bucket{
    private:
        vector<int> v;
    public:
        Bucket();
        void generate(int size, int min, int max);
        void sort(); // Use the bubble sort from Prog3 and Prog4
        int size();
        int atIndex(int);
        void merge(Bucket b); // merge b into this
};

Bucket::Bucket()
{
    v;
}
void Bucket::generate(int size, int min, int max)
{
    srand(time(0));
    for (int i=0; i < size; i++) {
        v.push_back(rand() % (max-min+1) + min); //write random numbers into the vector
    }
}
void Bucket::sort()
{
    int temp;
    for (int i=0; i < v.size()-1; i++) {
        for (int j =0; j < v.size()-i-1; j++) {
            if (v[j] > v[j+1]) {
                temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
                globalSwapCount++;
            }
        }  
    }
}
int Bucket::size()
{
    return v.size();
}
int Bucket::atIndex(int i)
{
    return v[i];
}
void Bucket::merge(Bucket b)
{
    int vi = 0;
    int bi = 0;
    while (vi < v.size() && bi < b.size()) {
        if (b.atIndex(bi) < v[vi]) {
            v.insert(v.begin()+vi, b.atIndex(bi));
            bi++;
            vi++;
        } else {
            vi++;
        } 
    }
    while (bi < b.size()) {
        v.push_back(b.atIndex(bi));
        bi++;
    }
}

int main(int argc, char *argv[])
{
    srand(time(0));

    int bucketCount = stoi(argv[1]);
    int bucketSize = stoi(argv[2]);
    int bucketMin = stoi(argv[3]);
    int bucketMax = stoi(argv[4]);
    cout << "Bucket Count:"<<bucketCount<<endl;
    cout << "Bucket Size:"<<bucketSize<<endl;
    cout << "Bucket Min Value:"<<bucketMin<<endl;
    cout << "Bucket Max value:"<<bucketMax<<endl;

    vector<Bucket> list; // create empty Bucket vector

    Bucket *bptr;
    for(int i=0; i<bucketCount; i++) // creating bucketCount Buckets
    {
        bptr = new Bucket; // allocating new Bucket
        bptr->generate(bucketSize, bucketMin, bucketMax);
        //Bucket::generate(int,int,int,int)
        list.push_back(*bptr); // pushing Bucket onto list
    }

    for (auto it = list.begin(); it != list.end(); it++)
    {
        it->sort(); // Bucket::sort
    }

    Bucket endGame; // create empty Bucket to merge ALL buckets

    while (list.size() > 0) // vector<Bucket>::size()
    {
        endGame.merge(list[0]); // merge first bucket in list into endGame
        list.erase(list.begin()); // erase the first bucket in the list
    }

    // write all the numbers in endGame bucket to a file
    fstream out("bucketList.out", ios::out);
    for(int i=0; i<endGame.size(); i++) // Bucket::size()
        out << endGame.atIndex(i) << endl; // Bucket::atIndex(int)
    cout << "Global Swap Count:"<<globalSwapCount<<endl;
    cout << "\nbucketList.out has "<<bucketCount * bucketSize<< " sorted numbers\n";

    return 0;
}
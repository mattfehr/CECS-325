// Matthew Fehr
// CECS 325-02
// Prog 6 – BigInt
// 5/9/2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <iomanip>
using namespace std;

class BigInt
{
    private:
        vector<char> digits;
        BigInt fiboHelper(BigInt n, BigInt a = 0, BigInt b = 1) {
            if (n == BigInt(0)) {
                return a;
            } else if (n == BigInt(1)) {
                return b;
            } else {
                return fiboHelper(n-1, b, a+b);
            }
        }
        BigInt factHelper(BigInt n, BigInt a = 1) {
            if (n == BigInt(1)) {
                return a;
            } else {
                return factHelper(n-1, a*n);
            }
        }
    public:
        BigInt() {
            //empty digits vector
            //cout << "Entering BigInt()\n";
        }
        BigInt(int number) {
            //cout << "Entering BigInt(int)\n";
            if (number == 0) {
                digits.push_back(0);
            } else {
                while (number > 0) {
                    char digit = number%10; //storing number%10 as a ASCII value not the number as a char (char variables store ASCII values not the actual char)
                    //cout << int(digit) << '\n'; //converts the ASCII value to an int
                    digits.push_back(digit);
                    number /= 10;
                }
            }
        }
        BigInt(string s) {
            //cout << "Entering BigInt(string)\n";
            int length = s.size();
            for (int i = length-1; i >= 0; i--) {
                char digit = s[i] - 48; //store character as a ASCII value
                //cout << int(digit) << '\n';
                digits.push_back(digit);
            }
        }
        BigInt operator+ (const BigInt &b) {
            //cout << "Entering BigInt operator+(BigInt)\n";
            BigInt sum;
            BigInt other = b;
            BigInt self = *this;
            char carry = 0;
            char temp = 0;
            //make same size
            int self_size = self.digits.size();
            int other_size = other.digits.size();
            while (self_size > other_size) { 
                other.digits.push_back('0'-48); //push ASCII value 0
                other_size++;
            }
            while (self_size < other_size) {
                self.digits.push_back('0'-48);
                self_size++;
            }
            //actual addition
            for (int i=0; i < self_size; i++) {
                temp = self.digits[i]+other.digits[i]+carry; //adding ASCII values
                carry = temp/10;
                temp = temp%10;
                sum.digits.push_back(temp);
            }
            if (carry > 0) {
                sum.digits.push_back(carry);
            }
            return sum;
        }
        BigInt operator- (const BigInt &b) {
            //cout << "Entering BigInt operator-(BigInt)\n";
            BigInt self = *this;
            BigInt difference;
            BigInt other = b;
            char temp = 0;
            //make same size
            int self_size = self.digits.size();
            int other_size = other.digits.size();
            while (self_size > other_size) { 
                other.digits.push_back('0'-48);
                other_size++;
            }
            while (self_size < other_size) {
                self.digits.push_back('0'-48);
                self_size++;
            }
            for (int i=0; i < self_size; i++) {
                //get borrowed 1 if needed
                if (self.digits[i] < other.digits[i]) {
                    int j = i+1;
                    while (self.digits[j] == 0) {
                        self.digits[j] = 9;
                        j++;
                    }
                    self.digits[j] -= 1; 
                    self.digits[i] += 10;
                }
                temp = self.digits[i] - other.digits[i];
                difference.digits.push_back(temp);
            }
            // get rid of leading zeros
            while (difference.digits.back() == 0) {
                difference.digits.pop_back();
            }
            return difference;
        }
        BigInt operator- (const int &number) {
            //cout << "Entering BigInt operator-(int)\n";
            BigInt difference;
            BigInt self = *this;
            int self_size = self.digits.size();
            int n = number;
            char temp = 0;
            char digit = 0;
            for (int i=0; i < self_size; i++) {
                digit = n%10; //get digit in place value
                if (self.digits[i] < digit) {
                    int j = i+1;
                    while (self.digits[j] == 0) {
                        self.digits[j] = 9;
                        j++;
                    }
                    self.digits[j] -= 1;
                    self.digits[i] += 10;
                }
                temp = self.digits[i] - digit;
                difference.digits.push_back(temp);
                n /= 10; //move to next place value
            }
            //get rid of leading zeros
            while (difference.digits.back() == 0) {
                difference.digits.pop_back();
            }
            return difference;

        }
        BigInt operator* (const BigInt &b) {
            //cout << "Entering BigInt operator*(BigInt)\n";
            BigInt other = b;
            BigInt self = *this;
            int self_size = self.digits.size();
            int other_size = other.digits.size();
            vector<BigInt> pp(other_size, BigInt()); //partial products vector
            char carry = 0;
            char multiplier = 0;
            char prod = 0;
            char digit = 0;
            for (int i=0; i < other_size; i++) {
                multiplier = other.digits[i];
                for (int k=0; k < i; k++) {
                    pp[i].digits.push_back(0); //add placeholder zeros
                }
                carry = 0;
                for (int j=0; j < self_size; j++) { //actual multiplication algorithm
                    //cout << int(digits[j]) << "*" << int(multiplier) << "+" << int(carry) << "=" << int(digits[j]*multiplier+carry) << '\n';
                    prod = self.digits[j]*multiplier + carry;
                    carry = prod/10;
                    digit = prod%10;
                    pp[i].digits.push_back(digit);
                }
                if (carry > 0) {
                    pp[i].digits.push_back(carry);
                }
            }
            //add the partial products
            BigInt product;
            for (int i = 0; i < pp.size(); i++) {
                //cout << pp[i] << '\n';
                product = product + pp[i];
            }
            return product;

        }
        BigInt operator/ (const BigInt &b) {
            BigInt other = b;
            BigInt remainder = *this;
            BigInt quotient(0);
            while (other < remainder) {
                remainder = remainder - other;
                quotient = quotient + BigInt(1);
            }
            return quotient;
        }
        BigInt operator% (const BigInt &b) {
            BigInt remainder = *this;
            BigInt other = b;
            while (other < remainder) {
                remainder = remainder - other;
            }
            return remainder;
        }
        BigInt operator++(int) { //post-increment
            //cout << "Entering BigInt operator(int)\n";
            BigInt old = *this;
            ++*this;
            return old;
        }
        BigInt operator++() { //pre-increment
            //cout << "Entering BigInt operator++()\n";
            int self_size = digits.size();
            int i=0;
            while (digits[i] == 9 && i < self_size) { //if last digit is 9, change all subsequent 9s to 0
                digits[i] = 0;
                i++;
            }
            if (i == self_size) {
                digits.push_back(1); //if the whole number is 9s, need a new digit at the end (9999->10000)
            } else {
                digits[i] = digits[i]+1; //if the 9s dont reach the end, increment the number not 9 (1899->1900) or if not 9 in the first place (188->189)
            }
            return *this;
        }
        char operator[](int i) { //index function
            return digits[i];
        } 
        bool operator==(BigInt other) {
            return digits == other.digits;
        }
        bool operator<(const BigInt other) {
            if (digits.size() == other.digits.size()) {
                int i = digits.size()-1;
                while (digits[i] == other.digits[i]) {
                    i--;
                }
                return digits[i] < other.digits[i];
            } else {
                return digits.size() < other.digits.size();
            }
        }
        void print() {
            for (int i = digits.size()-1; i >= 0; i--) {
                cout << int(digits[i]);
            }
        }
        int size() {
            return digits.size();
        }
        BigInt fibo() { //calls fibohelper
            BigInt self = *this;
            return fiboHelper(self);
        }// calls fiboHelper
        BigInt fact() {
            // BigInt fact = *this;
            // BigInt one(1);
            // BigInt mult = fact-one;
            // while (!(mult == one)) {
            //     fact = fact*mult;
            //     mult = mult-one;
            // }
            return factHelper(*this);
        }
        friend ostream & operator<<(ostream &out, const BigInt &b) {
            //cout << "Entering operator<<()\n";
            if (b.digits.size() > 12) {
                for (int i = b.digits.size()-1; i >= b.digits.size()-7; i--) {
                    out << int(b.digits[i]);
                    if (i == b.digits.size()-1) {
                        out << '.';
                    }
                }
                out << 'e' << b.digits.size()-1;
            } else {
                for (auto rit = b.digits.rbegin(); rit != b.digits.rend(); rit++) {
                    out << int(*rit); //convert ASCII number to an int
                }   
            }
            return out;
        }
        friend BigInt operator+ (const int &a, const BigInt &b) {
            BigInt sum;
            int n = a;
            char digit;
            char temp;
            char carry = 0;
            BigInt self = b;
            int length = max(int(self.digits.size()), int(to_string(a).length())); //int(ceil(log10(a))));
            int resize = length-self.digits.size();
            if (length > self.digits.size()) {
                for (int i = 0; i < resize; i++) {
                    self.digits.push_back('0'-48);
                }
            }
            for (int i=0; i < length; i++) {
                int digit = n%10;
                temp = self.digits[i]+digit+carry;
                carry = temp/10;
                temp = temp%10;
                n = n/10;
                sum.digits.push_back(temp);
            }
            if (carry > 0) {
                sum.digits.push_back(carry);
            }
            return sum;
        }
};


void testUnit()
{
    int space = 10;
    cout << "\a\nTestUnit:\n"<<flush;
    system("whoami");
    system("date");
    // initialize variables
    BigInt n1(25);
    BigInt s1("25");
    BigInt n2(1234);
    BigInt s2("1234");
    BigInt n3(n2);

    BigInt fibo(12345);
    BigInt fact(50);
    BigInt imax = INT_MAX;
    BigInt big("9223372036854775807");

    // display variables
    cout << "n1(int)    :"<<setw(space)<<n1<<endl;
    cout << "s1(str)    :"<<setw(space)<<s1<<endl;
    cout << "n2(int)    :"<<setw(space)<<n2<<endl;
    cout << "s2(str)    :"<<setw(space)<<s2<<endl;
    cout << "n3(n2)     :"<<setw(space)<<n3<<endl;
    cout << "fibo(12345):"<<setw(space)<<fibo<<endl;
    cout << "fact(50)   :"<<setw(space)<<fact<<endl;
    cout << "imax       :"<<setw(space)<<imax<<endl;
    cout << "big        :"<<setw(space)<<big<<endl;
    cout << "big.print(): "; big.print(); cout << endl;

    cout << n2 << "/"<< n1<< " = "<< n2/n1 <<" rem "<<n2%n1<<endl;
    cout << "fibo("<<fibo<<") = "<<fibo.fibo() << endl;
    cout << "fact("<<fact<<") = "<<fact.fact() << endl;

    cout << "10 + n1 = " << 10+n1 << endl;
    cout << "n1 + 10 = " << n1+10 << endl;

    cout << "(n1 == s1)? --> "<<((n1==s1)?"true":"false")<<endl;
    cout << "n1++ = ? --> before:"<<n1++<<" after:"<<n1<<endl;
    cout << "++s1 = ? --> before:"<<++s1<<" after:"<<s1<<endl;

    cout << "s2 * big = ? --> "<< s2 * big<<endl;
    cout << "big * s2 = ? --> "<< big * s2<<endl;
}


int main()
{
    // BigInt n1("157");
    // cout << n1 << '\n';
    // BigInt n2(19);
    // int n3 = 19;
    // cout << n1 << "+" << n2 << "=" << n1+n2 << '\n';
    // cout << n1 << "-" << n3 << "=" << n1-19 << '\n';
    // cout << n1 << "*" << n2 << "=" << n1*n2 << '\n';
    // cout << n1 << "/" << n2 << "=" << n1/n2 << '\n';
    // cout << n1 << "%" << n2 << "=" << n1%n2 << '\n';
    // cout << "int(19)+" << n1 << "=" << int(19)+n1 << '\n';
    // BigInt inc("9999");
    // inc++;
    // cout << inc << "\n";
    //BigInt fact(25);
    //cout << fact.fact() << '\n';
    // cout << BigInt(4).fibo() << '\n';
    // cout << BigInt("25")*BigInt("24") << '\n';
    testUnit();

    return 0;
}


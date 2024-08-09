// This code shows how to create the BigInt constructor and operator<<()

#include <iostream>
#include <vector>

using namespace std;
		
class BigInt
{
	private:
		vector<char> digits;
	public:

		BigInt(int n)
		{
			cout << "Entering BigInt()\n";
			if (n == 0)
				digits.push_back(0);
			else
			while (n > 0)
			{
				char digit = n%10;
				cout << int(digit) << endl;
	
				digits.push_back(digit);
				n /= 10;
			}
		}

        // this function seems to print the BigInt backwards...?
		friend ostream & operator<<(ostream & out, BigInt b)
		{	
		    cout << "Entering operator<<()\n";
			vector<char>::iterator it = b.digits.begin();
			while (it != b.digits.end())
				out << int(*it++);
			return out;
        	}
};


int main()
{
	BigInt b(42);
	cout << b;
}
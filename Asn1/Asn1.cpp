/*
    Cole Lawrence (Lawrence0)
    January 21st, 2015
	Asn1
	Windows 8.1/MVSE2012

	Outputs the age of Cole Lawrence prefixed with an integer, repeated for integers 1 through 9 inclusive.
*/
#include <cstdlib>
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;

// Use the address to change the number
void performSteps(int *anInteger) {
	//3. 
	*anInteger *= 2;
	//4.
	*anInteger += 5;
	//5.
	*anInteger *= 50;
	//6.
	int currentYear = 2015;
	*anInteger += currentYear;
	//7.
	bool hasHadBDay = false;
	*anInteger -= hasHadBDay ? 250 : 251;
	//8.
	int birthYear = 1996;
	*anInteger -= birthYear;
}

int main()
{
	//1. Choose integers existent in [1, 9]
	for (int from = 1, to = 9, i = from; i <= to; i++)
    {
		int anInteger = i;

		//2. In the steps which follow, @anInteger changes
		performSteps(&anInteger);

        cout << "Current chosen value is " << i << ", so the three-digit number is  " << anInteger << std::endl;
    }
}

// Napon Krassner (Jett)
// CSC 2430, Homework 2
// 4-20-2015
// Due: 4-29-2015
// Name: Long Integer Class with Operators Client - clientLongInt.cpp
// Description: This is the client file to test the LongInt class. It contains
//				the main program that will input 2 values, add them to get a
//				third value, multiply them together to produce a fourth value,
//				and outputs the two original values, sum and the product.
//				It also include code to test and demonstrate the LongInt class.
//******************************************************************************

#include <iostream>
#include <iomanip>
#include "LongInt.h"

using namespace std;

int main(int argc, char *argv[])
{
	cout << "****Welcome to Long Integer Class with Operators by Napon Krassner (Jett)****" << endl << endl;

	// Testing default constructor
	cout << "----Testing default constructor----" << endl;
	LongInt x, y;
	cout << "Initially x = " << x << endl << endl;
	
	// Testing constructor with input from keyboard and istream operator
	cout << "----Testing constructor with input from keyboard and istream operator----" << endl;
	cout << "LongInt Testing" << endl;
	cout << "Enter x: ";
	cin >> x;
	cout << "Enter y: ";
	cin >> y;
	cout << endl;

	// Determine length of largest value
	int maxlen = x.size();
	if (maxlen < y.size())
		maxlen = y.size();

	++maxlen;  // Leave room for carry out

	// Test printing with formatting
	cout << "----Test printing with formatting----" << endl;
	cout << "  x = " << setw(maxlen) << x << endl;
	cout << "  y = " << setw(maxlen) << y << endl << endl;

	// Test sum and product operator
	cout << "----Test sum and product operator----" << endl;
	LongInt sum = x + y;
	LongInt prod = x * y;
	cout << "sum = " << setw(maxlen) << sum << endl;
	cout << "prod= " << setw(maxlen) << prod << endl << endl;
	
	// Test == method
	cout << "----Test == method----" << endl;
	if (x == y)
		cout << "[x == y]" << endl;
	else
		cout << "[x != y]" << endl << endl;

	// Test "On the fly" addition
	cout << "----Test \"On the fly\" addition----" << endl;
	cout << "fly = " << LongInt("12345") + LongInt("987") << endl << endl;
	

	// Test += method
	cout << "----Test += method----" << endl;
	x = LongInt("12345");
	x += LongInt("987");
	cout << "  x = " << x << endl << endl;
	
	// Test *= method
	cout << "----Test *= method----" << endl;
	y = LongInt("12345");
	y *= LongInt("789");
	cout << "  y = " << y << endl << endl;
	
	return 0;
}
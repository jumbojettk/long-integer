// Napon Krassner (Jett)
// CSC 2430, Homework 2
// 4-20-2015
// Due: 4-29-2015
// Name: Long Integer Class with Operators Header - LongInt.h
// Description: This is the header file for the LongInt class contains all the
//				member function and member variable declarations and as well as
//				a inline documentation showing how things work.
//******************************************************************************

#ifndef _LONG_INT_
#define _LONG_INT_

#include <iostream>
#include <list>
#include <string>

using namespace std;

class LongInt
{
public:
	//********FRIEND FUNCTIONS/OPERATORS********
	// Parameters:  istream& - the istream object, LongInt& the LongInt object
	//				to be stored into.
	// Return: istream& object to input
	// Description: Clear out old value, inputs a sequence of LongInt
	//				chars on a single line, one digit at a time and
	//				stores them in the internal list.
	friend istream& operator>>(istream&, LongInt&);

	// Parameters:  ostream& - for output stream,
	//				const LongInt& v - for the value to be printed
	// Return: ostream& object to be output.
	// Description: Outputs the sequence of digits in LongInt from
	//				most-sig to least-sig.
	//				If field width > length of x
	//				then value must be right-justified by:
	//				output preceding series of blank spaces before
	//				numeric value.
	// Note: out.width() specifies min # of chars to be output
	friend ostream& operator<<(ostream&, const LongInt&);

	// Parameters:const LongInt& - a value x, const LongInt& - a value y
	// Return: LongInt - representing the sum of the 2 input objects (x + y)
	// Description: Adds the correspoding digits of two input values
	//				Deals with 'carry' over.
	//				Creates a new LongInt sum.
	// Notes:   Adding two numbers must begin with least-sigdigs,
	//			iterate towards the most sigdigs.
	//			Since the digits in a LongInt are stored as individual chars,
	//			convert each digit-char into the numeric value before adding.
	//			Then convert the num digit-sum back to char value and
	//			a possible 'carry' value into the adjacent position.
	//			
	friend LongInt operator+(const LongInt&, const LongInt&);

	// Parameters: const LongInt& - a value x, const LongInt& - a value y
	// Return: LongInt - representing the product of the 2 input objects.
	// Description: Multiplies the two input values.
	//				Deals with 'carry' over.
	//				Creates a new LongInt product.
	friend LongInt operator*(const LongInt&, const LongInt&);

	// Parameters:  const LongInt& for the first LongInt value
	//				const LongInt& for the second LongInt value
	// Return: True - if both values are same numeric value, False otherwise
	// Description: Compares the two LongInt values to see if they are equal.
	friend bool operator==(const LongInt&, const LongInt&);

	//********CONSTRUCTORS********
	// Parameters: None
	// Return: Nothing
	// Description: Initialize list representing the value 0.
	LongInt();

	// Parameters: String - the long number/digits
	// Return: Nothing
	// Description: Initialize the internal list to each of the digits in
	//				string parameter.
	LongInt(const string);

	//********DESTRUCTOR********
	// Don't need destructor since not allocating memory from the heap.

	//********ACCESSORS********
	// Parameters: None
	// Return: int - for number of decimal digs in the LongInt object
	// Description: Calculate and returns the size of the LongInt list.
	int size() const;

	//********MUTATORS********
	// Parameters: const LongInt& - for value to add to the cur LongInt.
	// Return: LongInt& - representing the result of the sum
	// Description: Adds the value in the parameter to the current
	//				value of LongInt.
	LongInt& operator+=(const LongInt&);

	// Parameters: const LongInt& - for value to multiply to the cur LongInt.
	// Return: LongInt& - representing the result of the product
	// Description: Multiplies the value in the parameter to the current
	//				value of LongInt.
	LongInt& operator*=(const LongInt&);

	


private:
	//********PRIVATE MEMBER VARIABLES********
	list<char> val;

	//********PRIVATE UTILITIES********
};

#endif
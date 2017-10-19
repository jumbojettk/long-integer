// Napon Krassner (Jett)
// CSC 2430, Homework 2
// 4-20-2015
// Due: 4-29-2015
// Name: Long Integer Class with Operators Implementation - LongInt.cpp
// Description: This is the implementation file for the LongInt class contains
//				all the function definition and shows how each member functions
//				and variables are implemented. The LongInt class uses the
//				STL list object to manipulate and calculate long integer
//				operations (addition and multiplication).
//******************************************************************************

#include <iostream>
#include <iomanip>
#include <list>
#include <string>
#include "LongInt.h"

using namespace std;

//********FRIEND FUNCTIONS/OPERATORS********
istream& operator>>(istream& in, LongInt& v)
{
	v.val.clear();  // clear old value in v
	char temp[1000];  // create array of char to store input
	
	// store input into array of char until \n
	// array now ends with '\0'
	in.getline(temp, 1000, '\n');

	// store 1 char at a time to v until reach '\0'
	char *cur = temp;
	while (*cur != '\0')  // don't store '\0' in the list
	{
		v.val.push_back(*cur);
		cur++;
	}

	return in;
}

ostream& operator<<(ostream& out, const LongInt& v)
{
	// Iterate through a const list
	list<char>::const_iterator curr;
	curr = v.val.begin();

	// Add space if field width > size of list
	if (out.width() > v.val.size())
	{
		int extraSpace = out.width() - v.val.size();

		for (int i = 0; i < extraSpace; i++)
		{
			out << ' ';
		}
	}
	
	// Don't have to test for empty list since init to 0
	while (curr != v.val.end())  // while not at the end
	{
		out << *curr;  // dereference and store to out obj
		curr++;
	}

	return out;
}


LongInt operator+(const LongInt& x, const LongInt& y)
{
	// Declare iterators start from end
	list<char>::const_reverse_iterator xRevCurr = x.val.rbegin();
	list<char>::const_reverse_iterator yRevCurr = y.val.rbegin();

	// Create new LongInt sum to store the string of added values
	LongInt sum;
	sum.val.clear();

	// Neccessary for carry over
	bool carry = false;
	int carryInt;
	int noneCarryInt;

	// Loop and iterate towards beginning of one of/both list
	while (xRevCurr != x.val.rend() && yRevCurr != y.val.rend())
	{
		// Convert char to int
		int xInt = *xRevCurr - '0';
		int yInt = *yRevCurr - '0';
		int xyIntSum;

		// If carry over before adding (from last digit)
		if (carry)  
		{
			xyIntSum = xInt + yInt + carryInt;// Add two values and the carry over
			carry = false;  // set back to false
		}
		else
			xyIntSum = xInt + yInt;  // Add two values

		// If value > 9 prepare for carry over
		if (xyIntSum >= 10)
		{
			carry = true;
			carryInt = xyIntSum / 10;  // Store the carry over
			noneCarryInt = xyIntSum % 10;  // Store the int
		}

		// If no carry over
		if (!carry)
		{
			string xyStrSum = to_string(xyIntSum);  // convert int back to char
			char xyCharSum = xyStrSum[0];
			sum.val.push_front(xyCharSum);  // push char to front of list
			
		}
		else  // store the none carryover digit
		{
			string xyStrSum = to_string(noneCarryInt);
			char xyCharSum = xyStrSum[0];
			sum.val.push_front(xyCharSum);
		}

		// Icrement to the next digit on both lists.
		xRevCurr++;
		yRevCurr++;
	}
	

	// Deal with the rest of the list if list has unequal size
	// Means y has bigger size
	while (xRevCurr != x.val.rend())
	{
		int xInt = *xRevCurr - '0';

		if (carry)  // Add the carry
		{
			xInt += carryInt;  // Add the carry over
			carry = false;  // set back to false

			// If value >= 10 prepare for carry over
			if (xInt >= 10)
			{
				carry = true;
				carryInt = xInt / 10;  // Store the carry over
				noneCarryInt = xInt % 10;  // Store the int
			}
		}

		// If no carry over
		if (!carry)
		{
			string xStr = to_string(xInt);  // convert int back to char
			char xChar = xStr[0];
			sum.val.push_front(xChar);  // push char to front of list
		}
		else  // store the none carryover digit
		{
			string xAddStr = to_string(noneCarryInt);
			char xAddChar = xAddStr[0];
			sum.val.push_front(xAddChar);
			
		}
		xRevCurr++;
	}
	// Means y has bigger size
	while (yRevCurr != y.val.rend())
	{
		int yInt = *yRevCurr - '0';

		if (carry)  // Add the carry
		{
			yInt += carryInt;  // Add the carry over
			carry = false;  // set back to false

			// If value >= 10 prepare for carry over
			if (yInt >= 10)
			{
				carry = true;
				carryInt = yInt / 10;  // Store the carry over
				noneCarryInt = yInt % 10;  // Store the int
			}
		}

		// If no carry over
		if (!carry)
		{
			string yStr = to_string(yInt);  // convert int back to char
			char yChar = yStr[0];
			sum.val.push_front(yChar);  // push char to front of list
		}
		else  // store the none carryover digit
		{
			string yAddStr = to_string(noneCarryInt);
			char yAddChar = yAddStr[0];
			sum.val.push_front(yAddChar);
			
		}
		yRevCurr++;
	}

	// If there's still carryover after both lists ended
	if (carry)
	{
		string leftOverCarryStr = to_string(carryInt);// convert int back to char
		char leftOverCarryChar = leftOverCarryStr[0];
		sum.val.push_front(leftOverCarryChar);// push char to front of list
		carry = false;
	}

	return sum;
}


LongInt operator*(const LongInt& x, const LongInt& y)
{
	// Create new LongInt object to store product and carry over
	LongInt prod;
	LongInt bottomList = y;
	LongInt topList = x;
	int countZero = 0;

	// Declare iterators from end of list
	list<char>::reverse_iterator botRevCurr = bottomList.val.rbegin();
	list<char>::reverse_iterator topRevCurr;

	// Iterate through the bottom list
	while (botRevCurr != bottomList.val.rend())
	{
		// Convert char to int
		int botInt = *botRevCurr - '0';
		topRevCurr = topList.val.rbegin();
		
		// Declare another list to store each multiplication for adding later
		LongInt tmpList;
		list<char>::reverse_iterator tmpRevCurr = tmpList.val.rbegin();
		for (int i = 0; i < countZero; i++)  // fill in the zero for adding
		{
			tmpList.val.push_front('0');
			tmpRevCurr++;
		}

		// Iterate through top list
		while (topRevCurr != topList.val.rend())
		{
			int topInt = *topRevCurr - '0';  // convert to int

			if (tmpRevCurr != tmpList.val.rend()) // If theres a value (carry over)
			{
				int tmpInt = *tmpRevCurr - '0';  // convert to int
				tmpInt = tmpInt + (botInt * topInt);

				if (tmpInt > 9)  // carry over
				{
					int carry = tmpInt / 10;  // carry
					int nonCarry = tmpInt % 10;  // non-carry
					
					// convert back to char
					string nonCarryStr = to_string(nonCarry);
					char nonCarryCh = nonCarryStr[0];
					string carryStr = to_string(carry);
					char carryCh = carryStr[0];

					// pop out the carry over and push
					tmpList.val.pop_front();
					tmpList.val.push_front(nonCarryCh);
					tmpList.val.push_front(carryCh);


				}
				else
				{
					// convert to char
					string tmpStr = to_string(tmpInt);
					char tmpCh = tmpStr[0];

					// pop and push
					tmpList.val.pop_front();
					tmpList.val.push_front(tmpCh);
				}

				// Icrement
				tmpRevCurr++;
				topRevCurr++;
			}
			else  // no carry over
			{
				int tmpInt = botInt * topInt;

				if (tmpInt > 9)
				{
					int carry = tmpInt / 10;
					int nonCarry = tmpInt % 10;

					// convert back to char
					string nonCarryStr = to_string(nonCarry);
					char nonCarryCh = nonCarryStr[0];
					string carryStr = to_string(carry);
					char carryCh = carryStr[0];

					// push but don't pop since no carry over
					tmpList.val.push_front(nonCarryCh);
					tmpList.val.push_front(carryCh);
				}
				else
				{
					string tmpStr = to_string(tmpInt);
					char tmpCh = tmpStr[0];

					// push but don't pop, no carry over
					tmpList.val.push_front(tmpCh);
				}

				// Icrement
				tmpRevCurr++;
				topRevCurr++;
			}	
		}

		prod += tmpList;

		// Increment and count
		botRevCurr++;
		countZero++;
	}
	return prod;
}

bool operator==(const LongInt& x, const LongInt& y)
{
	bool equal = false;

	// Declare const_iterators for both x and y
	list<char>::const_iterator xCurr = x.val.begin();
	list<char>::const_iterator yCurr = y.val.begin();

	if (x.size() != y.size())  // compare size of list first
		equal = false;
	else
	{
		while (xCurr != x.val.end() && yCurr != y.val.end())  // while not end of both list
		{
			if (*xCurr == *yCurr)  // keep iterating if they are equal
			{
				equal = true;
				xCurr++;
				yCurr++;
			}
			else
			{
				// false and exit loop
				equal = false;
				break;
			}
		}
	}

	return equal;
}

//********CONSTRUCTORS********
LongInt::LongInt()
{
	// Init list to have value 0
	val.push_back('0');
}


LongInt::LongInt(const string v)
{
	// Clear list before init
	val.clear();

	// Init val list with the values in v
	for (int i = 0; i < v.length(); i++)
	{
		val.push_back(v[i]);
	}
}

//********ACCESSORS********
int LongInt::size() const
{
	return val.size();
}


//********MUTATORS********
// Note: rhs = right hand side
LongInt& LongInt::operator+=(const LongInt& rhs)
{
	LongInt sum = *this + rhs;
	*this = sum;
	return *this;
}

LongInt& LongInt::operator*=(const LongInt& rhs)
{
	LongInt prod = *this * rhs;
	*this = prod;
	return *this;
}
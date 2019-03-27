#pragma once
#include <iostream>
#include <string>

using namespace std;

// constants for Number
#define BITS_PER_BYTE 8 // Each byte has 4 bits
#define BITS_IN_NUMBER 128 // Each Number has 128 bits
#define INTS_IN_NUMBER 4 // Each Number has 4 ints
#define BITS_PER_INT 32 // number of bits per int

// constants for Qfloat
#define BITS_IN_EXPONENT 15
#define BITS_IN_FRACTION 112

class Number {
protected:
	int m_number[INTS_IN_NUMBER]; // this number
public:
	Number();
	char getBit(const int i) const; // get bit at position i from m_number
	void setBit(const int i); // set bit at position i from m_number to 1
};

char getBit(const int n, const int i); // get bit at position i from int n
void setBit(int &n, const int i); // get bit at position i from int n
string add(const string &, const string &); // return string1+string2
string sub(const string &, const string &); // return string1-string2
string mul10(const string &n);
string div10(const string &n);
string mul2(const string &); // return string*2
string div2(const string &); // return string/2
string calculate2power(const int exp); // return 2^exp (string)
string DecToBin(const string &dec); // convert a decimal string into a binary string 
string BinToDec(const string &bin); // convert a binary string into a decimal string 
void PrintBin(const Number &); // print a Number in binary form

// --------------- Main Function -------------- //
bool *DecToBin(const Number&);
char *BinToHex(bool *bit);

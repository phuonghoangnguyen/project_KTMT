#pragma once
#include <map>

using namespace std;

#define BITS_PER_BYTE 8 // Each byte has 4 bits
#define BITS_IN_NUMBER 128 // Each Number has 128 bits
#define INTS_IN_NUMBER 4 // Each Number has 4 ints
#define BITS_PER_INT 32 // number of bits per int

class Number {
protected:
	int m_number[INTS_IN_NUMBER]; // this number
public:
	Number();
	char getBit(const int i) const; // get bit at position i from m_numbe
	void setBit(const int i); // set bit at position i from m_number to 1
};

char getBit(const int n, const int i); // get bit at position i from int n
// --------------- Main Function -------------- //
bool *DecToBin(const Number&);
char *BinToHex(bool *bit);

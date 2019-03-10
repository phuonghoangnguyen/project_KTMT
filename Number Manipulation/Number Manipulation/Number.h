#pragma once
#define BITS_PER_BYTE 8 // Each byte has 4 bits
#define BITS_IN_NUMBER 128 // Each Number has 128 bits
#define INTS_IN_NUMBER 4 // Each Number has 4 ints
const int BITS_PER_INT = BITS_PER_BYTE * sizeof(int); // number of bits per int

class Number {
protected:
	int m_number[INTS_IN_NUMBER]; // this number
public:
	Number();
	char getBit(const int i) const; // get bit at position i from m_number
	void setBit(const int i);
};

char getBit(const int n, const int i); // get bit at position i from int n

// --------------- Main Function -------------- //
bool *DecToBin(const Number&);
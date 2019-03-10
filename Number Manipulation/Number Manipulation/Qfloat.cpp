#include "Number.h"
#include "QFloat.h"
#include <string>
#include <cstdlib>

Qfloat::Qfloat() : Number()
{}

Qfloat::Qfloat(const string &)
{}

Qfloat::Qfloat(const Qfloat & other)
{
	for (int i = 0; i < INTS_IN_NUMBER; i++)
		m_number[i] = other.m_number[i];
}

string toIEEE754(const string binaryString) {
	// convert a binary float string into the binary format using IEEE-754 Standard
	const int binarySize = binaryString.length();
	const int qfloatSize = INTS_IN_NUMBER * BITS_PER_INT;
	char signBit;
	int expBits;

	int start;
	// identify the signBit
	if (binaryString[0] == '-') {
		signBit = '1';
		start = 2;
	}
	else {
		signBit = '0';
		start = 1;
	}

	// identify the expBitsonent
	int i = start;
	for (; i < binarySize; i++) {
		if (binaryString[i] == '.')
			break;
	}
	expBits = pow(2, BITS_IN_EXPONENT - 1) + i - start;

	string result;
	result += signBit;

	for (i = BITS_IN_EXPONENT - 1; i >= 0; i--)
		getBit(expBits, i) == 1 ? result += '1' : result += '0';

	i = start;
	while (i < binarySize) {
		if (binaryString[i] == '.') {
			i++;
			continue;
		}
		result += binaryString[i++];
	}
	return result;
}
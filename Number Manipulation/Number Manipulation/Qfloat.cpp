#include "Number.h"
#include "QFloat.h"
#include <string>
#include <cstdlib>

void Qfloat::setBinary(const string &bin)
{
	int length = bin.length();
	for (int i = 0; i < length; i++)
		if (bin[i] == '1')
			setBit(BITS_IN_NUMBER - i - 1);
}

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

	int pointPosition;
	int onePosition;
	for (int i = start; i < binarySize; i++) {
		if (binaryString[i] == '.')
			pointPosition = i;
		else if (binaryString[i] == '1')
			onePosition = i;
	}

	expBits = (pow(2, BITS_IN_EXPONENT - 1) - 1) + (pointPosition - onePosition) -
		(pointPosition > onePosition) ? 1 : 0;

	string result;
	result += signBit;

	for (int i = BITS_IN_EXPONENT - 1; i >= 0; i--)
		getBit(expBits, i) == 1 ? result += '1' : result += '0';

	int i = start;
	while (i < binarySize) {
		if (binaryString[i] == '.') {
			i++;
			continue;
		}
		result += binaryString[i++];
	}
	return result;
}
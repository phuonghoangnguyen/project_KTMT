#include "Number.h"
#include <string>

char Number::getBit(const int i) const
{
	// get bit at position i from m_number
	return (m_number[i / BITS_PER_INT] >> i % BITS_PER_INT) & 1;
}

void Number::setBit(const int i) {
	m_number[i / BITS_PER_INT] |= (1 << i % BITS_PER_INT);
}

Number::Number()
{
	for (int i = 0; i < INTS_IN_NUMBER; i++)
		m_number[i] = 0;
}

char getBit(const int n, const int i) {
	// get bit at position i from an int n
	return (n >> i) & 1;
}

bool *DecToBin(const Number& x)
{
	bool *result = new bool[BITS_IN_NUMBER];
	for (int i = 0; i < BITS_IN_NUMBER; i++)
		result[BITS_IN_NUMBER - i - 1] = x.getBit(i) == 1 ? true : false;
	return result;
}

char *BinToHex(bool *bit)
{
	char* result = new char[BITS_IN_NUMBER / 4 + 1];
	int i = 0;
	while (i < BITS_IN_NUMBER) {
		int dec = 0;
		do {
			if (bit[i])
				dec += (int)pow(2, 3 - i % 4);
			i++;
		} while (i % 4 != 0);
		result[(i - 1) / 4] = (dec < 10) ? '0' + dec : 'A' + dec - 10;
	}
	result[BITS_IN_NUMBER / 4] = '\0';
	return result;
}

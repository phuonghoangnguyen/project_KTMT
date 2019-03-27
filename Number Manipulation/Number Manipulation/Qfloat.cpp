#include "Number.h"
#include "QFloat.h"

void Qfloat::setBinary(const string &bin)
{
	int length = bin.length();
	for (int i = 0; i < length; i++)
		if (bin[i] == '1')
			setBit(BITS_IN_NUMBER - i - 1);
}

Qfloat::Qfloat() : Number()
{}

string toIEEE754(const string binaryString);

Qfloat::Qfloat(const string & s, int base)
{
	string binaryString = s;
	if (base == 10) {
		binaryString = DecToBin(binaryString);
		binaryString = toIEEE754(binaryString);
	}
	setBinary(binaryString);
}

Qfloat::Qfloat(const Qfloat & other)
{
	for (int i = 0; i < INTS_IN_NUMBER; i++)
		m_number[i] = other.m_number[i];
}

string toIEEE754(const string binaryString) 
{
	string result;
	// convert a binary float string into the binary format using IEEE-754 Standard
	const int binarySize = binaryString.length();

	// identify the sign bit
	char signBit = (binaryString[0] == '-') ? '1' : '0';
	result += signBit;

	// identify the exponent bits
	int expBits;

	int pointPosition = binaryString.find('.');
	if (pointPosition == -1)
		pointPosition = binarySize;

	int onePosition = binaryString.find('1');

	expBits = (pow(2, BITS_IN_EXPONENT - 1) - 1) + (pointPosition - onePosition);
	if (pointPosition > onePosition)
		expBits -= 1;

	for (int i = BITS_IN_EXPONENT - 1; i >= 0; i--)
		getBit(expBits, i) == 1 ? result += '1' : result += '0';

	int i = onePosition + 1;
	while (i < binarySize) {
		if (binaryString[i] == '.') {
			i++;
			continue;
		}
		result += binaryString[i++];
	}
	return result;
}

void ScanQfloat(Qfloat & x)
{
	string n;
	getline(cin, n);
	x = Qfloat(n, 10);
}

void PrintQfloat(const Qfloat & x)
{
	string result;

	int expBits = 0;
	for (int i = 0; i < BITS_IN_EXPONENT; i++) {
		if (x.getBit(BITS_IN_NUMBER - 1 - BITS_IN_EXPONENT + i) == 1)
			setBit(expBits, i);
	}
	expBits -= pow(2, BITS_IN_EXPONENT - 1) - 1;

	for (int i = 0; i < BITS_IN_FRACTION; i++) {
		result = (x.getBit(i) == 1) ? ('1' + result) : ('0' + result);
	}
	result = "1." + result;

	if (expBits > 0)
	{
		int pointPosition = 1;
		for (int i = 0; i < expBits; i++)
			result = mul10(result);
	}
	else
	{
		for (int i = expBits; i < 0; i++)
			result = '0' + result;

		int pointPosition = result.find('.');
		expBits = -expBits;
		for (int i = 0; i < expBits; i++)
			result = div10(result);
	}

	result = BinToDec(result);
	if (x.getBit(BITS_IN_NUMBER - 1) == 1)
		result = '-' + result;

	cout << result;
}

Qfloat binToDec(bool * bit)
{
	Qfloat result;
	for (int i = 0; i < BITS_IN_NUMBER; i++)
		if (bit[i])
			result.setBit(BITS_IN_NUMBER - 1 - i);
	return result;
}
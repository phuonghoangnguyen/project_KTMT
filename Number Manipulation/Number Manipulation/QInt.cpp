#include "QInt.h"
#include <algorithm>
#include <string>

QInt::QInt() : Number()
{}

QInt::QInt(const string&, int base)
{
}

QInt::QInt(const QInt & other)
{
	for (int i = 0; i < INTS_IN_NUMBER; i++)
		m_number[i] = other.m_number[i];
}

bool QInt::operator==(const QInt & other) const
{
	for (int i = 0; i < INTS_IN_NUMBER; i++)
		if (other.m_number[i] != m_number[i])
			return false;
	return true;
}

bool QInt::operator>(const QInt &other) const
{
	bool thisHasSign = this->getBit(BITS_IN_NUMBER - 1) == 1 ? true : false;
	bool otherHasSign = other.getBit(BITS_IN_NUMBER - 1) == 1 ? true : false;
	if (!thisHasSign && otherHasSign)
		return true;
	else if (thisHasSign && !otherHasSign)
		return false;
	for (int i = BITS_IN_NUMBER - 1; i >= 0; i--) {
		if (this->getBit(i) > other.getBit(i))
			return true;
	}
	return false;
}

bool QInt::operator<(const QInt &other) const
{
	bool thisHasSign = this->getBit(BITS_IN_NUMBER - 1) == 1 ? true : false;
	bool otherHasSign = other.getBit(BITS_IN_NUMBER - 1) == 1 ? true : false;
	if (!thisHasSign && otherHasSign)
		return false;
	else if (thisHasSign && !otherHasSign)
		return true;
	for (int i = BITS_IN_NUMBER - 1; i >= 0; i--) {
		if (this->getBit(i) < other.getBit(i))
			return true;
	}
	return false;
}

bool QInt::operator>=(const QInt &other) const
{
	return !(other < *this);
}

bool QInt::operator<=(const QInt & other) const
{
	return !(other > *this);
}

void QInt::operator=(const QInt &other)
{
	for (int i = 0; i < INTS_IN_NUMBER; i++)
		m_number[i] = other.m_number[i];
}

QInt QInt::operator~() const
{
	// not
	QInt result(*this);
	for (int i = 0; i < INTS_IN_NUMBER; i++)
		result.m_number[i] = ~m_number[i];
	return result;
}

QInt QInt::operator&(const QInt & other) const
{
	// and
	QInt result(*this);
	for (int i = 0; i < INTS_IN_NUMBER; i++)
		result.m_number[i] = other.m_number[i] & m_number[i];
	return result;
}

QInt QInt::operator|(const QInt & other) const
{
	// or
	QInt result(*this);
	for (int i = 0; i < INTS_IN_NUMBER; i++)
		result.m_number[i] = other.m_number[i] | m_number[i];
	return result;
}

QInt QInt::operator^(const QInt & other) const
{
	// xor
	QInt result(*this);
	for (int i = 0; i < INTS_IN_NUMBER; i++)
		result.m_number[i] = other.m_number[i] ^ m_number[i];
	return result;
}

/*QInt QInt::operator>>(const int d)
{
	QInt result;
	for (int i = BITS_IN_NUMBER - d - 1; i >= 0; i--) {
		if (getBit(i) == 1)
			result.setBit(i + d);
	}
	return result;
}*/

QInt QInt::operator<<(const int d)
{
	QInt result;
	for (int i = BITS_IN_NUMBER - d - 1; i >= 0; i--) {
		if (getBit(i) == 1)
			result.setBit(i + d);
	}
	return result;
}

pair<char, char> plusBit(char a, char b) {
	// add 2 bit return a pair of result and carry
	if (a != b) {
		return { '1','0' };
	}
	else {
		if (a == '0') {
			return { '0','0' };
		}
		else {
			return { '0','1' };
		}
	}
}

string to2sComplement(const string & binaryString)
{
	/*
		convert a binary string to 2's complement form
	*/
	string res = "";
	string temp = binaryString;
	char carry = '1';
	for (int i = binaryString.size() - 1; i >= 0; i--) {
		binaryString[i] == '1' ? temp[i] = '0' : temp[i] = '1';
		pair<char, char> p = plusBit(temp[i], carry);
		res += p.first;
		carry = p.second;
	}
	reverse(res.begin(), res.end());
	return res;
}

string toSignedBinary(const string & binaryString)
{
	/*
		usage: convert "-00001" into "11111"
						"00001" into "00001"
	*/
	if (binaryString[0] == '+')
		return binaryString;
	return to2sComplement(binaryString.c_str() + 1);
}


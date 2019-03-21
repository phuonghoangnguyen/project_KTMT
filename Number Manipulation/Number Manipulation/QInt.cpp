#include "QInt.h"
#include <algorithm>

void QInt::setBinary(const string & bin)
{
	int length = bin.length();
	for (int i = length - 1; i >= 0; i--)
		if (bin[i] == '1')
			setBit(length - i - 1);
}

void QInt::setHex(const string &hex)
{
	int length = hex.length();
	int start = -1;
	int pos = 0;
	for (int i = length - 1; i >= 0; i--) {
		if (pos % BITS_PER_INT == 0)
		{
			pos = 0;
			start++;
		}
		m_number[start] |= ((hex[i] >= '0' && hex[i] <= '9') ? hex[i] - '0' : hex[i] + 10 - 'A') << pos;
		pos += 4;
	}
}

string toSignedBinary(const string & binaryString);
void QInt::setDec(const string &dec)
{
	string bin = DecToBin(dec);
	
	if (bin[0] == '-') 
		bin = toSignedBinary(bin);

	setBinary(bin);
}

QInt::QInt() : Number()
{}

QInt::QInt(const string& s, int base)
{
	if (base == 2)
		setBinary(s);
	else if (base == 16)
		setHex(s);
	else if (base == 10)
		setDec(s);
}

QInt::QInt(const QInt & other)
{
	for (int i = 0; i < INTS_IN_NUMBER; i++)
		m_number[i] = other.m_number[i];
}

bool QInt::operator!=(const QInt & other) const
{
	return !(*this == other);
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
	return other < (*this);
}

bool QInt::operator<(const QInt &other) const
{
	bool thisHasSign = this->getBit(BITS_IN_NUMBER - 1) == 1 ? true : false;
	bool otherHasSign = other.getBit(BITS_IN_NUMBER - 1) == 1 ? true : false;

	if (!thisHasSign && otherHasSign)
		return false;
	if (thisHasSign && !otherHasSign)
		return true;
	if (thisHasSign && otherHasSign)
	{
		QInt zero("0", 10);
		return (zero - other) < (zero - (*this));
	}

	for (int i = BITS_IN_NUMBER - 1; i >= 0; i--) {
		if (this->getBit(i) > other.getBit(i))
			return false;
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

QInt QInt::operator>>(const int d) const
{
	// left shift
	QInt result;
	for (int i = 0; i < BITS_IN_NUMBER; i++) {
		if (getBit(BITS_IN_NUMBER - i - 1) == 1)
			result.setBit(BITS_IN_NUMBER - i - d - 1);
	}
	return result;
}

QInt QInt::operator<<(const int d) const
{
	// right shift
	QInt result;
	for (int i = BITS_IN_NUMBER - d - 1; i >= 0; i--) {
		if (getBit(i) == 1)
			result.setBit(i + d);
	}
	return result;
}

QInt QInt::rol(const int d) const
{
	// left rotation
	return (*this) << d | (*this) >> (BITS_IN_NUMBER - d);
}

QInt QInt::ror(const int d) const
{
	// right rotation
	return (*this) >> d | (*this) << (BITS_IN_NUMBER - d);
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
	string bin = binaryString.c_str() + 1;
	for (int i = bin.length(); i < BITS_IN_NUMBER; i++)
		bin = '0' + bin;
	return to2sComplement(bin);
}

void ScanQInt(QInt& x)
{
	string n;
	getline(cin, n);
	x = QInt(n, 10);
}

void PrintQInt(const QInt & x)
{
	if (x == QInt("0", 10))
	{
		cout << "0";
		return;
	}
	string number = "0";
	if (x.getBit(BITS_IN_NUMBER - 1) == 1)
	{
		number = calculate2power(BITS_IN_NUMBER - 1);
		number = '-' + number;
	}
	for (int i = 0; i < BITS_IN_NUMBER - 1; i++) 
		if (x.getBit(i) == 1)
			number = add(number, calculate2power(i));

	while (number[0] == '0')
		number = number.c_str() + 1;
	while (number[0] == '-' && number[1] == '0')
	{
		number = number.c_str() + 2;
		number = '-' + number;
	}

	cout << number;
}

char *DecToHex(const QInt& x)
{
	bool *bin = DecToBin(x);
	return BinToHex(bin);
}

QInt BinToDec(bool * bit)
{
	QInt result;
	for (int i = 0; i < BITS_IN_NUMBER; i++) 
		if (bit[i])
			result.setBit(BITS_IN_NUMBER - 1 - i);
	return result;
}

QInt QInt::operator+(const QInt &other) const
{
	QInt result;
	int sum;
	int carry = 0;
	for (int i = 0; i < BITS_IN_NUMBER; i++) {
		sum = this->getBit(i) + other.getBit(i) + carry;
		carry = (sum > 1) ? 1 : 0;
		sum %= 2;
		if (sum == 1)
			result.setBit(i);
	}

	QInt zero("0", 10);
	if (((*this) < zero && other < zero && result > zero) || 
		((*this)  > zero && other > zero && result < zero))
		cout << "Overflow!!!\n";

	return result;
}

QInt QInt::operator-(const QInt & other) const
{
	QInt negativeOther = ~other;
	QInt one("1", 2);
	negativeOther = negativeOther + one;
	return (*this) + negativeOther;
}

QInt QInt::operator*(const QInt & other) const
{
	QInt zero("0", 10);

	if (*this == zero || other == zero)
		return zero;
	if (*this < zero && other > zero)
		return zero - (zero - (*this)) * other;
	if (*this > zero && other < zero)
		return zero - (zero - other) * (*this);
	if (*this < zero && other < zero)
		return (zero - other) * (zero - *this);

	QInt result; 

	for (int i = 0; i < BITS_IN_NUMBER; i++)
		if (getBit(i) == 1)
			result = result + (other << i);

	return result;
}

QInt QInt::operator/(const QInt & other) const
{
	QInt zero("0", 10);

	if (other == zero)
	{
		cout << "DIVIDED BY 0\n";
		return zero;
	}
	if (*this == zero)
		return zero;
	if (*this < zero && other > zero)
		return zero - (zero - (*this)) / other;
	if (*this > zero && other < zero)
		return zero - (zero - other) / (*this);
	if (*this < zero && other < zero)
		return (zero - other) / (zero - *this);

	QInt result = *this;
	QInt remainder = zero;

	for (int i = 0; i < BITS_IN_NUMBER; i++)
	{
		remainder = remainder << 1;                  //
		if (result.getBit(BITS_IN_NUMBER - 1) == 1)  //    [remainder, result] <<= 1
			remainder.setBit(0);                     //
		result = result << 1;                        //

		remainder = remainder - other;
		if (remainder < zero)
			remainder = remainder + other;
		else 
			result.setBit(0);
	}
	return result;
}

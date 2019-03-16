#include "Number.h"
#include <algorithm>

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

string mul10(const string &n)
{
	if (n[0] == '-')
		return '-' + mul10(n.c_str() + 1);

	string result = n;

	int len = n.length();
	int i = len - 1;
	for (; i >= 0; i--) {
		if (n[i] == '.') {
			swap(result[i], result[i + 1]);
			break;
		}
	}
	if (i == -1)
		result += '0';
	if (result[len - 1] == '.')
		result = result.substr(0, len - 1);
	if (result[0] == '0')
		result = result.c_str() + 1;
	return result;
}

string div10(const string &n)
{
	if (n == "0")
		return n;
	if (n[0] == '-')
		return '-' + div10(n.c_str() + 1);

	string result = n;

	int len = n.length();
	int i = len - 1;
	for (; i >= 0; i--) {
		if (n[i] == '.') {
			swap(result[i], result[i - 1]);
			break;
		}
	}
	if (i == -1)
	{
		result += '.';
		swap(result[len], result[len - 1]);
	}
	if (result[0] == '.')
		result = '0' + result;
	if (result[len] == '0')
		result = result.substr(0, len - 1);

	return result;
}

string add(const string & n1, const string & n2)
{
	if (n1[0] == '-' && n2[0] != '-')
		return sub(n2, n1.c_str() + 1);
	if (n1[0] != '-' && n2[0] == '-')
		return sub(n1, n2.c_str() + 1);
	if (n1[0] == '-' && n2[0] == '-')
		return '-' + add(n1.c_str() + 1, n2.c_str() + 1);

	string result;
	string number1 = n1;
	string number2 = n2;

	int len1 = n1.length();
	int len2 = n2.length();

	// find the point position in n1
	int point_position1 = n1.find('.');
	if (point_position1 == -1)
		point_position1 = len1;

	// find the point position in n2
	int point_position2 = n2.find('.');
	if (point_position2 == -1)
		point_position2 = len2;

	if (point_position1 != len1 || point_position2 != len2)
	{
		int digitsAfterPoint1 = len1 - point_position1 - 1;
		int digitsAfterPoint2 = len2 - point_position2 - 1;
		// find the point position after calculation 
		int point_position = (digitsAfterPoint1 > digitsAfterPoint2) ? digitsAfterPoint1 : digitsAfterPoint2;
		for (int i = 0; i < point_position; i++)
		{
			number1 = mul10(number1);
			number2 = mul10(number2);
		}
		result = add(number1, number2);
		for (int i = 0; i < point_position; i++)
			result = div10(result);
		return result;
	}

	int carry = 0;
	int sum;

	while (true) {
		if (len1 > 0 && len2 > 0)
			sum = (n1[len1-- - 1] - '0') + (n2[len2-- - 1] - '0') + carry;
		else if (len1 > 0 && len2 <= 0)
			sum = (n1[len1-- - 1] - '0') + carry;
		else if (len1 <= 0 && len2 > 0)
			sum = (n2[len2-- - 1] - '0') + carry;
		else
			break;

		carry = (sum >= 10) ? 1 : 0;
		sum -= carry * 10;

		result = (char)(sum + '0') + result;
	}
	if (carry != 0)
		result = (char)(carry + '0') + result;

	return result;
}

int compare(const string &n1, const string &n2)
{
	if (n1 == n2)
		return 0;
	if (n1[0] == '-' && n2[0] == '-')
		return compare(n2.c_str() + 1, n1.c_str() + 1);
	if (n1[0] != '-' && n2[0] == '-')
		return 1;
	if (n1[0] == '-' && n2[0] != '-')
		return -1;

	int len1 = n1.length();
	int len2 = n2.length();

	if (len1 > len2)
		return 1;
	if (len1 < len2)
		return -1;
	for (int i = 0; i < len1; i++)
	{
		if (n1[i] > n2[i])
			return 1;
		if (n1[i] < n2[i])
			return -1;
	}
	return 0;
}

string sub(const string &n1, const string &n2)
{
	if (n1[0] == '-' && n2[0] == '-')
		return sub(n2.c_str() + 1, n1.c_str() + 1);
	if (n1[0] != '-' && n2[0] == '-')
		return add(n1, n2.c_str() + 1);
	if (n1[0] == '-' && n2[0] != '-')
		return add(n1, '-' + n2);
	if (compare(n1, n2) < 0)
		return '-' + sub(n2, n1);
	string result;
	string number1 = n1;
	string number2 = n2;

	int len1 = n1.length();
	int len2 = n2.length();

	// find the point position in n1
	int point_position1 = n1.find('.');
	if (point_position1 == -1)
		point_position1 = len1;

	// find the point position in n2
	int point_position2 = n2.find('.');
	if (point_position2 == -1)
		point_position2 = len2;

	if (point_position1 != len1 || point_position2 != len2)
	{
		int digitsAfterPoint1 = len1 - point_position1 - 1;
		int digitsAfterPoint2 = len2 - point_position2 - 1;
		// find the point position after calculation 
		int point_position = (digitsAfterPoint1 > digitsAfterPoint2) ? digitsAfterPoint1 : digitsAfterPoint2;
		for (int i = 0; i < point_position; i++)
		{
			number1 = mul10(number1);
			number2 = mul10(number2);
		}
		result = sub(number1, number2);
		for (int i = 0; i < point_position; i++)
			result = div10(result);
		return result;
	}

	int diff;
	int carry = 0;

	while (true) {
		if (len1 > 0 && len2 > 0)
			diff = (n1[len1-- - 1] - '0') - (n2[len2-- - 1] - '0') - carry + 10;
		else if (len1 > 0 && len2 <= 0)
			diff = (n1[len1-- - 1] - '0') - carry + 10;
		else if (len1 <= 0 && len2 > 0)
			diff = (n2[len2-- - 1] - '0') - carry + 10;
		else
			break;

		carry = (diff < 10) ? 1 : 0;
		diff %= 10;

		result = (char)(diff + '0') + result;
	}
	return result;
}

string mul(const string & n1, const string & n2)
{
	if (n1[0] == '-' && n2[0] == '-')
		return mul(n1.c_str() + 1, n2.c_str() + 1);
	if (n1[0] != '-' && n2[0] == '-')
		return '-' + mul(n1, n2.c_str() + 1);
	if (n1[0] == '-' && n2[0] != '-')
		return '-' + mul(n2, n1.c_str() + 1);

	string result("0");

	int len1 = n1.length();
	int len2 = n2.length();

	for (int i = len2 - 1; i >= 0; i--)
	{
		int product;
		int carry = 0;

		string sum;
		for (int j = len1 - 1; j >= 0; j--)
		{
			product = (n1[j] - '0') * (n2[i] - '0') + carry;
			carry = (product >= 10) ? product / 10 : 0;
			product %= 10;
			sum = (char)(product + '0') + sum;
		}
		if (carry != 0)
			sum = (char)(carry + '0') + sum;
		for (int k = len2 - 1; k > i; k--)
			sum += '0';
		result = add(result, sum);
	}

	return result;
}

string mul2(const string & n)
{
	if (n[0] == '-')
		return '-' + mul2(n.c_str() + 1);

	string result = n;
	int len = n.length();

	// find the point position in n
	int point_position = n.find('.');

	if (point_position != -1) {
		// erase the point from n
		result.erase(result.begin() + point_position);

		// find the point position after calculation 
		point_position = len - 1 - point_position;
	}
	else
		return mul(result, "2");

	if (result[0] == '0')
		result = result.c_str() + 1;
	result = mul(result, "2");
	for (int i = 0; i < point_position; i++)
		result = div10(result);

	return result;
}

string div2(const string &n)
{
	if (n[0] == '-')
		return '-' + div2(n.c_str() + 1);

	int len = n.length();

	string result = n;

	// find the point position in n
	int point_position = n.find('.');

	// erase the point from n
	if (point_position != -1)
		result.erase(result.begin() + point_position);

	// find the point position after calculation 
	point_position = (point_position == -1) ? 1 : len - point_position;

	// n/2 == (n*5)/10
	if (result[0] == '0')
		result = result.c_str() + 1;
	result = mul(result, "5");
	for (int i = 0; i < point_position; i++)
		result = div10(result);

	return result;
}

string calculate2power(const int exp) // return 2^exp (string)
{
	if (exp == 0)
		return "1";
	string result = "1";
	if (exp > 0)
		for (int i = 0; i < exp; i++)
			result = mul2(result);
	else if (exp < 0)
		for (int i = -exp; i > 0; i--)
			result = div2(result);
	return result;
}

string DecToBin(const string & dec)
{
	if (dec[0] == '-')
		return '-' + DecToBin(dec.c_str() + 1);

	string result;
	int len = dec.length();

	int point_position = dec.find('.');
	if (point_position == -1)
		point_position = len;

	string n = dec.substr(0, point_position);
	while (n != "0")
	{
		if ((n[n.length() - 1] - '0') % 2 != 0)
		{
			result += '1';
			n = sub(n, "1");
		}
		else result += '0';
		n = div2(n);
	}

	reverse(result.begin(), result.end());
	if (result == "")
		result = "0";

	n = '0' + (string)(dec.c_str() + point_position);
	if (point_position != len)
	{
		result += '.';
		int count = 0;
		do
		{
			n = mul2(n);
			result += n[0];
		} while (n != "1" && count != BITS_IN_FRACTION);
	}
	return result;
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

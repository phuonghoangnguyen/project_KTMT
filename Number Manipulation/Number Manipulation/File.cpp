#include "File.h"
#include "QInt.h"
#include "Qfloat.h"

string calculate(const string &n1, const string &n2, const string &opt, int base, int base2)
{
	string result;
	QInt ans;
	bool isQfloat = false;
	if (opt == "+")
	{
		QInt temp1(n1, base);
		QInt temp2(n2, base);
		ans = temp1 + temp2;
	}
	else if (opt == "-")
	{
		QInt temp1(n1, base);
		QInt temp2(n2, base);
		ans = temp1 - temp2;
	}
	else if (opt == "*")
	{
		QInt temp1(n1, base);
		QInt temp2(n2, base);
		ans = temp1 * temp2;
	}
	else if (opt == "/")
	{
		QInt temp1(n1, base);
		QInt temp2(n2, base);
		ans = temp1 / temp2;
	}
	else if (opt == ">")
	{
		QInt temp1(n1, base);
		QInt temp2(n2, base);
		if (temp1 > temp2)
			return "TRUE";
		return "FALSE";
	}
	else if (opt == "<")
	{
		QInt temp1(n1, base);
		QInt temp2(n2, base);
		if (temp1 < temp2)
			return "TRUE";
		return "FALSE";
	}
	else if (opt == ">=")
	{
		QInt temp1(n1, base);
		QInt temp2(n2, base);
		if (temp1 >= temp2)
			return "TRUE";
		return "FALSE";
	}
	else if (opt == "<=")
	{
		QInt temp1(n1, base);
		QInt temp2(n2, base);
		if (temp1 <= temp2)
			return "TRUE";
		return "FALSE";
	}
	else if (opt == "==")
	{
		QInt temp1(n1, base);
		QInt temp2(n2, base);
		if (temp1 == temp2)
			return "TRUE";
		return "FALSE";
	}
	else if (opt == "~")
	{
		QInt temp2(n2, base);
		ans = ~temp2;
	}
	else if (opt == "&")
	{
		QInt temp1(n1, base);
		QInt temp2(n2, base);
		ans = temp1 & temp2;
	}
	else if (opt == "|")
	{
		QInt temp1(n1, base);
		QInt temp2(n2, base);
		ans = temp1 | temp2;
	}
	else if (opt == "^")
	{
		QInt temp1(n1, base);
		QInt temp2(n2, base);
		ans = temp1 ^ temp2;
	}
	else if (opt == ">>")
	{
		QInt temp1(n1, base);
		int temp2 = 0;
		for (char digit : n2)
		{
			temp2 *= 10;
			temp2 += digit - '0';
		}
		ans = temp1 >> temp2;
	}
	else if (opt == "<<")
	{
		QInt temp1(n1, base);
		int temp2 = 0;
		for (char digit : n2)
		{
			temp2 *= 10;
			temp2 += digit - '0';
		}
		ans = temp1 << temp2;
	}
	else if (opt == "rol")
	{
		QInt temp1(n1, base);
		int temp2 = 0;
		for (char digit : n2)
		{
			temp2 *= 10;
			temp2 += digit - '0';
		}
		ans = temp1.rol(temp2);
	}
	else if (opt == "ror")
	{
		QInt temp1(n1, base);
		int temp2 = 0;
		for (char digit : n2)
		{
			temp2 *= 10;
			temp2 += digit - '0';
		}
		ans = temp1.ror(temp2);
	}
	else if (opt == "")
	{
		if (n2.length() == BITS_IN_NUMBER || n2.find('.') != -1)
		{
			Qfloat temp(n2, base);
			if (base2 == 10)
			{
				int expBits = 0;
				for (int i = 0; i < BITS_IN_EXPONENT; i++) {
					if (temp.getBit(BITS_IN_NUMBER - 1 - BITS_IN_EXPONENT + i) == 1)
						setBit(expBits, i);
				}
				expBits -= pow(2, BITS_IN_EXPONENT - 1) - 1;

				for (int i = 0; i < BITS_IN_FRACTION; i++) {
					result = (temp.getBit(i) == 1) ? ('1' + result) : ('0' + result);
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
				if (temp.getBit(BITS_IN_NUMBER - 1) == 1)
					result = '-' + result;

				return result;
			}
			else
			{
				bool *bin = DecToBin(temp);
				for (int i = 0; i < BITS_IN_NUMBER; i++) {
					if (bin[i])
						result += '1';
					else result += '0';
				}
				return result;
			}
		}
		ans = QInt(n2, base);
		base = base2;
	}

	if (base == 10)
	{
		if (ans == QInt("0", 10))
			return "0";
		result = "0";
		if (ans.getBit(BITS_IN_NUMBER - 1) == 1)
		{
			result = calculate2power(BITS_IN_NUMBER - 1);
			result = '-' + result;
		}
		for (int i = 0; i < BITS_IN_NUMBER - 1; i++)
			if (ans.getBit(i) == 1)
				result = add(result, calculate2power(i));

		while (result[0] == '0')
			result = result.c_str() + 1;
		while (result[0] == '-' && result[1] == '0')
		{
			result = result.c_str() + 2;
			result = '-' + result;
		}
	}
	else if (base == 2)
	{
		bool *bin = DecToBin(ans);
		for (int i = 0; i < BITS_IN_NUMBER; i++) {
			if (bin[i])
				result += '1';
			else result += '0';
		}
	}
	else if (base == 16)
		result = DecToHex(ans);

	return result;
}

void fileManipulate(const string &input, const string &output)
{
	ifstream fileIn(input);
	ofstream fileOut(output);
	string equation;
	while (getline(fileIn, equation)) {
		int base = 0;
		int i = 0;
		for (; equation[i] != ' '; i++)
		{
			base *= 10;
			base += equation[i] - '0';
		}
		i++;

		equation = equation.c_str() + i;

		string n1;
		i = 0;
		while ((equation[i] <= '9' && equation[i] >= '0')
			|| (equation[i] <= 'F' && equation[i] >= 'A')
			|| equation[i] == '-')
			n1 += equation[i++];
		
		if (n1 != "")
			equation = equation.c_str() + i + 1;

		int base2 = 0;
		string opt;
		i = 0;
		if (((equation[i] <= '9' && equation[i] >= '0')
			|| (equation[i] <= 'F' && equation[i] >= 'A')
			|| equation.find(' ') == -1) 
			&& equation[i] != '~')
		{
			for (char digit : n1)
			{
				base2 *= 10;
				base2 += digit - '0';
			}
		}
		else
		{
			do
				opt += equation[i++];
			while (equation[i] != ' ' && opt != "~");
		}

		if (opt != "")
			equation = equation.c_str() + i + 1;

		string n2 = equation;

		fileOut << calculate(n1, n2, opt, base, base2) << endl;
	}
	_fcloseall();
}


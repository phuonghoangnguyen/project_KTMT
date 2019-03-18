#pragma once
#include "Number.h"
#include <iostream>

#define BASE int(pow(10,9))

using namespace std;

class QInt : public Number
{
private:
	void setBinary(const string&);
	void setHex(const string&);
	void setDec(const string&);
public:
	QInt();
	QInt(const string&, int base);
	QInt(const QInt&);
	bool operator==(const QInt &) const;
	bool operator>(const QInt &) const;
	bool operator<(const QInt &) const;
	bool operator>=(const QInt &) const;
	bool operator<=(const QInt &) const;
	void operator=(const QInt &);
	QInt operator~() const; // not
	QInt operator&(const QInt &) const; // and
	QInt operator|(const QInt &) const; // or
	QInt operator^(const QInt &) const; // xor
	QInt operator>>(const int) const; // left shift
	QInt operator<<(const int) const; // right shift
	QInt rol(const int) const; // left rotation
	QInt ror(const int) const; // right rotation
	QInt operator+(const QInt &) const; // +
	QInt operator-(const QInt &) const; // -
	QInt operator*(const QInt &) const; // *
	QInt operator/(const QInt &) const; // /
};

void ScanQInt(QInt& x);
void PrintQInt(const QInt& x);
char *DecToHex(const QInt&);
QInt BinToDec(bool *bit);
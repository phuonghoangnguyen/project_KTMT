#pragma once
#include "Number.h"
#include <iostream>

using namespace std;

class QInt : public Number 
{
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
	//QInt operator>>(const int); // left shift
	QInt operator<<(const int); // right shift
};

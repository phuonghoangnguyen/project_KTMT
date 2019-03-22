#pragma once
#include "Number.h"
#include <iostream>

using namespace std;

class Qfloat : public Number
{	
private:
public:
	Qfloat();
	void setBinary(const string&);
	Qfloat(const string&, int base);
	Qfloat(const Qfloat&);
};

void ScanQfloat(Qfloat& x);
void PrintQfloat(const Qfloat &x);
Qfloat binToDec(bool *bit);
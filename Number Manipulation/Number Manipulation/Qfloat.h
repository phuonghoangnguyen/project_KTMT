#pragma once
#include "Number.h"
#include <iostream>

using namespace std;

#define BITS_IN_EXPONENT 15
#define BITS_IN_FRACTION 112

class Qfloat : public Number
{	
public:
	Qfloat();
	Qfloat(const string&);
	Qfloat(const Qfloat&);
};


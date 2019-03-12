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
	Qfloat(const string&);
	Qfloat(const Qfloat&);
};


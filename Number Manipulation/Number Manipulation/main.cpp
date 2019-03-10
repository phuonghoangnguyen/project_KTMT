#include "QFloat.h"
#include "QInt.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	QInt a;
	a.setBit(45);
	QInt b = a << 0;
	bool *bin = DecToBin(b);
	int count = 0;
	bool start = false;
	for (int i = 0; i < BITS_IN_NUMBER; i++) {
		if (start)
			count++;
		if (bin[i]) {
			start = true;
		}
		/*if (bin[i])
			cout << 1;
		else cout << 0;*/
	}
	cout << count;
	return 0;
}

// >>
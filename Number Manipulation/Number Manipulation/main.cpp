#include "QFloat.h"
#include "QInt.h"
#include <iostream>

using namespace std;

int main() {
	QInt a("ABF96CDE123", 16);
	char *hex = DecToHex(a);
	bool *bin = DecToBin(a);
	for (int i = 0; i < BITS_IN_NUMBER; i++) {
		if (bin[i])
			cout << 1;
		else cout << 0;
	}
	cout << endl;
	cout << hex << endl;
	delete[] bin;
	delete[] hex;
	return 0;
}
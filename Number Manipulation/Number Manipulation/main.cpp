#include "QFloat.h"
#include "QInt.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	QInt a;
	ScanQInt(a);
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
#include "QFloat.h"
#include "QInt.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	/*QInt a;
	ScanQInt(a);

	bool *bin = DecToBin(a);
	cout << "BIN: ";
	for (int i = 0; i < BITS_IN_NUMBER; i++) {
		if (bin[i])
			cout << 1;
		else cout << 0;
	}
	cout << endl;

	char *hex = DecToHex(a);
	cout << "HEX: " << hex << endl;

	cout << "DEC: ";
	PrintQInt(a);
	cout << endl;

	delete[] bin;
	delete[] hex;*/

	Qfloat a;
	ScanQfloat(a);

	bool *bin = DecToBin(a);
	cout << "BIN: ";
	for (int i = 0; i < BITS_IN_NUMBER; i++) {
		if (i == 1 || i == 16)
			cout << " ";
		if (bin[i])
			cout << 1;
		else cout << 0;
	}
	cout << endl;

	cout << "DEC: ";
	PrintQfloat(a);
	cout << endl;

	delete[] bin;

	return 0;
}
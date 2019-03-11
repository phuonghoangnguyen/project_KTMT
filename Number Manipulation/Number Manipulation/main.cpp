#include "QFloat.h"
#include "QInt.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
	QInt a("1111111001001", 2);
	char *hex = DecToHex(a);
	/*for (int i = 0; i < BITS_IN_NUMBER; i++) {
		if (bin[i])
			cout << 1;
		else cout << 0;
	}*/
	cout << hex;
	//delete[] bin;
	delete[] hex;
	return 0;
}
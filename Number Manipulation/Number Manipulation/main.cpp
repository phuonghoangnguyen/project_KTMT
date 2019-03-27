#include "Menu.h"
#include "File.h"

using namespace std;

const int N = 7;
string Menu[N] = {
"========CALCULATOR========",
"\t1.CALCULATE",
"\t2.COMPARE",
"\t3.BITWISE",
"\t4.CONVERT",
"\t5.README",
"\t0.EXIT" };

int main(int argc, char* argv[])
{
	if (argc == 3)
		fileManipulate(argv[1], argv[2]);
	if (argc == 1)
	{
	Menu:
		_flushall();
		int i = menu(Menu, N);
		switch (i)
		{
		case 0:
			cout << "CALCULATOR IS SHUTTING DOWN" << endl;
			return 0;
		case 1:
		{
			while (1)
			{
				clrscr();
				int base;
				cout << "Enter the Arithmetic Base you want to calculate on: ";
				cin >> base;
				getchar();
				string equa, op1, op2; char oprtor;
				getline(cin, equa);
				int i = 0;
				while (equa[i] != ' ')
				{
					op1 += equa[i];
					i++;
				}
				oprtor = equa[++i];
				i++;
				while (equa[i] != '\0')
				{
					if (equa[i] != ' ')
						op2 += equa[i];
					i++;
				}
				switch (base)
				{
				case 2:
				{
					QInt oper1(op1, 2), oper2(op2, 2);
					QInt ketqua;
					try {
						ketqua = Calculator(oper1, oper2, oprtor);
					}
					catch (std::logic_error const& e)
					{
						std::cerr << "Error: " << e.what();
						return EXIT_FAILURE;
					}
					PrintBin(ketqua);
					break;
				}
				case 10:
				{
					QInt oper1(op1, 10), oper2(op2, 10);
					QInt ketqua;
					try
					{
						ketqua = Calculator(oper1, oper2, oprtor);
					}
					catch (std::logic_error const & e) {
						std::cerr << "Error: " << e.what();
						return EXIT_FAILURE;
					}
					PrintQInt(ketqua);
					break;
				}
				case 16:
				{
					QInt oper1(op1, 16), oper2(op2, 16);
					QInt ketqua;
					try {
						ketqua = Calculator(oper1, oper2, oprtor);
					}
					catch (std::logic_error const & e) {
						std::cerr << "Error: " << e.what();
						return EXIT_FAILURE;
					}
					PrintHex(ketqua);
					break;
				}
				default:
					cout << "UNSUPPORTED ERROR!" << endl;
				}
				char flag;
				cout << endl << "Do you want to continue? (Y/N) ";
				cin >> flag;
				if (flag == 'N' || flag == 'n')
					goto Menu;
			}
		}

		case 2:
		{
			while (1)
			{
				// mac dinh nhap he 10
				clrscr();
				string equa, op1, op2; char operand;
				getline(cin, equa);
				int i = 0;
				while (equa[i] != ' ')
				{
					op1 += equa[i];
					i++;
				}
				operand = equa[++i];
				i++;
				while (equa[i] != '\0')
				{
					if (equa[i] != ' ')
						op2 += equa[i];
					i++;
				}
				QInt oper1(op1, 10), oper2(op2, 10);
				bool ketqua;
				try
				{

					switch (operand)
					{
					case '==':
					{
						ketqua = oper1 == oper2;
						break;
					}
					case '<=':
					{
						ketqua = oper1 <= oper2;
						break;
					}
					case '>=':
					{
						ketqua = oper1 >= oper2;
						break;
					}
					case '>':
					{
						ketqua = oper1 > oper2;
						break;
					}
					case '<':
					{
						ketqua = oper1 < oper2;
						break;
					}
					default:
						throw std::logic_error("unsupported error!");
					}
				}

				catch (std::logic_error const & e)
				{
					std::cerr << "Error: " << e.what();
					return EXIT_FAILURE;
				}

				// print ketqua
				if (ketqua)
					cout << "TRUE" << endl;
				else cout << "FALSE" << endl;
				char flag;
				do {
					cout << endl << "Do you want to continue? (Y/N) ";
					cin >> flag; _flushall();
					if (flag == 'Y' || flag == 'y')
						continue;
					else if (flag == 'N' || flag == 'n')
						goto Menu;
				} while (flag != 'y' && flag != 'Y' && flag != 'n' && flag != 'N');

				getchar();
			}
		}

		case 3:
		{
			while (1)
			{
				_flushall();
				clrscr();
				string equa, op1, op2, operand = "";
				getline(cin, equa);
				int i = 0;
				while (equa[i] != ' ')
				{
					op1 += equa[i];
					i++;
				}
				i++;
				while (equa[i] != ' ' && equa[i] != '\0')
				{
					operand += equa[i];
					i++;
				}
				if (operand == "~" || operand == "<<" || operand == ">>" || operand == "rol" || operand == "ror")
				{
					if (operand == "~")
					{
						QInt oper(op1, 10);
						PrintQInt(oper.operator~());
					}
					else
					{
						QInt oper(op1, 10);
						do {
							i++;
							op2 += equa[i];
						} while (equa[i] != '\0');

						int numb_shift = StoN(op2);
						if (operand == ">>") PrintQInt(oper >> numb_shift);
						else if (operand == "<<") PrintQInt(oper << numb_shift);
						else if (operand == "rol") PrintQInt(oper.rol(numb_shift));
						else PrintQInt(oper.ror(numb_shift));
					}
					goto Option;
				}
				else {
					while (equa[i] != '\0')
					{
						if (equa[i] != ' ')
							op2 += equa[i];
						i++;
					}
					QInt oper1(op1, 10), oper2(op2, 10);
					try {
						if (operand == "^")
							PrintQInt(oper1 ^ oper2);
						else if (operand == "&")
							PrintQInt(oper1 & oper2);
						else if (operand == "|")
							PrintQInt(oper1 | oper2);
						else
							throw std::logic_error("unsupported error!");
					}
					catch (std::logic_error const & e)
					{
						std::cerr << "Error: " << e.what();
						return EXIT_FAILURE;
					}
				}

			Option:
				char flag;
				do {
					cout << endl << "Do you want to continue? (Y/N) ";
					cin >> flag; _flushall();
					if (flag == 'Y' || flag == 'y')
						continue;
					else if (flag == 'N' || flag == 'n')
						goto Menu;
				} while (flag != 'y' && flag != 'Y' && flag != 'n' && flag != 'N');

				getchar();
			}
		}
		case 4:
		{
			while (1)
			{
				cout << "1. INTEGER " << endl << "2. FLOATING POINT " << endl;
				int choices; cin >> choices;
				int base_s, base_des;
				cout << "Choose the source base: ";
				cin >> base_s;
				cout << "Choose the destination base: ";
				cin >> base_des;
				_flushall(); getchar();
				try {
					if (choices == 1)
					{
						if (base_s == 2)
						{
							string temp;
							getline(cin, temp);
							QInt a(temp, 2);
							if (base_des == 2)
								PrintBin(a);
							else if (base_des == 10)
								PrintQInt(a);
							else if (base_des == 16)
								PrintHex(a);
							else throw std::logic_error("unsupported error!");
						}
						else if (base_s == 10)
						{
							QInt a; ScanQInt(a);
							if (base_des == 2)
								PrintBin(a);
							else if (base_des == 10)
								PrintQInt(a);
							else if (base_des == 16)
								PrintHex(a);
							else throw std::logic_error("unsupported error!");
						}
						else throw std::logic_error("unsupported error!");
					}
					else if (choices == 2)
					{
						if (base_s == 2)
						{
							string temp; getline(cin, temp);
							Qfloat f(temp, 2);
							if (base_des == 10)
								PrintQfloat(f);
							if (base_des == 2)
								PrintBin(f);
						}
						else if (base_s == 10)
						{
							Qfloat f;
							ScanQfloat(f);
							if (base_des == 10)
								PrintQfloat(f);
							if (base_des == 2)
								PrintBin(f);
						}
						else throw std::logic_error("unsupported error!");

					}
					else throw std::logic_error("unsupported error!");
				}

				catch (std::logic_error const & e)
				{
					std::cerr << "Error: " << e.what();
					goto Menu;
				}
				char flag;
				do {
					cout << endl << "Do you want to continue? (Y/N) ";
					cin >> flag; _flushall();
					if (flag == 'Y' || flag == 'y')
						continue;
					else if (flag == 'N' || flag == 'n')
						goto Menu;
				} while (flag != 'y' && flag != 'Y' && flag != 'n' && flag != 'N');
				getchar();
			}

		}

		case 5:
		{
			cout << "-- Input pattern: operand1 operator operand2" << endl << "    for two-operand equations" << endl;
			cout << "-- Input pattern: operand operator " << endl << "    for one-operand equations" << endl;
			cout << "-- Default Input: Decimal" << endl;
			cout << "...press Enter to go back to menu... " << endl;

			if (getchar()) goto Menu;
		}
		}
	}
	else
	{
		cout << "Usage:\n";
		cout << "<1712681_1712627_1712644_1712332.exe> <input.txt> <output.txt>\n";
		cout << "Or:\n<1712681_1712627_1712644_1712332.exe>";
	}
}
#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include <sstream>
#include <exception>
#include <Windows.h>
#include "console.h"
#include "Qfloat.h"
#include "QInt.h"

using namespace std;

#define BACKGROUND 11
#define TEXTCOLOR 15
enum BUTTON { up, down, enter, esc, backspace, Continue, Home, Delete }; // Buttons 
BUTTON key(int a); // return the button associated with the int a  
int menu(string Menu[7], int n); // in cac che do trong may tinh chon bang cach nhan enter
QInt Calculator(const QInt &oper1, const QInt &oper2, char oprtor); // calculate "oper1 oprtor oper2"
int StoN(const string &s); // convert a small string of number characters to int
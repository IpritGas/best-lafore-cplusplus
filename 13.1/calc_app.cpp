// calc_app.cpp : Defines the entry point for the console application.
// Verylong Сalculator

#include "stdafx.h"
#include "verylong.h"    //заголовочный файл verylong

int main()
{
	char choise, sign;
	verylong vl_1, vl_2, vl_r;
	do
	{
		cout << "Enter the expression" << endl;
		cout << "(first variable, operator, second variable):" << endl;
		cin >> vl_1 >> sign >> vl_2;
		switch (sign)
		{
		case '+':
			vl_r = vl_1 + vl_2;
			break;
		case '-':
			vl_r = vl_1 - vl_2;
			break;
		case '*':
			vl_r = vl_1 * vl_2;
			break;
		case '/':
			vl_r = vl_1 / vl_2;
			break;
		default:
			cout << "Unknown operator!" << endl;
			exit(1);
		}
		cout << "Result: " << vl_r << endl;
		cout << "Another operation (y/n)? " << flush;
		cin >> choise;
	} while (choise != 'n');
	return 0;
}
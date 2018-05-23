#pragma once
// verylong.h
// описатель класса сверхбольших целых чисел

#include <iostream>
#include <cstring>            // для strlen() и т.п.
#include <cstdlib>            // для ltoa()

using namespace std;

const int SZ = 1000;           // максимальное число разрядов

class verylong
{
private:
	char vlstr[SZ];            // число как строка
	int vlen;                  // длина строки verylong
	verylong multdigit(const int d2) const; // прототипы скрытых функций
	verylong mult10(const verylong v) const;
	friend int bigger(const verylong v_1, const verylong v_2);
public:
	verylong() : vlen(0)       // конструктор без аргументов
	{
		vlstr[0] = '\0';
	}
	verylong(const char s[SZ]) // конструктор (1 аргумент) для строки (перевернутой)
	{
		strcpy(vlstr, s); vlen = strlen(s);
	} 
	verylong(const unsigned long n) // конструктор (1 аргумент) для long int
	{                             
		_ltoa(n, vlstr, 10);           // перевести в строку
		_strrev(vlstr);                // перевернуть ее
		vlen = strlen(vlstr);          // найти длину
	}
	void putvl() const;              // вывести число
	void getvl();       // получить число от пользователя
	verylong operator + (const verylong v) const; // сложить числа
	verylong operator - (const verylong v) const; // вычесть
	verylong operator * (const verylong v) const; // умножить
	verylong operator / (const verylong v) const; // разделить
	friend istream& operator>> (istream& stream, verylong& v);
	friend ostream& operator<< (ostream& stream, verylong& v);
};
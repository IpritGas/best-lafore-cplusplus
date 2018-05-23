#pragma once
// verylong.h
// ��������� ������ ������������ ����� �����

#include <iostream>
#include <cstring>            // ��� strlen() � �.�.
#include <cstdlib>            // ��� ltoa()

using namespace std;

const int SZ = 1000;           // ������������ ����� ��������

class verylong
{
private:
	char vlstr[SZ];            // ����� ��� ������
	int vlen;                  // ����� ������ verylong
	verylong multdigit(const int d2) const; // ��������� ������� �������
	verylong mult10(const verylong v) const;
	friend int bigger(const verylong v_1, const verylong v_2);
public:
	verylong() : vlen(0)       // ����������� ��� ����������
	{
		vlstr[0] = '\0';
	}
	verylong(const char s[SZ]) // ����������� (1 ��������) ��� ������ (������������)
	{
		strcpy(vlstr, s); vlen = strlen(s);
	} 
	verylong(const unsigned long n) // ����������� (1 ��������) ��� long int
	{                             
		_ltoa(n, vlstr, 10);           // ��������� � ������
		_strrev(vlstr);                // ����������� ��
		vlen = strlen(vlstr);          // ����� �����
	}
	void putvl() const;              // ������� �����
	void getvl();       // �������� ����� �� ������������
	verylong operator + (const verylong v) const; // ������� �����
	verylong operator - (const verylong v) const; // �������
	verylong operator * (const verylong v) const; // ��������
	verylong operator / (const verylong v) const; // ���������
	friend istream& operator>> (istream& stream, verylong& v);
	friend ostream& operator<< (ostream& stream, verylong& v);
};
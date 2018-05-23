// verylong.cpp
// ���������� ��������� ������ ���� verylong

#include "verylong.h"        // ������������ ���� ��� verylong
//---------------------------------------------------------
void verylong::putvl() const // ����� �� ����� verylong
{
	char tempstr[SZ];
	strcpy(tempstr, vlstr);        // ������� �����
	cout << _strrev(tempstr);      // ����������� ����� � ������� ��
}
//---------------------------------------------------------
void verylong::getvl()       // �������� ������������ ����� �� ������������
{
	cin >> vlstr;              // �������� ������ �� ������������
	vlen = strlen(vlstr);      // ����� �� �����
	_strrev(vlstr);            // ����������� ��
}
//---------------------------------------------------------
verylong verylong::operator+ (const verylong v) const	// ��������
{
	if ((vlstr[vlen - 1] != '-') && (v.vlstr[v.vlen - 1] == '-'))	// �������� ����� � ������� �������
	{
		char tempstr[SZ];
		strcpy(tempstr, v.vlstr);
		tempstr[v.vlen - 1] = '\0';	// ������� �����
		return (verylong(vlstr) - verylong(tempstr));	// �������� �������� ����������
	}
	if ((vlstr[vlen - 1] == '-') && (v.vlstr[v.vlen - 1] != '-'))	// �������� ����� � ������� �������
	{
		char tempstr[SZ];
		strcpy(tempstr, vlstr);
		tempstr[vlen - 1] = '\0';	// ������� �����
		return (verylong(v.vlstr) - verylong(tempstr)); // �������� �������� ����������
	}
	bool minus = false;
	if ((vlstr[vlen - 1] == '-') && (v.vlstr[v.vlen - 1] == '-')) // �������� ������������� �����
		minus = true;
	int len1 = vlen;
	int len2 = v.vlen;
	if (minus)
	{
		--len1;	// �� ��������� ������
		--len2;
	}
	int maxlen = (len1 > len2) ? len1 : len2; // ����� ����� ������� �����
	char tempstr[SZ];
	int j;
	int carry = 0;             // ���������� � 1, ���� ����� >= 10
	for (j = 0; j < maxlen; j++)  // � ��� ��� ������ �������
	{
		int d1 = (j > len1 - 1) ? 0 : vlstr[j] - '0';    //�������� ������												 
		int d2 = (j > len2 - 1) ? 0 : v.vlstr[j] - '0'; // � ���
		int digitsum = d1 + d2 + carry;  // ������� �������
		if (digitsum >= 10)				 // ���� �������, ��
		{
			digitsum -= 10; carry = 1;	// ��������� ����� �� 10 � ���������� ������� � 1
		}
		else
			carry = 0;             // ����� ������� = 0
		tempstr[j] = digitsum + '0';  // �������� ������ � ������
	}
	if (carry == 1)               // ���� ������� � �����,
		tempstr[j++] = '1';         // ��������� ����� = 1
	if (minus)
		tempstr[j++] = '-';		// �������� �����
	tempstr[j] = '\0';            // ��������� ������������ ������
	return verylong(tempstr);     // ������� ��������� verylong
}
//---------------------------------------------------------
verylong verylong::operator- (const verylong v) const	// ���������
{
	if ((vlstr[vlen - 1] != '-') && (v.vlstr[v.vlen - 1] == '-')) // ��������� �� �������������� ��������������
	{
		char tempstr[SZ];
		strcpy(tempstr, v.vlstr);
		tempstr[v.vlen - 1] = '\0';	// ������� �����
		return (verylong(vlstr) + verylong(tempstr));	// �������� ��������� ���������
	}
	if ((vlstr[vlen - 1] == '-') && (v.vlstr[v.vlen - 1] != '-')) // ��������� �� �������������� ��������������
	{
		char tempstr[SZ];
		strcpy(tempstr, vlstr);
		tempstr[v.vlen] = '-';		// ��������� �����
		tempstr[v.vlen + 1] = '\0';
		return (verylong(vlstr) + verylong(tempstr));	// �������� ��������� ��������� ������������� �����
	}
	if ((vlstr[vlen - 1] == '-') && (v.vlstr[v.vlen - 1] == '-')) // ��������� ������������� �����
	{
		char tempstr_1[SZ];
		strcpy(tempstr_1, vlstr);
		tempstr_1[vlen - 1] = '\0';	// ������� �����
		char tempstr_2[SZ];
		strcpy(tempstr_2, v.vlstr);
		tempstr_2[v.vlen - 1] = '\0';	// ������� �����	
		return (verylong(tempstr_2) - verylong(tempstr_1)); // �������� ���������� ������������� �����
	}
	if (bigger(verylong(vlstr), verylong(v.vlstr)) == -1)	// ���� ������������� ����������� ������ �����������
	{
		verylong tempvl = verylong(v.vlstr) - verylong(vlstr);	// ������ �� �������
		tempvl.vlstr[tempvl.vlen] = '-';	// ��������� �����
		tempvl.vlstr[tempvl.vlen + 1] = '\0';
		return tempvl;
	}
	char tempstr[SZ];
	int j;
	int carry = 0;             // ���������� � -1, ���� �������� < 0
	for (j = 0; j < vlen; j++)  // � ��� ��� ������ �������
	{
		int d1 = (j > vlen - 1) ? 0 : vlstr[j] - '0';    //�������� ������												 
		int d2 = (j > v.vlen - 1) ? 0 : v.vlstr[j] - '0'; // � ���
		int digitsub = d1 - d2 + carry;  // ������� �������
		if (digitsub < 0)				 // ���� �������, ��
		{
			digitsub += 10; carry = -1;	// ��������� ����� �� 10 � ���������� ������� � -1
		}
		else
			carry = 0;             // ����� ������� = 0
		tempstr[j] = digitsub + '0';  // �������� ������ � ������
	}
	tempstr[j--] = '\0';            // ��������� ������������ ������
	for (j; j > 0; j--)		// ������ ������ ����
		if (tempstr[j] == '0')
			tempstr[j] = '\0';
		else
			break;
	return verylong(tempstr);     // ������� ��������� verylong
}
//---------------------------------------------------------
verylong verylong::operator* (const verylong v) const	//��������� ������������ �����
{
	bool minus = false;
	if (((vlstr[vlen - 1] != '-') && (v.vlstr[v.vlen - 1] == '-')) ||	// ��������� ����� � ������� �������
		((vlstr[vlen - 1] == '-') && (v.vlstr[v.vlen - 1] != '-')))
		minus = true;
	verylong pprod;            // ������������ ������ �������
	verylong tempsum;          // ������� �����
	int len = v.vlen;
	if (v.vlstr[v.vlen - 1] == '-')
		--len;		// �� ��������� ������
	for (int j = 0; j < len; j++) // ��� ������� ������� ���������
	{
		int digit = v.vlstr[j] - '0'; // �������� ������
		pprod = multdigit(digit);   // �������� ������� �� ����
		for (int k = 0; k < j; k++)
			pprod = mult10(pprod);     // �������� ��������� �� ������� 10-��
		tempsum = tempsum + pprod;  // ��������� ������������ � ������� �����							
	}
	verylong temp(tempsum);
	if (minus)
	{
		temp.vlstr[temp.vlen] = '-';		// �������� �����
		temp.vlstr[temp.vlen + 1] = '\0';   // ��������� ������������ ������
	}
	return temp;               // ������� ��������� verylong
}
//---------------------------------------------------------
verylong verylong::mult10(const verylong v) const // ��������� ��������� �� 10		  
{
	char tempstr[SZ];
	int len = v.vlen;
	if (v.vlstr[v.vlen - 1] == '-')
		--len;		// �� ��������� ������
	for (int j = len - 1; j >= 0; j--) // ���������� �� ���� ������ ����
		tempstr[j + 1] = v.vlstr[j];
	tempstr[0] = '0';                // �������� ����� ������� ������
	tempstr[len + 1] = '\0';        // ��������� ������������ ������
	return verylong(tempstr);        // ������� ���������
}
//---------------------------------------------------------
verylong verylong::multdigit(const int d2) const   // ��������� ����� �� �������� (�����)
{
	char tempstr[SZ];
	int j, carry = 0;
	int len = vlen;
	if (vlstr[vlen - 1] == '-')
		--len;		// �� ��������� ������
	for (j = 0; j < len; j++)    // ��� ������� ������� � ���� ������������
	{
		int d1 = vlstr[j] - '0';   // �������� �������� �������
		int digitprod = d1 * d2; // �������� �� �����
		digitprod += carry;      // �������� ������ �������
		if (digitprod >= 10)    // ���� ������ ����� �������,
		{
			carry = digitprod / 10;  // �������� ��������� �������� �������� �������
			digitprod -= carry * 10; // ���������� - ��������
		}
		else
			carry = 0;             // ����� ������� = 0
		tempstr[j] = digitprod + '0'; // �������� ������ � ������
	}
	if (carry != 0)             // ���� �� ����� �������,
		tempstr[j++] = carry + '0';   // ��� ��������� ������
	tempstr[j] = '\0';            // ��������� ������������
	return verylong(tempstr);     // ������� ������������ �����
}
//---------------------------------------------------------
verylong verylong::operator/ (const verylong v) const // �������
{
	bool minus = false;
	if (((vlstr[vlen - 1] != '-') && (v.vlstr[v.vlen - 1] == '-')) ||	// ������� ����� � ������� �������
		((vlstr[vlen - 1] == '-') && (v.vlstr[v.vlen - 1] != '-')))
		minus = true;
	char dividend[SZ];	// �������
	strcpy(dividend, vlstr);
	char divisor[SZ];	// ��������
	strcpy(divisor, v.vlstr);
	int len1 = vlen;	// ����� ��������
	int len2 = v.vlen;	// ����� ��������
	if (vlstr[vlen - 1] == '-')
	{
		dividend[len1 - 1] = '\0'; // ������� �����
		--len1;
	}
	if (v.vlstr[v.vlen - 1] == '-')
	{
		divisor[len2 - 1] = '\0';	// ������� ����c
		--len2;
	}
	if (divisor[len2 - 1] == '0')	// ������� �� ����
	{
		cout << "Division by zero!" << endl;
		char wrong[] = "Wrong!";
		_strrev(wrong);
		return verylong(wrong);
	}
	_strrev(dividend);  // �������������� ������ ��������
	char div_part[SZ];	// �������� ����� ��������
	char quot[SZ];	// �������
	int div_dig = 0;		// ������ � �������� ����� ��������
	int quot_dig = 0;		// ������ � �������
	bool allow_null = false;		// ���������� true, ����� � ������� ����������� �����, �������� �� ����
	for (int j = 0; j < len1; j++) // ��� ������� ������� ��������
	{
		char digit = dividend[j];	// �������� ������
		div_part[div_dig] = digit;	// �������� ����� � �������� ����� ��������
		div_part[div_dig + 1] = '\0';
		char rev_div_part[SZ];		// ������������ �������� ����� ��������
		strcpy(rev_div_part, div_part);
		_strrev(rev_div_part);
		if (bigger(verylong(rev_div_part), verylong(divisor)) == -1)
		{		// ���� �������� ����� �������� ������ ��������
			if (div_part[0] != '0') // ���� �������� ����� �������� ���������� �� � ����
				++div_dig;	// �������� ������ � �������� ����� ��������
			if (allow_null)
				quot[quot_dig++] = '0';	// �������� ���� � �������
		}
		else
		{
			allow_null = true;
			verylong sub_part = verylong(rev_div_part) - verylong(divisor);	// ����������� ��������
			quot[quot_dig] = '1';
			while (bigger(sub_part, verylong(divisor)) != -1) // ���� �������� �� ������ ��������
			{
				sub_part = sub_part - verylong(divisor);	// ��������� �������� �� ��������
				++quot[quot_dig];	// ��������� ����� � ������� ��������
			}
			++quot_dig;		// �������� ������ � �������
			for (int i = 0; i < strlen(div_part); i++)
				div_part[i] = '\0';		// �������� �������� ����� ��������
			strcpy(div_part, _strrev(sub_part.vlstr)); // ���������������� �������� ����� ���������� ���������
			if (div_part[0] == '0')		// ���� �������� ����� �������� ���������� � ����, ������ ���
			{
				div_part[0] = '\0';
			}
			div_dig = strlen(div_part); // ���������������� ������ � �������� ����� �� ������
		}
	}
	if (allow_null == false)	// ���� ������� �� ������������������
		quot[quot_dig++] = '0';	// ���������������� ������� �����
	quot[quot_dig] = '\0';
	verylong temp(_strrev(quot));
	if (minus)
	{
		temp.vlstr[temp.vlen] = '-';		// �������� �����
		temp.vlstr[temp.vlen + 1] = '\0';   // ��������� ������������ ������
	}
	return temp;               // ������� ��������� verylong
}
//--------------------------------------------------------
istream& operator>> (istream& stream, verylong& v)
{
	stream >> v.vlstr;           // �������� ������ �� ������������
	v.vlen = strlen(v.vlstr);   // ����� �� �����
	_strrev(v.vlstr);
	return stream;
}
//---------------------------------------------------------
ostream& operator<< (ostream& stream, verylong& v)
{
	char tempstr[SZ];
	strcpy(tempstr, v.vlstr);        // ������� �����
	stream << _strrev(tempstr);
	return stream;
}
//---------------------------------------------------------
int bigger(const verylong v_1, const verylong v_2)
{
	if ((v_1.vlen) > (v_2.vlen))
		return 1;
	if ((v_1.vlen) < (v_2.vlen))
		return -1;
	for (int j = v_1.vlen - 1; j >= 0; j--)  // � ��� ��� ������ �������
	{
		if (v_1.vlstr[j] > v_2.vlstr[j])
			return 1;
		if (v_1.vlstr[j] < v_2.vlstr[j])
			return -1;
	}
	return 0;
}
//---------------------------------------------------------
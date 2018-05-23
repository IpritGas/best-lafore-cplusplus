// verylong.cpp
// реализация обработки данных типа verylong

#include "verylong.h"        // заголовочный файл для verylong
//---------------------------------------------------------
void verylong::putvl() const // вывод на экран verylong
{
	char tempstr[SZ];
	strcpy(tempstr, vlstr);        // создать копию
	cout << _strrev(tempstr);      // перевернуть копию и вывести ее
}
//---------------------------------------------------------
void verylong::getvl()       // получить сверхбольшое число от пользователя
{
	cin >> vlstr;              // получить строку от пользователя
	vlen = strlen(vlstr);      // найти ее длину
	_strrev(vlstr);            // перевернуть ее
}
//---------------------------------------------------------
verylong verylong::operator+ (const verylong v) const	// сложение
{
	if ((vlstr[vlen - 1] != '-') && (v.vlstr[v.vlen - 1] == '-'))	// сложение чисел с разными знаками
	{
		char tempstr[SZ];
		strcpy(tempstr, v.vlstr);
		tempstr[v.vlen - 1] = '\0';	// удаляем минус
		return (verylong(vlstr) - verylong(tempstr));	// заменяем сложение вычитанием
	}
	if ((vlstr[vlen - 1] == '-') && (v.vlstr[v.vlen - 1] != '-'))	// сложение чисел с разными знаками
	{
		char tempstr[SZ];
		strcpy(tempstr, vlstr);
		tempstr[vlen - 1] = '\0';	// удаляем минус
		return (verylong(v.vlstr) - verylong(tempstr)); // заменяем сложение вычитанием
	}
	bool minus = false;
	if ((vlstr[vlen - 1] == '-') && (v.vlstr[v.vlen - 1] == '-')) // сложение отрицательных чисел
		minus = true;
	int len1 = vlen;
	int len2 = v.vlen;
	if (minus)
	{
		--len1;	// не учитывать минусы
		--len2;
	}
	int maxlen = (len1 > len2) ? len1 : len2; // найти самое длинное число
	char tempstr[SZ];
	int j;
	int carry = 0;             // установить в 1, если сумма >= 10
	for (j = 0; j < maxlen; j++)  // и так для каждой позиции
	{
		int d1 = (j > len1 - 1) ? 0 : vlstr[j] - '0';    //получить разряд												 
		int d2 = (j > len2 - 1) ? 0 : v.vlstr[j] - '0'; // и еще
		int digitsum = d1 + d2 + carry;  // сложить разряды
		if (digitsum >= 10)				 // если перенос, то
		{
			digitsum -= 10; carry = 1;	// увеличить сумму на 10 и установить перенос в 1
		}
		else
			carry = 0;             // иначе перенос = 0
		tempstr[j] = digitsum + '0';  // вставить символ в строку
	}
	if (carry == 1)               // если перенос в конце,
		tempstr[j++] = '1';         // последняя цифра = 1
	if (minus)
		tempstr[j++] = '-';		// добавить минус
	tempstr[j] = '\0';            // поставить ограничитель строки
	return verylong(tempstr);     // вернуть временный verylong
}
//---------------------------------------------------------
verylong verylong::operator- (const verylong v) const	// вычитание
{
	if ((vlstr[vlen - 1] != '-') && (v.vlstr[v.vlen - 1] == '-')) // вычитание из положительного отрицательного
	{
		char tempstr[SZ];
		strcpy(tempstr, v.vlstr);
		tempstr[v.vlen - 1] = '\0';	// удаляем минус
		return (verylong(vlstr) + verylong(tempstr));	// заменяем вычитание сложением
	}
	if ((vlstr[vlen - 1] == '-') && (v.vlstr[v.vlen - 1] != '-')) // вычитание из отрицательного положительного
	{
		char tempstr[SZ];
		strcpy(tempstr, vlstr);
		tempstr[v.vlen] = '-';		// добавляем минус
		tempstr[v.vlen + 1] = '\0';
		return (verylong(vlstr) + verylong(tempstr));	// заменяем вычитание сложением отрицательных чисел
	}
	if ((vlstr[vlen - 1] == '-') && (v.vlstr[v.vlen - 1] == '-')) // вычитание отрицательных чисел
	{
		char tempstr_1[SZ];
		strcpy(tempstr_1, vlstr);
		tempstr_1[vlen - 1] = '\0';	// удаляем минус
		char tempstr_2[SZ];
		strcpy(tempstr_2, v.vlstr);
		tempstr_2[v.vlen - 1] = '\0';	// удаляем минус	
		return (verylong(tempstr_2) - verylong(tempstr_1)); // заменяем вычитанием положительных чисел
	}
	if (bigger(verylong(vlstr), verylong(v.vlstr)) == -1)	// если положительное уменьшаемое меньше вычитаемого
	{
		verylong tempvl = verylong(v.vlstr) - verylong(vlstr);	// меняем их местами
		tempvl.vlstr[tempvl.vlen] = '-';	// добавляем минус
		tempvl.vlstr[tempvl.vlen + 1] = '\0';
		return tempvl;
	}
	char tempstr[SZ];
	int j;
	int carry = 0;             // установить в -1, если разность < 0
	for (j = 0; j < vlen; j++)  // и так для каждой позиции
	{
		int d1 = (j > vlen - 1) ? 0 : vlstr[j] - '0';    //получить разряд												 
		int d2 = (j > v.vlen - 1) ? 0 : v.vlstr[j] - '0'; // и еще
		int digitsub = d1 - d2 + carry;  // вычесть разряды
		if (digitsub < 0)				 // если перенос, то
		{
			digitsub += 10; carry = -1;	// увеличить сумму на 10 и установить перенос в -1
		}
		else
			carry = 0;             // иначе перенос = 0
		tempstr[j] = digitsub + '0';  // вставить символ в строку
	}
	tempstr[j--] = '\0';            // поставить ограничитель строки
	for (j; j > 0; j--)		// убрать лишние нули
		if (tempstr[j] == '0')
			tempstr[j] = '\0';
		else
			break;
	return verylong(tempstr);     // вернуть временный verylong
}
//---------------------------------------------------------
verylong verylong::operator* (const verylong v) const	//умножение сверхбольших чисел
{
	bool minus = false;
	if (((vlstr[vlen - 1] != '-') && (v.vlstr[v.vlen - 1] == '-')) ||	// умножение чисел с разными знаками
		((vlstr[vlen - 1] == '-') && (v.vlstr[v.vlen - 1] != '-')))
		minus = true;
	verylong pprod;            // произведение одного разряда
	verylong tempsum;          // текущая сумма
	int len = v.vlen;
	if (v.vlstr[v.vlen - 1] == '-')
		--len;		// не учитывать минусы
	for (int j = 0; j < len; j++) // для каждого разряда аргумента
	{
		int digit = v.vlstr[j] - '0'; // получить разряд
		pprod = multdigit(digit);   // умножить текущий на него
		for (int k = 0; k < j; k++)
			pprod = mult10(pprod);     // умножить результат на степень 10-ти
		tempsum = tempsum + pprod;  // прибавить произведение к текущей сумме							
	}
	verylong temp(tempsum);
	if (minus)
	{
		temp.vlstr[temp.vlen] = '-';		// добавить минус
		temp.vlstr[temp.vlen + 1] = '\0';   // поставить ограничитель строки
	}
	return temp;               // вернуть временный verylong
}
//---------------------------------------------------------
verylong verylong::mult10(const verylong v) const // умножение аргумента на 10		  
{
	char tempstr[SZ];
	int len = v.vlen;
	if (v.vlstr[v.vlen - 1] == '-')
		--len;		// не учитывать минусы
	for (int j = len - 1; j >= 0; j--) // сдвинуться на один разряд выше
		tempstr[j + 1] = v.vlstr[j];
	tempstr[0] = '0';                // обнулить самый младший разряд
	tempstr[len + 1] = '\0';        // поставить ограничитель строки
	return verylong(tempstr);        // вернуть результат
}
//---------------------------------------------------------
verylong verylong::multdigit(const int d2) const   // умножение числа на аргумент (цифру)
{
	char tempstr[SZ];
	int j, carry = 0;
	int len = vlen;
	if (vlstr[vlen - 1] == '-')
		--len;		// не учитывать минусы
	for (j = 0; j < len; j++)    // для каждого разряда в этом сверхбольшом
	{
		int d1 = vlstr[j] - '0';   // получить значение разряда
		int digitprod = d1 * d2; // умножить на цифру
		digitprod += carry;      // добавить старый перенос
		if (digitprod >= 10)    // если возник новый перенос,
		{
			carry = digitprod / 10;  // переносу присвоить значение старшего разряда
			digitprod -= carry * 10; // результату - младшего
		}
		else
			carry = 0;             // иначе перенос = 0
		tempstr[j] = digitprod + '0'; // вставить символ в строку
	}
	if (carry != 0)             // если на конце перенос,
		tempstr[j++] = carry + '0';   // это последний разряд
	tempstr[j] = '\0';            // поставить ограничитель
	return verylong(tempstr);     // вернуть сверхбольшое число
}
//---------------------------------------------------------
verylong verylong::operator/ (const verylong v) const // деление
{
	bool minus = false;
	if (((vlstr[vlen - 1] != '-') && (v.vlstr[v.vlen - 1] == '-')) ||	// деление чисел с разными знаками
		((vlstr[vlen - 1] == '-') && (v.vlstr[v.vlen - 1] != '-')))
		minus = true;
	char dividend[SZ];	// делимое
	strcpy(dividend, vlstr);
	char divisor[SZ];	// делитель
	strcpy(divisor, v.vlstr);
	int len1 = vlen;	// длина делимого
	int len2 = v.vlen;	// длина делителя
	if (vlstr[vlen - 1] == '-')
	{
		dividend[len1 - 1] = '\0'; // удаляем минус
		--len1;
	}
	if (v.vlstr[v.vlen - 1] == '-')
	{
		divisor[len2 - 1] = '\0';	// удаляем минуc
		--len2;
	}
	if (divisor[len2 - 1] == '0')	// деление на ноль
	{
		cout << "Division by zero!" << endl;
		char wrong[] = "Wrong!";
		_strrev(wrong);
		return verylong(wrong);
	}
	_strrev(dividend);  // переворачиваем строку делимого
	char div_part[SZ];	// активная часть делимого
	char quot[SZ];	// частное
	int div_dig = 0;		// разряд в активной части делимого
	int quot_dig = 0;		// разряд в частном
	bool allow_null = false;		// становится true, когда в частное вписывается цифра, отличная от нуля
	for (int j = 0; j < len1; j++) // для каждого разряда делимого
	{
		char digit = dividend[j];	// получить разряд
		div_part[div_dig] = digit;	// добавить цифру в активную часть делимого
		div_part[div_dig + 1] = '\0';
		char rev_div_part[SZ];		// перевернутая активная часть делимого
		strcpy(rev_div_part, div_part);
		_strrev(rev_div_part);
		if (bigger(verylong(rev_div_part), verylong(divisor)) == -1)
		{		// если активная часть делимого меньше частного
			if (div_part[0] != '0') // если активная часть делимого начинается не с нуля
				++div_dig;	// добавить разряд в активной части делимого
			if (allow_null)
				quot[quot_dig++] = '0';	// добавить ноль в частное
		}
		else
		{
			allow_null = true;
			verylong sub_part = verylong(rev_div_part) - verylong(divisor);	// уменьшаемая подчасть
			quot[quot_dig] = '1';
			while (bigger(sub_part, verylong(divisor)) != -1) // пока подчасть не меньше делителя
			{
				sub_part = sub_part - verylong(divisor);	// уменьшить подчасть на делитель
				++quot[quot_dig];	// увеличить цифру в разряде частного
			}
			++quot_dig;		// добавить разряд в частном
			for (int i = 0; i < strlen(div_part); i++)
				div_part[i] = '\0';		// очистить активную часть делимого
			strcpy(div_part, _strrev(sub_part.vlstr)); // инициализировать активную часть оставшейся подчастью
			if (div_part[0] == '0')		// если активная часть делимого начинается с нуля, убрать его
			{
				div_part[0] = '\0';
			}
			div_dig = strlen(div_part); // инициализировать разряд в активной части ее длиной
		}
	}
	if (allow_null == false)	// если частное не инициализировалось
		quot[quot_dig++] = '0';	// инициализировать частное нулем
	quot[quot_dig] = '\0';
	verylong temp(_strrev(quot));
	if (minus)
	{
		temp.vlstr[temp.vlen] = '-';		// добавить минус
		temp.vlstr[temp.vlen + 1] = '\0';   // поставить ограничитель строки
	}
	return temp;               // вернуть временный verylong
}
//--------------------------------------------------------
istream& operator>> (istream& stream, verylong& v)
{
	stream >> v.vlstr;           // получить строку от пользователя
	v.vlen = strlen(v.vlstr);   // найти ее длину
	_strrev(v.vlstr);
	return stream;
}
//---------------------------------------------------------
ostream& operator<< (ostream& stream, verylong& v)
{
	char tempstr[SZ];
	strcpy(tempstr, v.vlstr);        // создать копию
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
	for (int j = v_1.vlen - 1; j >= 0; j--)  // и так для каждой позиции
	{
		if (v_1.vlstr[j] > v_2.vlstr[j])
			return 1;
		if (v_1.vlstr[j] < v_2.vlstr[j])
			return -1;
	}
	return 0;
}
//---------------------------------------------------------
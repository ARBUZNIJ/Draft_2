#include "polynomials.h"
#include <locale>

int main()  
{
	setlocale(LC_ALL, "Rus");
	int quan_input;
	cout << "Введите количество мономов в полиноме: ";
	cin >> quan_input;
	Polynomial a(quan_input);
	cout << "Введите количество мономов в полиноме: ";
	cin >> quan_input;
	Polynomial b(quan_input), c;
	c = a*b;
	cout << c << endl/* << exam*/;
}
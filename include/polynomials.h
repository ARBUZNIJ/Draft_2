#pragma once
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class Polynomial
{
private:
	class Monome
	{
	public:
		double alpha;
		int m;
		Monome* next;
		Monome(double alp, int pow, Monome* next) : alpha(alp), m(pow)
		{
			this->next = next;
		}
		Monome(const Monome& mn) : alpha(mn.alpha), m(mn.m) //конструктор копировани€ мономов. —ледующий моном - null
		{
			next = nullptr;
		}
		~Monome()
		{
			m = 0;
			next = nullptr;
		} 
	};
	Monome* head;
	int quanity;
public:
	Polynomial(int quan);
	Polynomial();
	Polynomial(const Polynomial& p);
	~Polynomial();
	void pop(double alpha, int pow);
	void pop(double alpha, int pow_x, int pow_y, int pow_z);
	Polynomial& operator=(const Polynomial& p);
	Polynomial& operator *=(double factor);
	Polynomial operator *(double factor);
	Polynomial& operator +=(const Polynomial& p);
	Polynomial operator +(const Polynomial& p);
	Polynomial operator -(const Polynomial& p);
	Polynomial& operator -=(const Polynomial& p);
	Polynomial operator *(const Polynomial& p);
	friend ostream& operator<<(ostream& ostr, const Polynomial& p)
	{
		Monome* prev = p.head->next;
		if (p.quanity != 0)
		{
			ostr << prev->alpha << " x^" << (prev->m) / 100 << " y^" << ((prev->m) % 100) / 10 << " z^" << (prev->m) % 10;
			prev = prev->next;
		}
		for (int i = 1; i < p.quanity; i++)
		{
			ostr << " + " << prev->alpha << " x^" << (prev->m) / 100 << " y^" << ((prev->m) % 100) / 10 << " z^" << (prev->m) % 10;
			prev = prev->next;
		}
		return ostr;
	}
};
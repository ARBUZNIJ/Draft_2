#include "polynomials.h"

Polynomial::Polynomial(int quan) : quanity(0)
{
	head = new Monome(0, 0, nullptr); //фиктивная голова
	double a;
	int pow_x, pow_y, pow_z;
	for (int i = 0; i < quan; i++)
	{
		cin >> a >> pow_x >> pow_y >> pow_z;
		if (a != 0 && (pow_x >= 0 && pow_x <= 9) &&
			(pow_y >= 0 && pow_y <= 9) &&
			(pow_z >= 0 && pow_z <= 9))
		{
			pop(a, pow_x, pow_y, pow_z);
		}
		else if (a == 0)	continue;
		else
		{
			string except("Invalid input of monome ");
			except += to_string(i);
			throw invalid_argument(except);
		}

	}

}

Polynomial::Polynomial() : quanity(0)
{
	head = new Monome(0, 0, nullptr); //фиктивная голова
}

Polynomial::Polynomial(const Polynomial& p) : quanity(p.quanity)
{
	Monome* ind_p = p.head->next;
	head = new Monome(0, 0, nullptr); //фиктивная голова
	Monome* ind_this = head;
	for (int i = 0; i < quanity; i++)
	{
		ind_this->next = new Monome(*ind_p);
		ind_p = ind_p->next;
		ind_this = ind_this->next;
	}
}
void Polynomial::pop(double alpha, int pow)
{
	if (quanity == 0)
	{
		head->next = new Monome(alpha, pow, nullptr);
		quanity++;
		return;
	}
	Monome* last = head->next;
	Monome* pre_last = head;
	int i;
	for (i = 0; i < quanity; i++)
	{
		if (pow > last->m)
		{
			pre_last->next = new Monome(alpha, pow, last);
			quanity++;
			return;
		}
		else if (last->m == pow)
		{
			last->alpha += alpha;
			if (last->alpha == 0)
			{
				quanity--;
				pre_last->next = last->next;
				delete last;
			}
			return;
		}
		pre_last = last;
		last = last->next;
	}
	if (i == quanity)
	{
		pre_last->next = new Monome(alpha, pow, nullptr);
		quanity++;
	}
}

void Polynomial::pop(double alpha, int pow_x, int pow_y, int pow_z)
{
	if (quanity == 0)
	{
		head->next = new Monome(alpha, pow_x * 100 + pow_y * 10 + pow_z, nullptr);
		quanity++;
		return;
	}
	Monome* last = head->next;
	Monome* pre_last = head;
	int i;
	for (i = 0; i < quanity; i++)
	{
		if (pow_x * 100 > last->m ||
			(pow_x == (last->m) / 100 && pow_y * 10 > (last->m) % 100) ||
			(pow_x == (last->m) / 100 && pow_y == ((last->m) % 100) / 10 && pow_z > (last->m) % 10))
		{
			pre_last->next = new Monome(alpha, pow_x * 100 + pow_y * 10 + pow_z, last);
			quanity++;
			return;
		}
		else if (pow_x == (last->m) / 100 && pow_y == ((last->m) % 100) / 10 && pow_z == (last->m) % 10)
		{
			last->alpha += alpha;
			if (last->alpha == 0)
			{
				quanity--;
				pre_last->next = last->next;
				delete last;
			}
			return;
		}
		pre_last = last;
		last = last->next;
	}
	if (i == quanity)
	{
		pre_last->next = new Monome(alpha, pow_x * 100 + pow_y * 10 + pow_z, last);
		quanity++;
	}
}

Polynomial& Polynomial:: operator=(const Polynomial& p)
{
	if (this == &p)
		return *this;

	Monome* ind = head, * ind_next = head->next;
	for (int i = 0; i < quanity; i++)
	{
		delete ind;
		ind = ind_next;
		ind_next = ind_next->next;
	}

	quanity = p.quanity;
	Monome* ind_p = p.head->next;
	head = new Monome(0, 0, nullptr); //фиктивная голова
	Monome* ind_this = head;
	for (int i = 0; i < quanity; i++)
	{
		ind_this->next = new Monome(*ind_p);
		ind_p = ind_p->next;
		ind_this = ind_this->next;
	}
	return *this;
}

Polynomial& Polynomial:: operator *=(double factor)
{
	Monome* prev = head->next;
	for (int i = 0; i < quanity; i++)
	{
		prev->alpha *= factor;
		prev = prev->next;
	}
	return *this;
}

Polynomial Polynomial:: operator *(double factor)
{
	Polynomial tmp(*this);
	return tmp.operator*=(factor);
}

Polynomial& Polynomial:: operator +=(const Polynomial& p)
{
	Monome* ind_p = p.head->next, * this_last = head->next, * this_pre_last = head;
	for (int i = 0; i < p.quanity; i++)
	{
		while (this_last != nullptr && ind_p->m < this_last->m)
		{
			this_pre_last = this_last;
			this_last = this_last->next;
		}
		if (this_last == nullptr || ind_p->m > this_last->m)
		{
			this_pre_last = this_pre_last->next = new Monome(*ind_p);
			this_pre_last->next = this_last;
			quanity++;
		}
		else if (ind_p->m == this_last->m)
		{
			this_last->alpha += ind_p->alpha;
			if (this_last->alpha < 1e-15)
			{
				quanity--;
				this_pre_last->next = this_last->next;
				delete this_last;
				this_last = this_pre_last->next;
			}
		}
		ind_p = ind_p->next;
	}
	return *this;
}

Polynomial Polynomial:: operator +(const Polynomial& p)
{
	Polynomial tmp(*this);
	return tmp.operator+=(p);
}

Polynomial Polynomial::operator -(const Polynomial& p)
{
	Polynomial tmp(*this);
	return tmp.operator-=(p);
}

Polynomial& Polynomial:: operator -=(const Polynomial& p)
{
	Polynomial tmp(p);
	tmp.operator*(-1);
	return operator+=(tmp);
}

Polynomial Polynomial:: operator *(const Polynomial& p)
{
	Polynomial tmp;
	Monome* ind_this = head->next;
	for (int i = 0; i < quanity; i++)
	{
		Monome* ind_p = p.head->next;
		for (int j = 0; j < p.quanity; j++)
		{
			if ((ind_this->m % 10 + ind_p->m % 10 < 10) &&
				((ind_this->m / 10) % 10 + (ind_p->m / 10) % 10 < 10) &&
				(ind_this->m / 100 + ind_p->m / 100 < 10))

				tmp.pop(ind_this->alpha * ind_p->alpha, ind_this->m + ind_p->m);

			else throw invalid_argument("The pow of the result is above 10");
			ind_p = ind_p->next;
		}
		ind_this = ind_this->next;
	}
	return tmp;
}

Polynomial::~Polynomial()
{
	Monome* ind = head, * ind_next = head->next;
	for (int i = 0; i < quanity; i++)
	{
		delete ind;
		ind = ind_next;
		ind_next = ind_next->next;
	}
	quanity = 0;
}
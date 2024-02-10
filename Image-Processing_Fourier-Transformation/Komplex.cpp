#include "Komplex.h"

using namespace std;

Komplex Komplex::operator+(const Komplex& other)
{
	double new_re = this->a + other.a;
	double new_im = this->b + other.b;

	Komplex temp(new_re, new_im);
	return temp;
}

Komplex Komplex::operator-(const Komplex& other)
{
	double new_re = this->a - other.a;
	double new_im = this->b - other.b;

	Komplex temp(new_re, new_im);
	return temp;
}

Komplex Komplex::operator*(const Komplex& other)
{
	double new_re = (this->a * other.a) - (this->b * other.b);
	double new_im = (this->a * other.b) + (this->b * other.a);

	Komplex temp(new_re, new_im);
	return temp;
}

Komplex Komplex::operator*(double x)
{
	Komplex temp(this->a * x, this->b * x);
	return temp;
}

double Komplex::abs() const
{
	return sqrt((a * a) + (b * b));
}
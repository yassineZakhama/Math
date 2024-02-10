#pragma once

#include <math.h>

class Komplex
{
private:
	double a;
	double b;

public:
	Komplex() : a{ 0.0 }, b{ 0.0 } {}
	Komplex(double _a, double _b)
		: a{ _a }, b{ _b } {}

	Komplex(double phi)
		: a{ cos(phi) }, b{ sin(phi) } {}

	double re() const { return a; }
	double im() const { return b; }

	Komplex operator+(const Komplex& other);
	Komplex operator-(const Komplex& other);
	Komplex operator*(const Komplex& other);
	Komplex operator*(double x);

	double abs() const;
};
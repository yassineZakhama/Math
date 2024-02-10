#pragma once

#include <iostream>
#include "MyVektor.h"
#include <cmath>
#include <vector>

MyVektor operator+(MyVektor a, MyVektor b)
{
	MyVektor temp(a.get_dimension());

	for (int i = 0; i < a.get_dimension(); ++i)
		temp[i] = a[i] + b[i];
	//temp.set_component(i, a[i] + b[i]);
	return temp;
}
MyVektor operator*(double lambda, MyVektor a)
{
	for (int i = 0; i < a.get_dimension(); ++i)
		a[i] = a[i] * lambda;
	// a.set_component(i, a[i] * lambda);

	return a;
}

double f(MyVektor x)
{
	return sin(x[0] * x[1]) + sin(x[0]) + cos(x[1]);
}
double g(MyVektor x)
{
	return -(2 * x[0] * x[0] - 2 * x[0] * x[1] + x[1] * x[1] + x[2] * x[2] - 2 * x[0] - 4 * x[2]);
}

MyVektor gradient(MyVektor x, double (*funktion)(MyVektor x))
{
	MyVektor gradient(x.get_dimension());

	const double h = 1E-8;

	double f_ohne_aenderung = funktion(x);

	for (int i = 0; i < x.get_dimension(); ++i)
	{
		double temp = x[i];
		x[i] = x[i] + h;
		// x.set_component(i, x[i] + h);

		gradient[i] = (funktion(x) - f_ohne_aenderung) / h;
		//gradient.set_component(i, (funktion(x) - f_ohne_aenderung) / h);

		x[i] = temp;
		//x.set_component(i, temp);
	}

	return gradient;
}

MyVektor gradientenverfahren(MyVektor x, double (*funktion)(MyVektor x))
{
	unsigned gemachte_schritte = 0;
	float lambda;
	std::cout << "Start-Schrittweite eingeben : ";
	std::cin >> lambda;

	while (true)
	{
		MyVektor grad = gradient(x, funktion);

		//Abbruch Bedingungen
		if (grad.get_laenge() <= 1E-5 || gemachte_schritte == 25)
		{
			if (grad.get_laenge() <= 1E-5)
				std::cout << "Ende wegen ||grad f(x)||<1e-5 bei " << std::endl;

			else
				std::cout << "Ende wegen Schrittanzahl = 25 bei" << std::endl;

			std::cout << "\tx = ";
			x.log();
			std::cout << "\tlambda = " << lambda << std::endl;
			std::cout << "\tf(x) = " << funktion(x) << std::endl;
			std::cout << "\tgrad f(x) = ";
			grad.log();
			std::cout << "\t||grad f(x)|| = " << grad.get_laenge() << "\n" << std::endl;

			break;
		}

		std::cout << "\tSchritt " << gemachte_schritte << ':' << std::endl;

		std::cout << "x = ";
		x.log();
		std::cout << "lambda = " << lambda << std::endl;
		std::cout << "f(x) = " << funktion(x) << std::endl;
		std::cout << "grad f(x) = ";
		grad.log();
		std::cout << "||grad f(x)|| = " << grad.get_laenge() << "\n" << std::endl;

		//
		MyVektor x_1 = x + lambda * gradient(x, funktion);
		std::cout << "x_neu = ";
		x_1.log();
		std::cout << "f(x_neu) = " << funktion(x_1) << "\n" << std::endl;

		if (funktion(x_1) > funktion(x))
		{
			x = x_1;

			std::cout << "Test mit doppelter Schrittweite (lambda = " << lambda * 2 << " ):" << std::endl;
			x_1 = x + 2 * lambda * gradient(x, funktion);
			std::cout << "x_test = ";
			x_1.log();
			std::cout << "f(x_test) = " << f(x_1) << std::endl;

			if (funktion(x_1) > funktion(x))
			{
				x = x_1;
				lambda *= 2;
				std::cout << "verdoppele Schrittweite!" << std::endl;
			}
			else
				std::cout << "behalte alte Schrittweite!" << std::endl;
		}
		else
		{
			do
			{
				lambda /= 2;
				std::cout << "halbiere Schrittweite (lambda = " << lambda << " ):" << std::endl;

				x_1 = x + 2 * lambda * gradient(x, funktion);

				std::cout << "x_neu = ";
				x_1.log();
				std::cout << "f(x_neu) = " << funktion(x_1) << "\n" << std::endl;
			} while (funktion(x_1) < funktion(x));

		}

		++gemachte_schritte;
		std::cout << "\n" << std::endl;
	}

	return x;
}


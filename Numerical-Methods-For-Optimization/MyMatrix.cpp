#include "MyMatrix.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

MyMatrix::MyMatrix(std::initializer_list<std::initializer_list<double>> lst) {
	zeilen = lst.size();
	spalten = lst.begin()->size();

	// Allocate memory for the matrix
	matrix = new double* [zeilen];
	for (int i = 0; i < zeilen; i++) {
		matrix[i] = new double[spalten];
	}

	// Copy the values from the initializer list
	int i = 0;
	int j = 0;
	for (const auto& row : lst) {
		j = 0;
		for (const auto& val : row) {
			matrix[i][j] = val;
			j++;
		}
		i++;
	}
}

MyMatrix::~MyMatrix()
{
	for (int i = 0; i < zeilen; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

MyMatrix MyMatrix::invers()
{
	if (zeilen != 2 || spalten != 2)
	{
		throw "Inverse nicht moeglich!";
	}

	MyMatrix inv_mat(zeilen, spalten);

	double faktor = 1 / ((matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]));
	
	inv_mat.set_component(0, 0, matrix[1][1] * faktor);
	inv_mat.set_component(0, 1, - matrix[0][1] * faktor);
	inv_mat.set_component(1, 0, - matrix[1][0] * faktor);
	inv_mat.set_component(1, 1, matrix[0][0] * faktor);
	
	return inv_mat;
}

void MyMatrix::log()
{
	int max_length = spalten;
	

	// output the matrix without a fixed precision and with padding
	for (int i = 0; i < zeilen; ++i) {
		for (int j = 0; j < spalten; ++j) {
			std::cout << std::setw(max_length + 6) << matrix[i][j];
		}
		std::cout << std::endl;
	}

	//std::cout << "Zeilen : " << zeilen << "\tSpalten : " << spalten << std::endl;
}

MyVektor MyMatrix::operator*(MyVektor x)
{
	MyVektor temp(zeilen);
	
	for (int i = 0; i < zeilen; ++i)
	{
		for (int j = 0; j < spalten; ++j)
		{
			//std::cout << temp[i] << " + " << x[j] << " * " << matrix[i][j] << std::endl;
			temp[i] = temp[i] + x[j] * matrix[i][j];

		}
	}
	return temp;
}


MyVektor f_jacobi(MyVektor x)
{
	MyVektor temp(3);

	temp[0] = x[0] * x[1] * exp(x[2]);
	temp[1] = x[1] * x[2] * x[3];
	temp[2] = x[3];

	return temp;
}
MyVektor f_newton(MyVektor x)
{
	MyVektor temp(2);
	temp[0] = (x[0] * x[0] * x[0]) * (x[1] * x[1] * x[1]) - 2 * x[1];
	temp[1] = x[0] - 2;

	return temp;
}


MyMatrix jacobi(MyVektor x, MyVektor(*funktion)(MyVektor x))
{
	const double h = 1E-4;

	MyVektor werte_ohne_aenderung = funktion(x);

	int zeilen = werte_ohne_aenderung.get_dimension();
	int spalten = x.get_dimension();

	MyMatrix jacobi_matrix(zeilen, spalten);

	for (int j = 0; j < spalten; ++j)
	{
		double temp = x[j];
		x[j] = x[j] + h;

		MyVektor werte_mit_aenderung = funktion(x);
		for (int i = 0; i < zeilen; ++i)
		{
			jacobi_matrix.set_component(i, j, (werte_mit_aenderung[i] - werte_ohne_aenderung[i]) / h);


		}
		x[j] = temp;
	}
	return jacobi_matrix;
}

MyVektor newton_verfahren(MyVektor x, MyVektor(*funktion)(MyVektor x))
{
	unsigned gemachte_schritte = 0;

	while (true)
	{
		cout << "\tSchritt " << gemachte_schritte << ':' << endl;

		// startstelle
		cout << "x = ";
		x.log();

		MyVektor ergebnis_f_newton = funktion(x);
		cout << "f(x) = ";
		ergebnis_f_newton.log();

		MyMatrix A = jacobi(x, f_newton);
		cout << "Jacobi-Matrix:" << endl;
		A.log();

		cout << "Inverse von Jacobi-Matrix:" << endl;
		try {
			A.invers().log();
		}
		catch (const char* error) {
			cout << error << endl;
		}

		MyVektor dx(2);
		cout << "dx = ";
		dx = A.invers() * ((-1) * ergebnis_f_newton);
		dx.log();

		cout << "||f(x)|| = " << x.get_laenge() << endl;

		x = x + dx;
		++gemachte_schritte;

		cout << endl;

		//abbruchbedingungen
		if (funktion(x).get_laenge() <= 1E-5 || gemachte_schritte == 50)
		{
			if (funktion(x).get_laenge() <= 1E-5)
				std::cout << "Ende wegen ||grad f(x)||<1e-5 bei " << std::endl;

			else
				std::cout << "Ende wegen Schrittanzahl = 50 bei" << std::endl;

			std::cout << "\tx = ";
			x.log();

			std::cout << "\tf(x) = ";
			funktion(x).log();

			std::cout << "\t||f(x)|| = " << funktion(x).get_laenge() << "\n" << std::endl;

			return x;
		}
	}
}

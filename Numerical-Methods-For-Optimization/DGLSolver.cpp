#include "DGLSolver.h"
#include <iostream>


MyVektor DGLSolver::ableitungen(MyVektor y, double x)
{
	if(erste_ordnung)
	{ 
		MyVektor v = f_DGL_System(y, x);
		return v;
	}
	else
	{
		int y_dimension = y.get_dimension();

		
		MyVektor result(y_dimension);

		for (int i = 0; i < y_dimension -1 ; ++i)
		{
			result[i] = y[i + 1];
		}

		result[y_dimension - 1] = f_DGL_nterOrdnung(y, x);
		return result;
	}
}

void DGLSolver::euler_heun_verfahren(double x_start, double x_end, MyVektor y_start)
{
	bool heun;
	std::cout << "0 fuer Euler, alles andere ist Heun \n ?> ";
	std::cin >> heun;

	int anzahl_schritte;
	std::cout << "Anzahl schritte eingeben \n ?> ";
	std::cin >> anzahl_schritte;

	double h = (x_end - x_start) / anzahl_schritte;

	int dimension = y_start.get_dimension();

	double next_x = x_start;
	MyVektor next_y = y_start;
	MyVektor ableitung(dimension);

	int gemachte_schritte = 0;

	if (heun)
	{
		MyVektor y_test(dimension);
		MyVektor ableitung_y_test(dimension);

		if (erste_ordnung)
		{
			while (gemachte_schritte != anzahl_schritte)
			{
				std::cout << "Schritt " << gemachte_schritte << ":" << std::endl;

				// x
				std::cout << "\tx = " << next_x << std::endl;

				// y
				std::cout << "\ty = ( " << next_y[0];
				for (int i = 1; i < dimension; ++i)
					std::cout << " ; " << next_y[i];
				std::cout << " )" << std::endl;

				// Ableitung bevor heun
				ableitung = f_DGL_System(next_y, next_x);
				std::cout << "\ty'_orig = ( " << ableitung[0];
				for (int i = 1; i < dimension; ++i)
					std::cout << " ; " << ableitung[i];
				std::cout << " )" << std::endl;

				// y_test
				std::cout << std::endl;
				y_test = next_y + (h * ableitung);
				std::cout << "\ty_test = ( " << y_test[0];
				for (int i = 1; i < dimension; ++i)
					std::cout << " ; " << y_test[i];
				std::cout << " )" << std::endl;

				// Ableitung y_test
				ableitung_y_test = f_DGL_System(y_test, next_x + h);
				std::cout << "\ty'_test = ( " << ableitung_y_test[0];
				for (int i = 1; i < dimension; ++i)
					std::cout << " ; " << ableitung_y_test[i];
				std::cout << " )" << std::endl;

				// Ableitung mittel
				std::cout << std::endl;
				ableitung = 0.5 * (ableitung + ableitung_y_test);
				std::cout << "\ty'_mittel = ( " << ableitung[0];
				for (int i = 1; i < dimension; ++i)
					std::cout << " ; " << ableitung[i];
				std::cout << " )" << std::endl;

				next_y = next_y + (h * ableitung);
				next_x += h;

				++gemachte_schritte;

				std::cout << std::endl;
			}
			// ENDE
			std::cout << "Ende bei:" << std::endl;

			std::cout << "\tx = " << next_x << std::endl;

			std::cout << "\ty = ( " << next_y[0];
			for (int i = 1; i < dimension; ++i)
				std::cout << " ; " << next_y[i];
			std::cout << " )" << std::endl;
		}
		else
		{
			while (gemachte_schritte != anzahl_schritte)
			{
				std::cout << "Schritt " << gemachte_schritte << ":" << std::endl;

				std::cout << "\tx = " << next_x << std::endl;
				std::cout << std::endl;

				// y
				for (int i = 0; i < dimension; ++i)
					std::cout << "\ty" << i << "(" << next_x << ")" << " = " << next_y[i] << std::endl;
				std::cout << std::endl;

				// Ableitung bevor heun
				ableitung = ableitungen(next_y, next_x);
				for (int i = 0; i < dimension; ++i)
					std::cout << "\ty" << i << "'_orig(" << next_x << ")" << " = " << ableitung[i] << std::endl;
				std::cout << std::endl;

				// y_test
				y_test = next_y + (h * ableitung);
				for (int i = 0; i < dimension; ++i)
					std::cout << "\ty" << i << "'_test(" << next_x << ")" << " = " << y_test[i] << std::endl;
				std::cout << std::endl;

				// Ableitung y_test
				ableitung_y_test = ableitungen(y_test, next_x + h);
				for (int i = 0; i < dimension; ++i)
					std::cout << "\ty" << i << "'_test(" << next_x << ")" << " = " << ableitung_y_test[i] << std::endl;
				std::cout << std::endl;

				// Ableitung mittel
				ableitung = 0.5 * (ableitung + ableitung_y_test);
				for (int i = 0; i < dimension; ++i)
					std::cout << "\ty" << i << "'_mittel(" << next_x << ")" << " = " << ableitung[i] << std::endl;
				std::cout << std::endl;

				next_y = next_y + (h * ableitung);
				next_x += h;

				++gemachte_schritte;

				std::cout << std::endl;
			}
			// ENDE
			std::cout << "Ende bei:" << std::endl;

			std::cout << "\tx = " << next_x << std::endl;

			std::cout << std::endl;

			for (int i = 0; i < dimension; ++i)
				std::cout << "\ty" << i << "(" << next_x << ")" << " = " << next_y[i] << std::endl;
			std::cout << std::endl;
		}
	}
	else
	{
		if (erste_ordnung)
		{
			while (gemachte_schritte != anzahl_schritte)
			{
				std::cout << "Schritt " << gemachte_schritte << ":" << std::endl;

				std::cout << "\tx = " << next_x << std::endl;

				std::cout << "\ty = ( " << next_y[0];
				for (int i = 1; i < dimension; ++i)
					std::cout << " ; " << next_y[i];
				std::cout << " )" << std::endl;

				ableitung = f_DGL_System(next_y, next_x);
				std::cout << "\ty' = ( " << ableitung[0];
				for (int i = 1; i < dimension; ++i)
					std::cout << " ; " << ableitung[i];
				std::cout << " )" << std::endl;

				next_x += h;
				next_y = next_y + (h * ableitung);
				++gemachte_schritte;

				std::cout << std::endl;
			}
			// ENDE
			std::cout << "Ende bei:" << std::endl;

			std::cout << "\tx = " << next_x << std::endl;

			std::cout << "\ty = ( " << next_y[0];
			for (int i = 1; i < dimension; ++i)
				std::cout << " ; " << next_y[i];
			std::cout << " )" << std::endl;
		}
		else
		{
			while (gemachte_schritte != anzahl_schritte)
			{
				std::cout << "Schritt " << gemachte_schritte << ":" << std::endl;

				std::cout << "\tx = " << next_x << std::endl;
				std::cout << std::endl;

				// y
				for (int i = 0; i < dimension; ++i)
					std::cout << "\ty" << i << "(" << next_x << ")" << " = " << next_y[i] << std::endl;
				std::cout << std::endl;

				// Ableitung
				ableitung = ableitungen(next_y, next_x);
				for (int i = 0; i < dimension; ++i)
					std::cout << "\ty" << i << "'(" << next_x << ")" << " = " << ableitung[i] << std::endl;
				std::cout << std::endl;

				// new y
				for (int i = 0; i < dimension; ++i)
					next_y[i] = next_y[i] + (h * ableitung[i]);

				next_x += h;
				++gemachte_schritte;
			}
			// ENDE
			std::cout << "Ende bei:" << std::endl;

			std::cout << "\tx = " << next_x << std::endl;

			std::cout << std::endl;

			for (int i = 0; i < dimension; ++i)
				std::cout << "\ty" << i << "(" << next_x << ")" << " = " << next_y[i] << std::endl;
			std::cout << std::endl;

		}
	}
}
#pragma once
#include <vector>
#include "MyVektor.h"


class MyMatrix
{
private:
	int zeilen;
	int spalten;
	double** matrix;

public:
	MyMatrix(int n = 0, int m = 0) : zeilen{ n }, spalten{ m } 
	{ 
		matrix = new double*[zeilen];

		for (int i = 0; i < zeilen; ++i)
			matrix[i] = new double[spalten];
		
	}

    MyMatrix(std::initializer_list<std::initializer_list<double>> lst); 

	~MyMatrix();

	double get_component(int n, int m) const { return matrix[n][m]; }
	void set_component(int n, int m, double new_value) { matrix[n][m] = new_value; }

	int get_rows() const { return zeilen; }
	int get_cols() const { return spalten; }

	MyMatrix invers();

	void log();

	MyVektor operator*(MyVektor x);
};

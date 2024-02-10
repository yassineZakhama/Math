#pragma once
#include <vector>
#include <string>

class MyVektor
{
private:
	int dimension;
	std::vector<double> vektor;

public:
	MyVektor(int _dimension = 0) : dimension{_dimension} { vektor.resize(_dimension); }
	MyVektor(std::initializer_list<double> init);

	
	int get_dimension() const { return dimension; }

	void set_component(int index, double new_value); 
	double get_component(int index) const; 

	double get_laenge();

	double& operator[](int index) { return vektor[index]; }
	
	void log();
};

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
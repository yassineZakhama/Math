#include "MyVektor.h"
#include <iostream>

MyVektor::MyVektor(std::initializer_list<double> init)
{
	dimension = 0;

	for (auto item : init)
    {
		vektor.push_back(item);
		++dimension;
	}
}

void MyVektor::set_component(int index, double new_value) 
{ 
	if (index >= dimension)
		std::cout << "Index ungueltig." << std::endl;
	else
		vektor[index] = new_value;
}

double MyVektor::get_component(int index) const 
{ 
	if (index >= dimension)
		std::cout << "Index ungueltig." << std::endl;
	else
		return vektor[index];
}

double MyVektor::get_laenge()
{
	double temp = 0;
	for (auto item : vektor)
		temp += item * item;

	return sqrt(temp);
}

void MyVektor::log()
{
	std::cout << "( " << vektor[0];

	for (int i = 1; i < dimension; ++i)
		std::cout << " ; " << vektor[i];

	std::cout << " )" << std::endl;
}

/*std::string MyVektor::als_string()
{
	std::string s = "( ";

	s += std::to_string(vektor[0]);

	for (int i = 1; i < dimension; ++i) {
		s += " ; ";
		s += std::to_string(vektor[i]);
		std::cout << vektor[i] << std::endl;
	}

	return s + " )";
}*/

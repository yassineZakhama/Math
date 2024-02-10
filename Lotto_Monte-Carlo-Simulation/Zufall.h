#pragma once

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <map>
class CZufall
{
public:
	int wert(int a, int b);
	void initialisiere(int);
	std::map<int, int> test(int, int, int);
	std::map<int, int> test_falsch(int, int, int);

};
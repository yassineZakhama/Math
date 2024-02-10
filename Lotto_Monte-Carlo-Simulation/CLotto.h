#pragma once
#include "Zufall.h"
#include <vector>

class CLotto
{
private:
	CZufall zufall;
	int k;
	int n;
	std::vector<int> tippZettel;

public:
	CLotto(int _k, int _n, int s);

	void set_tippZettel(std::vector<int> zettel) { tippZettel = zettel; }

	std::vector<int> ziehung();

	int anzahl_richtige_zahlen();
};
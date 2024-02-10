#include "CLotto.h"

CLotto::CLotto(int _k, int _n, int s)
	: k{ _k }, n{ _n }
{
	if (s < 0)
		zufall.initialisiere(time(NULL));
	else
		zufall.initialisiere(s);
}

std::vector<int> CLotto::ziehung()
{
	std::vector<int> getippte_zahlen(k);
	bool es_gibt_duplikat = true;

	for (int i = 0; i < k; ++i) // k Zahlen erzeugen
	{
		int x;
		while (es_gibt_duplikat)
		{
			x = zufall.wert(1, n);

			es_gibt_duplikat = false;
			for (int j = 0; j < i; ++j) // vergleiche x mit bisher erzeugten Zahlen
			{
				if (getippte_zahlen[j] == x) // wenn x existiert -> neue Zahl generieren
				{
					es_gibt_duplikat = true; 
					break;
				}
			}
		}
		getippte_zahlen[i] = x;
		es_gibt_duplikat = true;
	}

	return getippte_zahlen;
}

int CLotto::anzahl_richtige_zahlen()
{
	std::vector<int> gezogen = ziehung();

	int count = 0;

	for (auto it1 : gezogen)
	{
		for (auto it2 : tippZettel)
		{
			if (it1 == it2)
			{
				count++;
				break;
			}
		}
	}
	return count;
}
#include <iostream>
#include "Zufall.h"
#include <iomanip>
#include <map>
#include "CLotto.h"

using namespace std;

void log(std::map<int, int> m)
{
	for (auto it : m)
		cout << it.first << " wurde " << it.second << " mal erzeugt." << endl;
}

void monte_carlo(int r, int k, int n, int N, int typ);
//==========================================================================
int main()
{
	
	bool random1 = true;
	if (random1)
	{
		// Die selben Zufallnummer werden immer erzeugt
		CZufall r1;
		
		cout << "Gleiche Seeds" << endl;
		for (int i = 0; i < 3; ++i)
		{
			r1.initialisiere(1);
			log(r1.test(3, 7, 10000));
			cout << endl;
		} 
	}

	bool random2 = true;
	if (random2)
	{
		// Verschiedene Zufallnummer werden erzeugt
		CZufall r2;

		cout << "Verschiedene Seeds" << endl;
		for (int i = 0; i < 3; ++i)
		{
			r2.initialisiere(i);
			log(r2.test(3, 7, 1000));
			cout << endl;
		}
	}

	bool random3 = true;
	if (random3)
	{
		// Verschiedene Zufallnummer werden erzeugt, aber nicht immer
		CZufall r3;

		cout << "Verschiedene Seeds" << endl;
		for (int i = 0; i < 3; ++i)
		{
			r3.initialisiere(time(NULL));
			log(r3.test(3, 7, 1000));
			cout << endl;
		}
	}

	bool random4 = true;
	if (random4)
	{
		// Fast immer wird die selbe nummer N mal erzeugt
		CZufall r4;

		cout << "Verschiedene Seeds" << endl;
		
			log(r4.test_falsch(3, 7, 1000));
			cout << endl;
		
	}

	//============
	// AUFGABE 3
	//============
	bool aufgabe3 = false;
	if (aufgabe3)
	{
		cout << "Ergebnis aus Praktikum e-Test:\t34,2194" << endl;

		cout << endl;
		cout << "Player 1 (nutzt immer den gleichen Tippzettel): ";
		monte_carlo(2, 8, 27, 100000, 1);

		cout << endl;
		cout << "Player 2 (jedes Mal neuer Tippzettel): ";
		monte_carlo(2, 8, 27, 100000, 2);
	}
}
//==========================================================================

void monte_carlo(int r, int k, int n, int N, int typ)
{
	int count = 0; // Counter fuer erfolgreiche Zahlen

	if (typ == 1) // immer der gleiche Tippzettel
	{
		CLotto player1(k,n,-1); 

		player1.set_tippZettel(player1.ziehung()); // zufaelliger Tippzettel setzen

		for (int i = 0; i < N; ++i)
			if (player1.anzahl_richtige_zahlen() == r)
				++count;
	}
	else // jedes mal neuer Tippzettel
	{
		CLotto player2(k, n, -1);	

		vector<int> tippZettel;
		for (int i = 0; i < N; ++i)
		{
			tippZettel = player2.ziehung(); // jedes mal neuer zufaelliger Tippzettel
			player2.set_tippZettel(tippZettel);

			if (player2.anzahl_richtige_zahlen() == r)
				++count;
		}
	}

	double wahrscheinlichkeit = double(count) * 100 / N;

	cout << wahrscheinlichkeit << endl;
}
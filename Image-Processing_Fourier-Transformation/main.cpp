#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "Komplex.h"

using namespace std;

vector<Komplex> werte_einlesen(const std::string dateiname);
void werte_ausgeben(const std::string dateiname, vector<Komplex> werte, double epsilon = -1.0);

vector<Komplex> fourier_trafo(const vector<Komplex> vec, bool hin_trafo = true);

void abweichung(vector<Komplex>& a, vector<Komplex>& b);
//=======================================================================

int main()
{
	
	vector<Komplex> v1 = werte_einlesen("daten1.txt");
	
	vector<Komplex> v2 = fourier_trafo(v1);
	werte_ausgeben("trafo.txt", v2);
	werte_ausgeben("trafo0,001.txt", v2, 0.001);
	werte_ausgeben("trafo0,01.txt", v2, 0.01);
	werte_ausgeben("trafo0,1.txt", v2, 0.1);
	werte_ausgeben("trafo1,0.txt", v2, 1.0);
	
	vector<Komplex> temp;
	vector<Komplex> rueck_trafo;

	temp = werte_einlesen("trafo.txt");
	rueck_trafo = fourier_trafo(temp, false);
	//werte_ausgeben("ruecktrafo.txt", rueck_trafo);
	//werte_ausgeben("ruecktrafo_10.txt", rueck_trafo);
	cout << "Bei Daten_original1.txt" << endl;
	cout << "Maximale Abweichung bei Standard-Epsilon: ca. ";
	abweichung(rueck_trafo, v1 );

	temp = werte_einlesen("trafo0,001.txt");
	rueck_trafo = fourier_trafo(temp, false);
	//werte_ausgeben("ruecktrafo_30.txt", rueck_trafo);
	cout << "Maximale Abweichung bei epsilon=0.001: ";
	abweichung(v1, rueck_trafo);

	temp = werte_einlesen("trafo0,01.txt");
	rueck_trafo = fourier_trafo(temp, false);
	//werte_ausgeben("ruecktrafo_100.txt", rueck_trafo);
	cout << "Maximale Abweichung bei epsilon=0.01: ";
	abweichung(v1, rueck_trafo);

	temp = werte_einlesen("trafo0,1.txt");
	rueck_trafo = fourier_trafo(temp, false);
	//werte_ausgeben("ruecktrafo_300.txt", rueck_trafo);
	cout << "Maximale Abweichung bei epsilon=0.1: ";
	abweichung(v1, rueck_trafo);

	temp = werte_einlesen("trafo1,0.txt");
	rueck_trafo = fourier_trafo(temp, false);
	//werte_ausgeben("ruecktrafo_300.txt", rueck_trafo);
	cout << "Maximale Abweichung bei epsilon=1: ";
	abweichung(v1, rueck_trafo);
	
	
	vector<Komplex> z1 = werte_einlesen("ruecktrafo.txt");
	vector<Komplex> z2 = werte_einlesen("ruecktrafo0,001.txt");
	vector<Komplex> z3 = werte_einlesen("ruecktrafo0,01.txt");
	vector<Komplex> z4 = werte_einlesen("ruecktrafo0,1.txt");
	vector<Komplex> z5 = werte_einlesen("ruecktrafo1,0.txt");
	cout << "Bei Daten_original1.txt" << endl;
	cout << "Maximale Abweichung bei Standard-Epsilon: ca. ";
	abweichung(v1, z1);
	cout << "Maximale Abweichung bei epsilon=0.001: ";
	abweichung(v1, z2);
	cout << "Maximale Abweichung bei epsilon=0.01: ";
	abweichung(v1, z3);
	cout << "Maximale Abweichung bei epsilon=0.1: ";
	abweichung(v1, z4);
	cout << "Maximale Abweichung bei epsilon=1: ";
	abweichung(v1, z5);
	
	vector<Komplex> v_1 = werte_einlesen("daten2.txt");
	
	vector<Komplex> v_2 = fourier_trafo(v_1);
	//werte_ausgeben("trafo_zweite.txt", v_2, 0);

	vector<Komplex> v_3 = fourier_trafo(v_2, false);
	
	werte_ausgeben("ruecktrafo_zweite.txt", v_3);
	werte_ausgeben("ruecktrafo0,001_zweite.txt", v_3, 0.001);
	werte_ausgeben("ruecktrafo0,01_zweite.txt", v_3, 0.01);
	werte_ausgeben("ruecktrafo0,1_zweite.txt", v_3, 0.1);
	werte_ausgeben("ruecktrafo1,0_zweite.txt", v_3, 1.0);
	
	vector<Komplex> z_1 = werte_einlesen("ruecktrafo_zweite.txt");
	vector<Komplex> z_2 = werte_einlesen("ruecktrafo0,001_zweite.txt");
	vector<Komplex> z_3 = werte_einlesen("ruecktrafo0,01_zweite.txt");
	vector<Komplex> z_4 = werte_einlesen("ruecktrafo0,1_zweite.txt");
	vector<Komplex> z_5 = werte_einlesen("ruecktrafo1,0_zweite.txt");
	cout << "Bei Daten_original2.txt" << endl;
	cout << "Maximale Abweichung bei Standard-Epsilon: ca. ";
	abweichung(v_1, z_1);
	cout << "Maximale Abweichung bei epsilon=0.001: ";
	abweichung(v_1, z_2);
	cout << "Maximale Abweichung bei epsilon=0.01: ";
	abweichung(v_1, z_3);
	cout << "Maximale Abweichung bei epsilon=0.1: ";
	abweichung(v_1, z_4);
	cout << "Maximale Abweichung bei epsilon=1: ";
	abweichung(v_1, z_5);
	
	
	vector<Komplex> bild = werte_einlesen("bild.txt");
	
	vector<Komplex> trafo = fourier_trafo(bild);

	//werte_ausgeben("trafo_default.txt", trafo);
	werte_ausgeben("trafo_10.txt", trafo, 10);
	werte_ausgeben("trafo_30.txt", trafo, 30);
	werte_ausgeben("trafo_100.txt", trafo, 100);
	werte_ausgeben("trafo_300.txt", trafo, 300);
	
	vector<Komplex> temp;
	vector<Komplex> rueck_trafo; 

	temp = werte_einlesen("trafo_10.txt");
	rueck_trafo = fourier_trafo(temp, false);
	werte_ausgeben("ruecktrafo_10.txt", rueck_trafo);

	temp = werte_einlesen("trafo_30.txt");
	rueck_trafo = fourier_trafo(temp, false);
	werte_ausgeben("ruecktrafo_30.txt", rueck_trafo);

	temp = werte_einlesen("trafo_100.txt");
	rueck_trafo = fourier_trafo(temp, false);
	werte_ausgeben("ruecktrafo_100.txt", rueck_trafo);

	temp = werte_einlesen("trafo_300.txt.txt");
	rueck_trafo = fourier_trafo(temp, false);
	werte_ausgeben("ruecktrafo_300.txt", rueck_trafo);
	
}

//=======================================================================
vector<Komplex> werte_einlesen(const std::string dateiname)
{
	int i, N, idx;
	double re, im;

	vector<Komplex> werte;

	// File oeffnen
	ifstream fp;
	fp.open(dateiname);

	// Dimension einlesen
	fp >> N;

	// Werte-Vektor anlegen
	werte.resize(N);
	Komplex null(0, 0);
	for (i = 0; i < N; i++)
		werte[i] = null;
	// Eintraege einlesen und im Werte-Vektor ablegen
	while (!fp.eof())
	{
		fp >> idx >> re >> im;
		Komplex a(re, im);
		werte[idx] = a;
	}
	// File schliessen
	fp.close();

	return werte;
}

void werte_ausgeben(const std::string dateiname, vector<Komplex> werte, double epsilon)
{
	int i;
	int N = werte.size();
	// File oeffnen
	ofstream fp;
	fp.open(dateiname);
	// Dimension in das File schreiben
	fp << N << endl;
	// Eintraege in das File schreiben
	fp.precision(10);
	for (i = 0; i < N; i++)
		if (werte[i].abs() > epsilon)
			fp << i << "\t" << werte[i].re() << "\t" << werte[i].im() << endl;
	// File schliessen
	fp.close();
}

vector<Komplex> fourier_trafo(const vector<Komplex> vec, bool hin_trafo)
{
	double N = static_cast<double>(vec.size());
	double faktor = 1 / sqrt(N);

	if (hin_trafo) // vec hat die Fk's
	{
		vector<Komplex> Cn(N);

		for (size_t n = 0; n < N; ++n)
		{
			for (size_t k = 0; k < N; ++k)
			{
				Komplex Z( n * (-2.0)* M_PI* k / N );
			
				Cn[n] = Cn[n] + ((Z * vec[k]) * faktor);
			}
		}

		return Cn;
	}
	else // vec hat die Cn's
	{
		vector<Komplex> Fk(N);

		for (size_t k = 0; k < N; ++k)
		{
			for (size_t n = 0; n < N; ++n)
			{
				Komplex Z(n * 2.0 * M_PI * k / N);

				Fk[k] = Fk[k] + ((Z * vec[n]) * faktor);
			}
		}

		return Fk;
	}
}
void abweichung(vector<Komplex>& a, vector<Komplex>& b)
{
	Komplex temp;
	double max_abw = 0.0;
	if (a.size() == b.size())
	{
		for (int i = 0; i < a.size(); i++)
		{
			temp = (a[i] - b[i]);
			if (max_abw < temp.abs())
			{
				max_abw = temp.abs();
			}
		}
	}
	cout << max_abw << endl;
}
#pragma once
#include "MyVektor.h"

class DGLSolver
{
private:
	bool erste_ordnung;

	MyVektor(*f_DGL_System)(MyVektor y, double x);
	double (*f_DGL_nterOrdnung)(MyVektor y, double x);

	MyVektor ableitungen(MyVektor y, double x);

public:
	DGLSolver(MyVektor(*_f_DGL_System)(MyVektor y, double x))
		: erste_ordnung{ true }, f_DGL_System{ _f_DGL_System }, f_DGL_nterOrdnung{ nullptr } {}

	DGLSolver(double (*_f_DGL_nterOrdnung)(MyVektor y, double x))
		: erste_ordnung{ false }, f_DGL_System{ nullptr }, f_DGL_nterOrdnung{ _f_DGL_nterOrdnung } {}

	bool get_erste_ordnung() const { return erste_ordnung; }
	void set_erste_ordnung(bool b) { erste_ordnung = b; }

	void euler_heun_verfahren(double x_start, double x_end, MyVektor y_start);
};
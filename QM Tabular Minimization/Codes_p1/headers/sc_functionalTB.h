// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 3
// Revision: 2021-05-3

#ifndef __SC_FUNCTIONALTB__H
#define __SC_FUNCTIONALTB__H "sc_functionalTB.h"

#include "sc_functional.h"

SC_MODULE(SC_FUNCTIONALTB)
{
	sc_signal<sc_logic> a, b, c, d, s;
	sc_signal<sc_logic> o;

	SC_FUNCTIONAL* sc_f;

	SC_CTOR(SC_FUNCTIONALTB)
	{
		sc_f = new SC_FUNCTIONAL("assign_statements");
			sc_f->a(a);
			sc_f->b(b);
			sc_f->c(c);
			sc_f->d(d);
			sc_f->s(s);
			sc_f->o(o);


		SC_THREAD(inGenerating);
		SC_THREAD(Displaying);
			sensitive << o;
	}

	void inGenerating();
	void Displaying();
};

#endif
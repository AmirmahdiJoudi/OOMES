// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 3
// Revision: 2021-05-3

#ifndef __SC_FUNCTIONAL__H
#define __SC_FUNCTIONAL__H "sc_functional.h"

#include <systemc.h>

SC_MODULE(SC_FUNCTIONAL)
{
	sc_in<sc_logic> a, b, c, d, s;
	sc_out<sc_logic> o;

	sc_signal<sc_logic> w, f, g;

	SC_CTOR(SC_FUNCTIONAL)
	{
		SC_THREAD(evl_w);
			sensitive << a << b << c << d;
		SC_THREAD(evl_f);
			sensitive << w << b << c << d;
		SC_THREAD(evl_g);
			sensitive << a << b << c << d;
		SC_THREAD(evl_o);
			sensitive << s << g << f;
	}
	
	void evl_w();
	void evl_f();
	void evl_g();
	void evl_o();
};



#endif
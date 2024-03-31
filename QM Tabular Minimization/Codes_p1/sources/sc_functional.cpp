// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 3
// Revision: 2021-05-3

#include "sc_functional.h"
#include <iostream>

using namespace std;
using namespace sc_core;

void SC_FUNCTIONAL::evl_w()
{
	while(true)
	{
		wait(10, SC_NS);
		sc_logic aa = a->read().value();
		sc_logic bb = b->read().value();
		sc_logic cc = c->read().value();
		sc_logic dd = d->read().value();
		w = ~aa&~bb&~cc&~dd | ~aa&~bb&~cc&dd | ~aa&~bb&cc&~dd | ~aa&bb&~cc&dd | ~aa&bb&cc&~dd | ~aa&bb&cc&dd | aa&~bb&~cc&~dd | aa&~bb&~cc&dd | aa&~bb&cc&~dd | aa&bb&cc&~dd;
		wait();
	}
}

void SC_FUNCTIONAL::evl_f()
{
	while(true)
	{
		wait(12, SC_NS);
		sc_logic ww = w;
		sc_logic bb = b->read().value();
		sc_logic cc = c->read().value();
		sc_logic dd = d->read().value();
		f = ~ww&~bb&cc&~dd | ~ww&bb&cc&~dd | ww&~bb&~cc&~dd | ww&~bb&~cc&dd | ww&~bb&cc&~dd | ww&~bb&cc&dd | ww&bb&cc&~dd | ww&bb&cc&dd;
		wait();
	}
}

void SC_FUNCTIONAL::evl_g()
{
	while(true)
	{
		wait(14, SC_NS);
		sc_logic aa = a->read().value();
		sc_logic bb = b->read().value();
		sc_logic cc = c->read().value();
		sc_logic dd = d->read().value();
		g = ~aa&~bb&~cc&~dd | ~aa&~bb&cc&dd | ~aa&bb&~cc&dd | ~aa&bb&cc&~dd | ~aa&bb&cc&dd | aa&~bb&cc&~dd | aa&~bb&cc&dd | aa&bb&~cc&dd;
		wait();
	}
}

void SC_FUNCTIONAL::evl_o()
{
	while(true)
	{
		wait(5, SC_NS);
		if(s == SC_LOGIC_1)
			o = g;
		else
			o = f;
		wait();		
	}
}
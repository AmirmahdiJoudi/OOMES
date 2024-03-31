#ifndef __CONTROLLER__H
#define __CONTROLLER__H "controller.h"

#include <systemc.h>

SC_MODULE(Controller)
{
	sc_in<sc_logic> clk, rst;
	sc_in<sc_logic> push, pop, tos, ready;
	sc_out<sc_logic> en, memWrite, memRead, inc, dec, ldRin, ldRout, ld;

	enum states {WAITING, PUSHING1, PUSHING2, POPING1, POPING2, POPING3, TOSING1, TOSING2, TOSING3};
	sc_signal<states> PState, NState;

	SC_CTOR(Controller)
	{
		SC_METHOD(Combinational_one);
			sensitive << push << pop << tos << ready << PState;
		SC_METHOD(Combinational_two);
			sensitive << PState;
		SC_METHOD(Sequential);
			sensitive << clk << rst;
	}

	void Combinational_one();
	void Combinational_two();
	void Sequential();
};

#endif
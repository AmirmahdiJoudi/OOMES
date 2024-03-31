#ifndef __COUNTER__H
#define __COUNTER__H "counter.h"

#include <systemc.h>

SC_MODULE(Counter)
{
	sc_in<sc_logic> clk, rst, inc, dec;
	sc_out<sc_lv<9>> count;

	SC_CTOR(Counter)
	{
		SC_METHOD(counting);
			sensitive << clk << rst;
	}

	void counting();
};

#endif
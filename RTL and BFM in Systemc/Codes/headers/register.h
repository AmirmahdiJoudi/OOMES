#ifndef __REGISTER__H
#define __REGISTER__H "register.h"

#include <systemc.h>

SC_MODULE(Register)
{
	sc_in<sc_logic> clk, rst, ldRin;
	sc_in<sc_lv<16>> dataIn;
	sc_out<sc_lv<16>> dataOut;

	SC_CTOR(Register)
	{
		SC_METHOD(registering);
			sensitive << clk << rst;
	}

	void registering();
};

#endif
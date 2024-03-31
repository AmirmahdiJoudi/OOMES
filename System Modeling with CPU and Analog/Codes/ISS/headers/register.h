#ifndef __REGISTER__H
#define __REGISTER__H "register.h"

#include <systemc.h>

SC_MODULE(Register)
{
	sc_in<sc_logic> clk, rst, outEnable;
	sc_in<sc_lv<16>> dataIn;
	sc_out<sc_lv<16>> dataOut;

	sc_signal<sc_lv<16>> out;

	SC_CTOR(Register)
	{
		SC_METHOD(registering);
			sensitive << clk << rst;
		SC_METHOD(outputControl);
			sensitive << outEnable << out;
	}

	void registering();
	void outputControl();
};

#endif
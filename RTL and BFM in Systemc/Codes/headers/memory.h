#ifndef __MEMORY__H
#define __MEMORY__H "memory.h"

#include <systemc.h>

SC_MODULE(Memory)
{
	sc_in<sc_logic> clk, memWrite, memRead;
	sc_in<sc_lv<9>> address;
	sc_inout<sc_lv<16>> dataInOut;

	sc_lv<16> mem[512];

	SC_CTOR(Memory)
	{
		SC_THREAD(reading);
			sensitive << memRead << address;
		SC_THREAD(writing);
			sensitive << memWrite << address << dataInOut;
	}

	void reading();
	void writing();

};

#endif
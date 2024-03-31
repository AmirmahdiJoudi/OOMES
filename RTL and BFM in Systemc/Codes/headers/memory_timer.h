#ifndef __MEMORY_TIMER_H
#define __MEMORY_TIMER_H "memory_timer.h"

#include <systemc.h>

SC_MODULE(MemoryTimer)
{
	sc_in<sc_logic> clk, rst, ld, en;
	sc_in<sc_lv<3>> pin;
	sc_out<sc_logic> memReady;

	sc_lv<3> count;

	SC_CTOR(MemoryTimer)
	{
		SC_THREAD(counting);
			sensitive << clk << rst;
	}

	void counting();

};

#endif
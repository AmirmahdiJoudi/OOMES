#ifndef __FUNCTIONAL_MEMORY_TIMER_H
#define __FUNCTIONAL_MEMORY_TIMER_H "functioal_memory_timer.h"

#include <systemc.h>

SC_MODULE(FunctionalMemoryTimer)
{
	sc_in<sc_logic> clk, en;
	sc_out<sc_logic> memReady;

	SC_CTOR(FunctionalMemoryTimer)
	{
		SC_THREAD(counting);
			sensitive << en;
	}

	void counting();

};

#endif
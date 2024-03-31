#ifndef __TIMER__
#define __TIMER__ "timer.h"

#include <systemc.h>

SC_MODULE(timer)
{
	sc_in<sc_logic> startTimer;
	sc_in<sc_logic> en;
	sc_out<sc_logic> timeOut;

	sc_signal<sc_logic> out;

	SC_CTOR(timer)
	{
		SC_THREAD(starting);
			sensitive << startTimer;
		SC_METHOD(outputControl);
			sensitive << en << out;
	}

	void starting();
	void outputControl();
};

#endif
#ifndef __DISPLAY__
#define __DISPLAY__ "Display.h"

#include <systemc.h>

SC_MODULE(Display)
{
	sc_in<sc_logic> data;
	sc_in<sc_logic> en;

	SC_CTOR(Display)
	{
		SC_THREAD(Displaying);
			sensitive << data << en;;
	}

	void Displaying();
};

#endif
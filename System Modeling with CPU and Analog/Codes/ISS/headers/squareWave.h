#ifndef __SQUAREWAVE__
#define __SQUAREWAVE__ "squareWave.h"

#include <systemc.h>

SC_MODULE(squareWave)
{
	sc_out<double> out;

	double T;
	bool form;

	SC_HAS_PROCESS(squareWave);
	squareWave(sc_module_name name, double _T, bool _form = false) : T(_T), form(_form)
	{
		SC_THREAD(wave);
	}

	void wave();
};

#endif

#include "timer.h"

void timer::starting()
{
	if(startTimer != SC_LOGIC_1)
		wait();
	if(startTimer == SC_LOGIC_1)
		wait();
	out = SC_LOGIC_0;
	wait(1, SC_MS);
	out = SC_LOGIC_1;
	wait(20, SC_NS);
	out = SC_LOGIC_0;
	while(true)
	{
		wait(999980, SC_NS);
		out = SC_LOGIC_1;
		wait(20, SC_NS);
		out = SC_LOGIC_0;
	}
}

void timer::outputControl()
{
	if(en == SC_LOGIC_1)
		timeOut = out;
	else
		timeOut = SC_LOGIC_Z;
}

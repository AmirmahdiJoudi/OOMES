#include "sensor2FrontEnd.h"

void Sensor2FrontEnd::clocking()
{
	rst = SC_LOGIC_1;
	wait(2, SC_NS);
	rst = SC_LOGIC_0;
	wait(2, SC_NS);
	while(true)
	{
		clk = SC_LOGIC_1;
		wait(250, SC_NS);
		clk = SC_LOGIC_0;
		wait(250, SC_NS);
	}
}
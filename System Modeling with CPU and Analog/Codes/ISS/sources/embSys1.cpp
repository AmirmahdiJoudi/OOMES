#include "embSys1.h"

void embSys1::clocking()
{
	while(true)
	{
		clk = SC_LOGIC_0;
		wait(10, SC_NS);
		clk = SC_LOGIC_1;
		wait(10, SC_NS);
	}
}
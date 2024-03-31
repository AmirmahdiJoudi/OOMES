#include "memory_timer.h"

void MemoryTimer::counting()
{
	while(true)
	{
		if(rst == SC_LOGIC_1)
		{
			count = "000";
			memReady = SC_LOGIC_0;
		}
		else if(clk->event() && clk == SC_LOGIC_1)
			if(ld == SC_LOGIC_1)
				count = pin;
			else if(en == SC_LOGIC_1)
				count = count.to_uint() + 1;
		if(count == "111")
			memReady = SC_LOGIC_1;
		else
			memReady = SC_LOGIC_0;
		wait();
	}	
}

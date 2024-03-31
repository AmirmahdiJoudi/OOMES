#include "functional_memory_timer.h"

void FunctionalMemoryTimer::counting()
{
	while(true)
	{
		memReady = SC_LOGIC_0;
		if(en == SC_LOGIC_1)
		{
			for(int i = 0; i < 5; i++)
				wait(clk->posedge_event());
			memReady = SC_LOGIC_1;
		}
		wait();
	}	
}

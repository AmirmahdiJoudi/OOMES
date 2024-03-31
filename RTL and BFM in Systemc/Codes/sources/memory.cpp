#include "memory.h"

void Memory::reading()
{
	while(true)
	{
		if(memRead == SC_LOGIC_1)
		{
			for(int i = 0; i < 5; i++)
				wait(clk->posedge_event());
			dataInOut = mem[address->read().to_uint()];
		}
		wait();
	}
}

void Memory::writing()
{
	while(true)
	{
		if(memWrite == SC_LOGIC_1)
		{
			for(int i = 0; i < 5; i++)
				wait(clk->posedge_event());
			mem[address->read().to_uint()] = dataInOut;
		}
		wait();
	}
}
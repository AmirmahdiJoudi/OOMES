#include "functional_stack_handler.h"

void FunctionalStackHandler::manage_system()
{
	while(true)
	{
		if(rst == SC_LOGIC_1)
		{
			dataOut = "0000000000000000";
			count = 0;
		}
		else
		{
			if(push == SC_LOGIC_1)
			{
				adr = (sc_lv<9>)count;
				memR = dataIn;
				memWrite = SC_LOGIC_1;
				while(memReady != SC_LOGIC_1)
					wait(clk->posedge_event());
				memWrite = SC_LOGIC_0;
				wait(clk->posedge_event());
				count = count + 1;	
			}
			else if(pop == SC_LOGIC_1)
			{
				int n = count - 1;	
				adr = (sc_lv<9>)n;
				memRead = SC_LOGIC_1;
				while(memReady != SC_LOGIC_1)
					wait(clk->posedge_event());
				memRead = SC_LOGIC_0;
				wait(clk->posedge_event());
				count = n;
				dataOut = memR;			
			}
			else if(tos == SC_LOGIC_1)
			{
				int n = count - 1;	
				adr = (sc_lv<9>)n;
				memRead = SC_LOGIC_1;
				while(memReady != SC_LOGIC_1)
					wait(clk->posedge_event());
				memRead = SC_LOGIC_0;
				wait(clk->posedge_event());
				dataOut = memR;	
			}
		}
		wait();
	}
} 

void FunctionalStackHandler::manage_signs()
{
	if(count == 0)
		empty = SC_LOGIC_1;
	else if(count == 512)
		full = SC_LOGIC_1;
	else
	{
		empty = SC_LOGIC_0;
		full = SC_LOGIC_0;
	}
} 

void FunctionalStackHandler::set_enable()
{
	if(memRead == SC_LOGIC_1 || memWrite == SC_LOGIC_1)
		en = SC_LOGIC_1;
	else
		en = SC_LOGIC_0;
}
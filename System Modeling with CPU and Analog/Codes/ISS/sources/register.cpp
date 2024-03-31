#include "register.h"

void Register::registering()
{
	if(rst == SC_LOGIC_1)
		out = "0000000000000000";
	else if(clk->event() && clk == SC_LOGIC_1)
		out = dataIn;
}

void Register::outputControl()
{
	if(outEnable == SC_LOGIC_1)
		dataOut = out;
	else
		dataOut = "ZZZZZZZZZZZZZZZZ";
}
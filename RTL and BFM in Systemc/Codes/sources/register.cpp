#include "register.h"

void Register::registering()
{
	if(rst == SC_LOGIC_1)
		dataOut = "0000000000000000";
	else if(clk->event() && clk == SC_LOGIC_1)
		if(ldRin == SC_LOGIC_1)
			dataOut = dataIn;
		else
			dataOut = dataOut;
}
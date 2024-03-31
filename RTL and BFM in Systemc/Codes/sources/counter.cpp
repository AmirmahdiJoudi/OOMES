#include "counter.h"

void Counter::counting()
{
	if(rst == SC_LOGIC_1)
		count = "000000000";
	else if(clk->event() && clk == SC_LOGIC_1)
		if(inc == SC_LOGIC_1)
			count = count->read().to_uint() + 1;
		else if(dec == SC_LOGIC_1)
			count = count->read().to_uint() - 1;
}
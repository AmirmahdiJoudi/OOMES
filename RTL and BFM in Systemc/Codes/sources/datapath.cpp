#include "datapath.h"

void DataPath::DataPath_Assign()
{
	pin = "011";
	while(true)
	{
		full = (count.read() == "1111111111111111") ? SC_LOGIC_1 : SC_LOGIC_0;
		empty = (count.read() == "0000000000000000") ? SC_LOGIC_1 : SC_LOGIC_0;
		adr = count;
		if(memWrite == SC_LOGIC_1)
			memR = RDataIn;
		if(memRead == SC_LOGIC_1)
			RDataOut = memR;
		wait();
	}
}
#include "controller.h"

void Controller::Combinational_one()
{
	NState = WAITING;
	switch(PState)
	{
		case WAITING:
			if(push == SC_LOGIC_1)
				NState = PUSHING1;
			else if(pop == SC_LOGIC_1)
				NState = POPING1;
			else if(tos == SC_LOGIC_1)
				NState = TOSING1;
			break;
		case PUSHING1:
			if(ready == SC_LOGIC_1)
				NState = PUSHING2;
			else
				NState = PUSHING1;
			break;
		case PUSHING2:
			NState = WAITING;
			break;
		case POPING1:
			NState = POPING2;
			break;
		case POPING2:
			if(ready == SC_LOGIC_1)
				NState = POPING3;
			else
				NState = POPING2;
			break;
		case POPING3:
			NState = WAITING;
			break;
		case TOSING1:
			NState = TOSING2;
			break;
		case TOSING2:
			if(ready == SC_LOGIC_1)
				NState = TOSING3;
			else
				NState = TOSING2;
			break;
		case TOSING3:
			NState = WAITING;
			break;
	}
}

void Controller::Combinational_two()
{
	en = SC_LOGIC_0;
	memWrite = SC_LOGIC_0;
	memRead = SC_LOGIC_0;
	inc = SC_LOGIC_0;
	dec = SC_LOGIC_0;
	ldRin = SC_LOGIC_0;
	ldRout = SC_LOGIC_0;
	ld = SC_LOGIC_0;
	switch(PState)
	{
		case WAITING:
			ld = SC_LOGIC_1;
			ldRin = SC_LOGIC_1;
			break;
		case PUSHING1:
			en = SC_LOGIC_1;
			memWrite = SC_LOGIC_1;
			break;
		case PUSHING2:
			inc = SC_LOGIC_1;
			break;
		case POPING1:
			dec = SC_LOGIC_1;
			memRead = SC_LOGIC_1;
			en = SC_LOGIC_1;
			break;
		case POPING2:
			memRead = SC_LOGIC_1;
			en = SC_LOGIC_1;
			break;
		case POPING3:
			ldRout = SC_LOGIC_1;
			break;
		case TOSING1:
			dec = SC_LOGIC_1;
			memRead = SC_LOGIC_1;
			en = SC_LOGIC_1;
			break;
		case TOSING2:
			memRead = SC_LOGIC_1;
			en = SC_LOGIC_1;
			break;
		case TOSING3:
			ldRout = SC_LOGIC_1;
			inc = SC_LOGIC_1;
			break;
	}	
}

void Controller::Sequential()
{
	if(rst == SC_LOGIC_1)
		PState = WAITING;
	else if(clk->event() && clk == SC_LOGIC_1)
		PState = NState;
}
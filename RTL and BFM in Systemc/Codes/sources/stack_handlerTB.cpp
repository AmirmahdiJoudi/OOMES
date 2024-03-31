#include "stack_handlerTB.h"
#include <iostream>

using namespace std;

void StackHandlerTB::Clocking()
{
	while(true)
	{
		for(int i = 0; i < 1000; i++)
		{
			wait(10, SC_NS);
			clk = SC_LOGIC_1;
			wait(10, SC_NS);
			clk = SC_LOGIC_0;
		}
		wait();
	}	
}

void StackHandlerTB::Reseting()
{
	while(true)
	{
		rst = SC_LOGIC_1;
		wait(15, SC_NS);
		rst = SC_LOGIC_0;
		wait();
	}
}

void StackHandlerTB::Inputting()
{
	while(true)
	{
		push = SC_LOGIC_1;
		dataIn = "0000000011111111";
		wait(120, SC_NS);
		dataIn = "0000000011111110";
		wait(120, SC_NS);
		dataIn = "0000000011111100";
		wait(120, SC_NS);
		dataIn = "0000000011111000";
		wait(120, SC_NS);
		dataIn = "0000000011110000";
		wait(120, SC_NS);
		push = SC_LOGIC_0;
		tos = SC_LOGIC_1;
		wait(120, SC_NS);
		tos = SC_LOGIC_0;
		wait(20, SC_NS);
		pop = SC_LOGIC_1;
		wait(120, SC_NS);
		wait(120, SC_NS);
		pop = SC_LOGIC_0;
		push = SC_LOGIC_1;
		dataIn = "1111111111111000";
		wait(120, SC_NS);
		push = SC_LOGIC_1;
		dataIn = "1111111111111100";
		wait(120, SC_NS);
		push = SC_LOGIC_1;
		dataIn = "1111111111111110";
		wait(120, SC_NS);
		push = SC_LOGIC_0;
		wait(20, SC_NS);
		pop = SC_LOGIC_1;
		wait(120, SC_NS);
		wait(120, SC_NS);
		pop = SC_LOGIC_0;
		wait();
	}
}

void StackHandlerTB::StructuralDisplaying()
{
	while(true)
	{
		cout << "Structural:"<<endl;
		cout << "Data is ready at: "<<sc_time_stamp()<<endl;
		cout << "Data is "<< dataOut.read() <<endl;
		wait();
	}
}

void StackHandlerTB::FunctionalDisplaying()
{
	while(true)
	{
		cout << "Functional:"<<endl;
		cout << "Data is ready at: "<<sc_time_stamp()<<endl;
		cout << "Data is "<< dataOut.read() <<endl;
		wait();
	}
}

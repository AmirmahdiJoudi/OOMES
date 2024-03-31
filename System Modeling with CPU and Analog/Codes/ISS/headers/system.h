#include <iostream>
#include "ISSV6.h"
#include "Memory.h"
#include "systemc-2.3.2/include/systemc.h"

template <int adrBit, int dataBit>
SC_MODULE (embsystem)
{
public:
	sc_in <sc_logic> clk;

	sc_signal <sc_logic> memReady, readMem, writeMem;
	sc_signal <sc_logic> CS;

	sc_signal <sc_logic> readIO, writeIO;
	sc_signal <sc_lv <16>> addrBus;
	sc_signal <sc_lv<16>, SC_MANY_WRITERS> dataBus; 

	sc_signal <sc_lv <16>> dataBusOut,  addrBus2, dataBus2;
	sc_signal <sc_logic> readMem2, writeMem2, readIO2, writeIO2, memReady2, active, act;

	sayacInstruction<16, 4, 16, 3> *sayacInstructionModuleEmb;
	memory <16,16> *memoryModule;

	SC_CTOR(embsystem)
	{
		sayacInstructionModuleEmb = new sayacInstruction<16, 4, 16, 3>("sayacInstructionSetModuleEmb");
		(*sayacInstructionModuleEmb)
		(
			clk, memReady, dataBus, readMem, writeMem, readIO, writeIO, addrBus
		);
		
		memoryModule = new memory <16, 16>("memoryModule");
		(*memoryModule)(clk, readMem, writeMem, CS, addrBus, dataBus, memReady, dataBus);

		SC_METHOD (Modeling);
			sensitive << clk;
	}
	void Modeling();


};

template <int adrBit, int dataBit>
void embsystem<adrBit, dataBit>::Modeling()
{
	CS = SC_LOGIC_1;
}
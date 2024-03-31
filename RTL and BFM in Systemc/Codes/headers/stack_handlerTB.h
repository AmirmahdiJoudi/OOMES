#ifndef __STACK_HANDLERTB__H
#define __STACK_HANDLERTB__H "stack_handlerTB.h"

#include <systemc.h>

#include "stack_handler.h"
#include "functional_stack_handler.h"

SC_MODULE(StackHandlerTB)
{
	sc_signal<sc_logic> clk, rst, push, pop, tos;
	sc_signal<sc_lv<16>> dataIn, dataOut, fdataOut;
	sc_signal<sc_logic> full, ffull, empty, fempty;

	StackHandler *SH;
	FunctionalStackHandler *FSH;

	SC_CTOR(StackHandlerTB)
	{
		SH = new StackHandler("StackHandler");
			SH->clk(clk);
			SH->rst(rst);
			SH->push(push);
			SH->pop(pop);
			SH->tos(tos);
			SH->dataIn(dataIn);
			SH->dataOut(dataOut);
			SH->full(full);
			SH->empty(empty);
		FSH = new FunctionalStackHandler("FunctionalStackHandler");
			FSH->clk(clk);
			FSH->rst(rst);
			FSH->push(push);
			FSH->pop(pop);
			FSH->tos(tos);
			FSH->dataIn(dataIn);
			FSH->dataOut(fdataOut);
			FSH->full(ffull);
			FSH->empty(fempty);
		SC_THREAD(Clocking);
		SC_THREAD(Reseting);
		SC_THREAD(Inputting);
		SC_THREAD(StructuralDisplaying);
			sensitive << dataOut;
		SC_THREAD(FunctionalDisplaying);
			sensitive << fdataOut;
	}

	void Clocking();
	void Reseting();
	void Inputting();
	void StructuralDisplaying();
	void FunctionalDisplaying();
};

#endif
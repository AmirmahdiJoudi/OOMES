#ifndef __FUNCTIONAL_STACK_HANDLER__H
#define __FUNCTIONAL_STACK_HANDLER__H "functional_stack_handler.h"

#include <systemc.h>
#include "functional_memory_timer.h"
#include "memory.h"

SC_MODULE(FunctionalStackHandler)
{
	sc_in<sc_logic> clk, rst, push, pop, tos;
	sc_in<sc_lv<16>> dataIn;
	sc_out<sc_logic> full, empty;
	sc_out<sc_lv<16>> dataOut;

	Memory *mem;

	sc_signal<sc_logic> en, memWrite, memRead, memReady;
	sc_signal<sc_lv<9>> adr;
	sc_signal<sc_lv<16>, SC_MANY_WRITERS> memR;

	sc_signal<int> count;

	FunctionalMemoryTimer *FMT;

	SC_CTOR(FunctionalStackHandler)
	{
		mem = new Memory("FunctionalStackMemory");
			mem->clk(clk);
			mem->memWrite(memWrite);
			mem->memRead(memRead);
			mem->address(adr);
			mem->dataInOut(memR);
		FMT = new FunctionalMemoryTimer("FunctionalMemoryTimer");
			FMT->clk(clk);
			FMT->en(en);
			FMT->memReady(memReady);
		SC_THREAD(manage_system);
			sensitive << push << pop << tos << rst << clk; 
		SC_METHOD(manage_signs);
			sensitive << count;
		SC_METHOD(set_enable);
			sensitive << memRead << memWrite;
	}

	void manage_system();
	void manage_signs();
	void set_enable();
};

#endif
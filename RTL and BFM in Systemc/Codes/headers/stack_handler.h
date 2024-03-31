#ifndef __STACK_HANDLER__H
#define __STACK_HANDLER__H "stack_handler.h"

#include <systemc.h>
#include "datapath.h"
#include "controller.h"

SC_MODULE(StackHandler)
{
	sc_in<sc_logic> clk, rst, push, pop, tos;
	sc_in<sc_lv<16>> dataIn;
	sc_out<sc_logic> full, empty;
	sc_out<sc_lv<16>> dataOut;

	DataPath *DP;
	Controller *CU;

	sc_signal<sc_logic> inc, dec, ldRin, ldRout, memRead, memWrite, ld, en, ready;

	SC_CTOR(StackHandler)
	{
		DP = new DataPath("StackHandlerDataPath");
			DP->clk(clk);
			DP->rst(rst);
			DP->inc(inc);
			DP->dec(dec);
			DP->ldRin(ldRin);
			DP->ldRout(ldRout);
			DP->memRead(memRead);
			DP->memWrite(memWrite);
			DP->ld(ld);
			DP->en(en);
			DP->dataIn(dataIn);
			DP->full(full);
			DP->empty(empty);
			DP->ready(ready);
			DP->dataOut(dataOut);
		CU = new Controller("StackHandlerController");
			CU->clk(clk);
			CU->rst(rst);
			CU->push(push);
			CU->pop(pop);
			CU->tos(tos);
			CU->ready(ready);
			CU->en(en);
			CU->memWrite(memWrite);
			CU->memRead(memRead);
			CU->inc(inc);
			CU->dec(dec);
			CU->ldRin(ldRin);
			CU->ldRout(ldRout);
			CU->ld(ld);
	}
};

#endif
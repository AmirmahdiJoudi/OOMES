#ifndef __DATAPATH__H
#define __DATAPATH__H "datapath.h"

#include <systemc.h>

#include "memory.h"
#include "counter.h"
#include "register.h"
#include "memory_timer.h"

SC_MODULE(DataPath)
{
	sc_in<sc_logic> clk, rst, inc, dec, ldRin, ldRout, memRead, memWrite, ld, en;
	sc_in<sc_lv<16>> dataIn;
	sc_out<sc_logic> full, empty;
	sc_out<sc_logic> ready;
	sc_out<sc_lv<16>> dataOut;

	Memory *mem;
	Counter *AddressCounter;
	Register *RegIn, *RegOut;
	MemoryTimer *Timer;

	sc_signal<sc_lv<9>> count, adr;
	sc_signal<sc_lv<16>> RDataIn, RDataOut;
	sc_signal<sc_lv<16>, SC_MANY_WRITERS> memR;
	sc_signal<sc_lv<3>> pin;

	SC_CTOR(DataPath)
	{
		mem = new Memory("StackMmeory");
			mem->clk(clk);
			mem->memWrite(memWrite);
			mem->memRead(memRead);
			mem->address(adr);
			mem->dataInOut(memR);
		AddressCounter = new Counter("AddressGenerator");
			AddressCounter->clk(clk);
			AddressCounter->rst(rst);
			AddressCounter->inc(inc);
			AddressCounter->dec(dec);
			AddressCounter->count(count);
		RegIn = new Register("InputRegister");
			RegIn->clk(clk);
			RegIn->rst(rst);
			RegIn->ldRin(ldRin);
			RegIn->dataIn(dataIn);
			RegIn->dataOut(RDataIn);
		RegOut = new Register("OutputRegister");
			RegOut->clk(clk);
			RegOut->rst(rst);
			RegOut->ldRin(ldRout);
			RegOut->dataIn(RDataOut);
			RegOut->dataOut(dataOut);
		Timer = new MemoryTimer("WaitStateTimer");
			Timer->clk(clk);
			Timer->rst(rst);
			Timer->ld(ld);
			Timer->en(en);
			Timer->pin(pin);
			Timer->memReady(ready);

		SC_THREAD(DataPath_Assign);
			sensitive << count << ready << memRead << memWrite << RDataIn << memR;
	}

	void DataPath_Assign();
};

#endif
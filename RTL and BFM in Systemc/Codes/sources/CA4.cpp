#include <systemc.h>

#include "stack_handlerTB.h"

int sc_main(int , char*[])
{
	StackHandlerTB SHTB("StackHandlerTestBench");

	sc_trace_file *VCD;
	VCD = sc_create_vcd_trace_file("StackHandlerTestBench");
	sc_trace(VCD, SHTB.clk, "clk");
	sc_trace(VCD, SHTB.rst, "rst");
	sc_trace(VCD, SHTB.push, "push");
	sc_trace(VCD, SHTB.pop, "pop");
	sc_trace(VCD, SHTB.tos, "tos");
	sc_trace(VCD, SHTB.dataIn, "dataIn");
	sc_trace(VCD, SHTB.dataOut, "dataOut");
	sc_trace(VCD, SHTB.fdataOut, "fdataOut");;
	sc_trace(VCD, SHTB.full, "full");
	sc_trace(VCD, SHTB.ffull, "ffull");
	sc_trace(VCD, SHTB.empty, "empty");
	sc_trace(VCD, SHTB.fempty, "fempty");

	sc_trace(VCD, SHTB.SH->DP->RDataIn,"DataIn");
	sc_trace(VCD, SHTB.SH->DP->RDataOut,"DataOut");
	sc_trace(VCD, SHTB.SH->DP->Timer->count, "count");
	sc_trace(VCD, SHTB.SH->DP->AddressCounter->count, "Acount");

	sc_start(20000, SC_NS);
	return 0;
}
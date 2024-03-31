#include <iostream>
#include <systemc.h>
//#include "InstructionTest.h"
#include "embSys1.h"

int sc_main(int argc, char *argv[])
{
	sc_report_handler::set_actions (SC_ID_VECTOR_CONTAINS_LOGIC_VALUE_, SC_DO_NOTHING);
	sc_report_handler::set_actions (SC_WARNING, SC_DO_NOTHING);
	embSys1* TOP = new embSys1("systemTest_TB");

	sc_trace_file* VCDFile;
	VCDFile = sc_create_vcd_trace_file("system_Main");
	sc_trace(VCDFile, TOP -> clk, "clk");
	sc_start(5000,SC_NS);
	
	return 0;
}
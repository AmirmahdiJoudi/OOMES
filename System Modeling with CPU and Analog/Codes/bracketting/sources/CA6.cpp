#include <systemc-ams.h>

#include "embSys1.h"

int sc_main(int argc, char* argv[])
{
	sc_set_time_resolution(1, SC_NS);

	embSys1 ES1("ES1");

	sc_trace_file *VCD1;
	VCD1 = sc_create_vcd_trace_file("EmbeddedSystem1");
	sc_trace(VCD1, ES1.clk, "clk");
	sc_trace(VCD1, ES1.data_s1, "data_s1");
	sc_trace(VCD1, ES1.data_s2, "data_s2");

	sca_trace_file *VCD2;
	VCD2 = sca_create_vcd_trace_file("EmbeddedSystem2");
	sca_trace(VCD2, ES1.to, "timeOut");
	sca_trace(VCD2, ES1.s1.sensor1.out, "sensor1");
	sca_trace(VCD2, ES1.s2.sensor2.out, "sensor2");

	sc_start(400000, SC_MS);
}
#ifndef __Sensor1__
#define __Sensor1__ "Sensor1.h"

#include <systemc-ams.h>

SC_MODULE(Sensor1)
{
	sc_in<double> in;
	sca_tdf::sca_out<double> out;

	sca_eln::sca_de::sca_vsource vin;
	sca_eln::sca_tdf::sca_vsink vout;

	sca_eln::sca_r r;
	sca_eln::sca_c c;
	
	SC_HAS_PROCESS(sc_module_name);
	Sensor1(sc_module_name, double r_value, double c_value);

private:
	sca_eln::sca_node a;
	sca_eln::sca_node b;
	sca_eln::sca_node_ref gnd;
};

#endif

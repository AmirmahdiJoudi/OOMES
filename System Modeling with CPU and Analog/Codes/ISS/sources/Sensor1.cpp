#include "Sensor1.h"

Sensor1::Sensor1(sc_module_name, double r_value, double c_value)
	:r("r",r_value), c("c", c_value), vin("vin", 1.0), vout("vout"), a("a"), b("b"), gnd("gnd")
{
	vin.p(a);
	vin.n(gnd);
	vin.inp(in);
	vin.set_timestep(100, SC_NS);

	r.n(a);
	r.p(b);

	c.n(b);
	c.p(gnd);

	vout.p(b);
	vout.n(gnd);
	vout.outp(out);
	vout.set_timestep(100, SC_NS);
}
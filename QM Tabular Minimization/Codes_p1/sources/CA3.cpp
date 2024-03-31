// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 3
// Revision: 2021-05-3

#include <systemc.h>
#include "sc_functionalTB.h"

using namespace sc_core;

int sc_main(int, char*[])
{	
	SC_FUNCTIONALTB* TOP = new SC_FUNCTIONALTB("AssignmentTB");
	sc_trace_file* VCDFILE;
	VCDFILE = sc_create_vcd_trace_file("Assignment");
	sc_trace(VCDFILE, TOP->a, "a");
	sc_trace(VCDFILE, TOP->b, "b");
	sc_trace(VCDFILE, TOP->c, "c");
	sc_trace(VCDFILE, TOP->d, "d");
	sc_trace(VCDFILE, TOP->s, "s");
	sc_trace(VCDFILE, TOP->sc_f->w, "w");
	sc_trace(VCDFILE, TOP->sc_f->f, "f");
	sc_trace(VCDFILE, TOP->sc_f->g, "g");
	sc_trace(VCDFILE, TOP->o, "o");

	sc_start(160, SC_NS);
	return 0;
}

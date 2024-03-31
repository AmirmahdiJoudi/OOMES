#ifndef __SENSOR1_FE__
#define __SENSOR1_FE__ "senor1FrontEnd.h"

#include <systemc.h>
#include <systemc-ams.h>

#include "squareWave.h"
#include "Sensor1.h"
#include "ADC.h"
#include "tdf2de.h"
#include "register.h"

SC_MODULE(Sensor1FrontEnd)
{
	sc_in<sc_logic> en;
	sc_out<sc_lv<16>> out;

	squareWave SQ;
	Sensor1 sensor1;
	ADC adc;
	tdf2de t2d;
	Register reg;

	SC_CTOR(Sensor1FrontEnd) : SQ("SQ1", 5000), sensor1("s1", 1000, 1.59e-9), adc("ADC1", 1), t2d("T2D1"), reg("reg1")
	{
		SQ.out(sq_out);

		sensor1.in(sq_out);
		sensor1.out(s1_out);

		adc.in(s1_out);
		adc.out(adc_out);

		t2d.in(adc_out);
		t2d.out(t2d_out);

		reg.clk(clk);
		reg.rst(rst);
		reg.outEnable(en);
		reg.dataIn(t2d_out);
		reg.dataOut(out);

		SC_THREAD(clocking);
	}

	void clocking();

private:
	sc_signal<sc_logic> clk;
	sc_signal<sc_logic> rst;
	sc_signal<double> sq_out;
	sca_tdf::sca_signal<double> s1_out;
	sca_tdf::sca_signal<sc_dt::sc_int<16>> adc_out;
	sc_signal<sc_lv<16>> t2d_out;
};

#endif
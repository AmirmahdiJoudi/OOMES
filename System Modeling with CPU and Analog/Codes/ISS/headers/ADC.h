#ifndef __ADC__
#define __ADC__ "ADC.h"

#include <systemc-ams.h>
#include <cmath>

SCA_TDF_MODULE(ADC)
{
    sca_tdf::sca_in<double> in;
    sca_tdf::sca_out<sc_dt::sc_int<16>> out;

    sca_time Tm;
    double Vm;
    
    ADC(sc_module_name name, double Vmax = 0.8, sca_time _Tm = sca_time(100, SC_NS))
        : Vm(Vmax), Tm(_Tm) {}

    void set_attributes();
    void initialize();
    void processing();
};

#endif
#ifndef __TDF2DE__
#define __TDF2DE__  "tdf2de.hpp"

#include <systemc-ams.h>

SCA_TDF_MODULE(tdf2de)
{
    sca_tdf::sca_in<sc_dt::sc_int<16>> in;
    sca_tdf::sca_de::sca_out<sc_lv<16>> out;

    sca_time Tm;
    tdf2de(sc_module_name name, sca_time _Tm = sca_time(100, SC_NS))
        :Tm(_Tm) {}

    void set_attributes();
    void initialize();
    void processing();
};

#endif
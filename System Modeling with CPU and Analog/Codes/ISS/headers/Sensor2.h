#ifndef __SENSOR2__
#define __SENSOR2__ "Sensor2.h"

#include <systemc-ams.h>

SCA_TDF_MODULE(Sensor2)
{
    sca_tdf::sca_de::sca_in<double> in;
    sca_tdf::sca_out<double> out;

    sca_time Tm;
    sca_tdf::sca_ltf_nd ltf_nd;
    Sensor2(sc_module_name name, sca_time _Tm = sca_time(100, SC_NS))
        :Tm(_Tm) {}

    void set_attributes();
    void initialize();
    void processing();

private:
    sca_vector<double> num;
    sca_vector<double> den;
};

#endif
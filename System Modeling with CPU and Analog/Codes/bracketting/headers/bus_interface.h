#ifndef __BUS_INTERFACE__
#define __BUS_INTERFACE__ "bus_interface.h"

#include <systemc.h>

SC_MODULE(BusInterface)
{
    sc_in <sc_lv<16>> address;
    sc_inout_rv<16> data;
    sc_in <sc_logic> readIO;
    sc_in <sc_logic> writeIO;

    sc_in <sc_lv<16>> data_s1;
    sc_in <sc_lv<16>> data_s2;
    sc_in <sc_logic> to;
    sc_out <sc_logic> st;
    sc_out <sc_logic> en_s1;
    sc_out <sc_logic> en_s2;
    sc_out <sc_logic> en_timer;


    SC_CTOR(BusInterface)
    {
        SC_METHOD(Interfacing);
            sensitive << address << data << readIO << writeIO << data_s1 << data_s2 << to;
    }

    void Interfacing();

};

#endif
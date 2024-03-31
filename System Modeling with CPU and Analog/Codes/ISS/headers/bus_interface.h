#ifndef __BUS_INTERFACE__
#define __BUS_INTERFACE__ "bus_interface.h"

#include <systemc.h>

SC_MODULE(BusInterface)
{
    sc_in <sc_lv<16>> address;
    sc_inout_rv<16> data;
    sc_in <sc_lv<16>> memDataIn;
    sc_in <sc_logic> readIO;
    sc_in <sc_logic> writeIO;
    sc_in <sc_logic> memRead;
    sc_in <sc_logic> memWrite;
    sc_in <sc_logic> memReady;

    sc_in <sc_lv<16>> data_s1;
    sc_in <sc_lv<16>> data_s2;
    sc_out <sc_logic> data_d;
    sc_in <sc_logic> to;
    sc_out <sc_logic> st;
    sc_out <sc_logic> en_s1;
    sc_out <sc_logic> en_s2;
    sc_out <sc_logic> en_d;

    sc_out <sc_logic> en_timer;
    sc_out <sc_logic> memCS;
    sc_out <sc_logic> memMemReady;
    sc_out <sc_logic> memMemRead;
    sc_out <sc_logic> memMemWrite;
    sc_out <sc_lv<16>>memDataOut;
    sc_out <sc_lv<16>>memAddress;


    SC_CTOR(BusInterface)
    {
        SC_METHOD(Interfacing);
            sensitive << address << data << memDataIn << readIO << writeIO << memRead << memWrite << memReady <<data_s1 << data_s2 << data_d << to;
    }

    void Interfacing();

};

#endif
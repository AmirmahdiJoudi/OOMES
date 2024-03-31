#ifndef __ProcessorBracketing__
#define __ProcessorBracketing__ "ProcessorBracketing.h"

#include <systemc.h>

SC_MODULE(ProcessorBracketing)
{
    sc_in <sc_logic> clk;
    sc_out <sc_lv<16>> address;
    sc_inout_rv<16> data;
    sc_out <sc_logic> readIO;
    sc_out <sc_logic> writeIO; 
    sc_out <sc_logic> readMEM;
    sc_out <sc_logic> writeMEM; 

    SC_CTOR(ProcessorBracketing)
    {
        SC_THREAD(abstractModel);
            sensitive << clk.pos();
    }

    void abstractModel();
};

#endif
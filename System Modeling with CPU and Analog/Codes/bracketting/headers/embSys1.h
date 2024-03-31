#ifndef __EMBSYS1__
#define __EMBSYS1__ "embSys1.h"

#include <systemc.h>

#include "sensor1FrontEnd.h"
#include "sensor2FrontEnd.h"
#include "timer.h"
#include "bus_interface.h"
#include "ProcessorBracketing.h"

SC_MODULE(embSys1)
{
    sc_signal <sc_logic> clk;
    sc_signal <sc_logic> readIO;
    sc_signal <sc_logic> writeIO;
    sc_signal <sc_logic> readMEM;
    sc_signal <sc_logic> writeMEM;
    sc_signal <sc_lv<16>> address;
    sc_signal_rv<16> data;

    sc_signal <sc_lv<16>> data_s1;
    sc_signal <sc_lv<16>> data_s2;

    sc_signal <sc_logic> to;
    sc_signal <sc_logic> st;
    sc_signal <sc_logic> en_s1;
    sc_signal <sc_logic> en_s2;
    sc_signal <sc_logic> en_timer;

    Sensor1FrontEnd s1;
    Sensor2FrontEnd s2;
    timer tm;
    BusInterface bus;
    ProcessorBracketing processor;

    SC_CTOR(embSys1): s1("s1"), s2("s2"), tm("tm"), bus("bus"), processor("processor")
    {
        bus.address(address);
        bus.data(data);
        bus.readIO(readIO);
        bus.writeIO(writeIO);
        bus.data_s1(data_s1);
        bus.data_s2(data_s2);
        bus.to(to);
        bus.st(st);
        bus.en_s1(en_s1);
        bus.en_s2(en_s2);
        bus.en_timer(en_timer);

        processor.clk(clk);
        processor.address(address);
        processor.data(data);
        processor.readIO(readIO);
        processor.writeIO(writeIO); 
        processor.readMEM(readMEM);
        processor.writeMEM(writeMEM); 

        s1.en(en_s1);
        s1.out(data_s1);

        s2.en(en_s2);
        s2.out(data_s2);

        tm.startTimer(st);
        tm.en(en_timer);
        tm.timeOut(to);

        SC_THREAD(clocking);
    }

    void clocking();
};

#endif
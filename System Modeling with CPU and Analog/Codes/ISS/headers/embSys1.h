#ifndef __EMBSYS1__
#define __EMBSYS1__ "embSys1.h"

#include <systemc.h>

#include "sensor1FrontEnd.h"
#include "sensor2FrontEnd.h"
#include "timer.h"
#include "bus_interface.h"
#include "sayacInstruction.h"
#include "Memory.h"
#include "Display.h"

SC_MODULE(embSys1)
{
    sc_signal <sc_logic> clk;
    sc_signal <sc_logic> CS;
    sc_signal <sc_logic> readIO;
    sc_signal <sc_logic> writeIO;
    sc_signal <sc_logic> readMem;
    sc_signal <sc_logic> writeMem;
    sc_signal <sc_logic> memReadyFromMem;
    sc_signal <sc_logic> memReadyToCPU;
    sc_signal <sc_lv<16>> address;
    sc_signal_rv<16> data;
    sc_signal <sc_logic> memMemRead;
    sc_signal <sc_logic> memMemWrite;
    sc_signal <sc_lv<16>> memDataIn;
    sc_signal <sc_lv<16>> memDataOut;
    sc_signal <sc_lv<16>> memAddress;

    sc_signal <sc_lv<16>> data_s1;
    sc_signal <sc_lv<16>> data_s2;
    sc_signal <sc_logic> data_d;

    sc_signal <sc_logic> to;
    sc_signal <sc_logic> st;
    sc_signal <sc_logic> en_s1;
    sc_signal <sc_logic> en_s2;
    sc_signal <sc_logic> en_timer;
    sc_signal <sc_logic> en_d;

    Sensor1FrontEnd s1;
    Sensor2FrontEnd s2;
    timer tm;
    Display D;
    BusInterface bus;
    sayacInstruction<16, 4, 16, 3> sayacInstructionModuleEmb;
    memory <16,16> memoryModule;

    SC_CTOR(embSys1): s1("s1"), s2("s2"), tm("tm"), D("Dp"), bus("bus"), sayacInstructionModuleEmb("sayacInstructionSetModuleEmb"), memoryModule("memoryModule")
    {
        bus.address(address);
        bus.data(data);
        bus.readIO(readIO);
        bus.writeIO(writeIO);
        bus.memRead(readMem);
        bus.memWrite(writeMem);
        bus.memReady(memReadyFromMem);
        bus.data_s1(data_s1);
        bus.data_s2(data_s2);
        bus.data_d(data_d);
        bus.to(to);
        bus.st(st);
        bus.en_s1(en_s1);
        bus.en_s2(en_s2);
        bus.en_d(en_d);
        bus.en_timer(en_timer);
        bus.memCS(CS);
        bus.memMemReady(memReadyToCPU);
        bus.memMemRead(memMemRead);
        bus.memMemWrite(memMemWrite);
        bus.memDataOut(memDataOut);
        bus.memAddress(memAddress);
        bus.memDataIn(memDataIn);

        s1.en(en_s1);
        s1.out(data_s1);

        s2.en(en_s2);
        s2.out(data_s2);

        D.en(en_d);
        D.data(data_d);

        tm.startTimer(st);
        tm.en(en_timer);
        tm.timeOut(to);

        sayacInstructionModuleEmb.clk(clk);
        sayacInstructionModuleEmb.memReady(memReadyToCPU);
        sayacInstructionModuleEmb.dataBus(data);
        sayacInstructionModuleEmb.readMem(readMem);
        sayacInstructionModuleEmb.writeMem(writeMem);
        sayacInstructionModuleEmb.readIO(readIO);
        sayacInstructionModuleEmb.writeIO(writeIO);
        sayacInstructionModuleEmb.addrBus(address);
        
        memoryModule.clk(clk);
        memoryModule.memRead(memMemRead);
        memoryModule.memWrite(memMemWrite);
        memoryModule.CS(CS);
        memoryModule.address(memAddress);
        memoryModule.dataIn(memDataOut);
        memoryModule.memReady(memReadyFromMem);
        memoryModule.dataOut(memDataIn);

        SC_THREAD(clocking);
    }

    void clocking();
};

#endif
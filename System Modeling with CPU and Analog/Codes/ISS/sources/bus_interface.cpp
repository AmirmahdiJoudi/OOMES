#include "bus_interface.h"

#define A15_12_IO 0xF
#define A7_4_IO 0x1
#define A3_0_S1_begin 0x0
#define A3_0_S1_end 0x3
#define A3_0_S2_begin 0x4
#define A3_0_S2_end 0x7
#define A3_0_timer_begin 0x8
#define A3_0_timer_end 0xB

void BusInterface::Interfacing()
{
    data = "ZZZZZZZZZZZZZZZZ";
    en_s1 = SC_LOGIC_0;
    en_s2 = SC_LOGIC_0;
    en_timer = SC_LOGIC_0;
    en_d = SC_LOGIC_0;
    memMemRead = SC_LOGIC_0;
    memMemReady = SC_LOGIC_0;
    memMemWrite = SC_LOGIC_0;
    memCS = SC_LOGIC_0;
    st = SC_LOGIC_0;
    if(readIO == SC_LOGIC_1)
    {
        if(address.read()(15, 12).to_uint() == A15_12_IO && address.read()(7, 4).to_uint() == A7_4_IO)
        {
            if(address.read()(3, 0).to_uint() >= A3_0_S1_begin && address.read()(3, 0).to_uint() <= A3_0_S1_end)
            {
                en_s1 = SC_LOGIC_1;
                data = data_s1;
            }
            else if(address.read()(3, 0).to_uint() >= A3_0_S2_begin && address.read()(3, 0).to_uint() <= A3_0_S2_end)
            {
                en_s2 = SC_LOGIC_1;
                data = data_s2;
            }
            else if(address.read()(3, 0).to_uint() >= A3_0_timer_begin && address.read()(3, 0).to_uint() <= A3_0_timer_end)
            {
                en_timer = SC_LOGIC_1;
                data->write((data.read()(15, 1), to.read()));
            }
        }
    }
    if(writeIO == SC_LOGIC_1)
    {
        if(address.read()(15, 12).to_uint() == A15_12_IO && address.read()(7, 4).to_uint() == A7_4_IO)
        {
            if(address.read()(3, 0).to_uint() >= A3_0_timer_begin && address.read()(3, 0).to_uint() <= A3_0_timer_end)
            {
                st = data.read()[0];
            }
            else
            {
                en_d = SC_LOGIC_1;
                data_d = data.read()[15];
            }
        }
    }
    if(memRead == SC_LOGIC_1)
    {
        if(address.read()(15,12) != A15_12_IO)
        {
            memMemRead = SC_LOGIC_1;
            memCS = SC_LOGIC_1;
            memAddress = address;
            memMemReady = memReady;
            data = memDataIn;
        }
    }
    if(memWrite == SC_LOGIC_1)
    {
        if(address.read()(15,12) != A15_12_IO)
        {
            memMemWrite = SC_LOGIC_1;
            memCS = SC_LOGIC_1;
            memDataOut = data;
            memAddress = address;
            memMemReady = memReady;
        }
    }
}
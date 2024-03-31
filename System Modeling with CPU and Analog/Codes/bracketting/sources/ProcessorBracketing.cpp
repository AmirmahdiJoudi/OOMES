#include "ProcessorBracketing.h"

#define s1_address 0xFF12
#define s2_address 0xFF16
#define tm_address 0xFF1A

#define sensor1TH 0.95
#define sensor2TH 2.5e-6

void ProcessorBracketing::abstractModel()
{
    sc_lv<16> sensor1Data;
    sc_lv<16> sensor2Data;
    address = tm_address;
    data = 0xFFF1;
    writeIO = SC_LOGIC_1;
    wait();
    data = 0xFFF0;
    writeIO = SC_LOGIC_0;
    wait();
    while(true)
    {
        data = "ZZZZZZZZZZZZZZZZ";
        readIO = SC_LOGIC_1;
        address = tm_address;
        wait(1, SC_NS);
        while(data.read()[0].value() != 1)
            wait(1, SC_NS);
        cout << sc_time_stamp() << endl;
        address = s1_address;
        wait();
        sensor1Data = data;
        wait();
        address = s2_address;
        wait();
        sensor2Data = data;
        wait();  
        cout << (sensor1Data.to_uint() + 1)/(pow(2, 15)) << " " << (sensor2Data.to_uint() + 1)/(pow(2, 15))*1e-6 << endl;
        if((sensor1Data.to_uint() + 1)/(pow(2, 15)) > sensor1TH)
            cout << "Sensor1: Passed." << endl;
        else
            cout << "Sensor1: Failed." << endl;
        if((sensor2Data.to_uint() + 1)/(pow(2, 15)) > sensor2TH)
            cout << "Sensor2: Passed." << endl;
        else
            cout << "Sensor2: Failed." << endl;
    }
}
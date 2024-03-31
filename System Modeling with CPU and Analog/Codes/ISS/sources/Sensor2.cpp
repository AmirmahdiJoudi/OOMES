#include "Sensor2.h"

void Sensor2::set_attributes()
{
    set_timestep(Tm);
}

void Sensor2::initialize()
{
    //out.initialize(0.0);
    num(0) = 1;
    den(0) = 0;
    den(1) = 1;
}

void Sensor2::processing()
{
    out = ltf_nd(num, den, in);
}

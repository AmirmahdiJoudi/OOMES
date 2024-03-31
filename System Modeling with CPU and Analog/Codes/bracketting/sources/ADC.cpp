#include "ADC.h"

void ADC::set_attributes()
{
    set_timestep(Tm);
}

void ADC::initialize()
{
   // out.initialize(0);
}

void ADC::processing()
{
    if(in.read() > Vm)
        out.write(Vm);
    else if(in.read() < -Vm)
        out.write(-Vm);
    else
        out.write(in/Vm*(pow(2, 15) - 1));
}

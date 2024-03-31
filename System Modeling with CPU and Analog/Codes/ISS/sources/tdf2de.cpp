#include "tdf2de.h"

void tdf2de::set_attributes()
{
    set_timestep(Tm);
}

void tdf2de::initialize()
{
    //out.initialize(0.0);
}

void tdf2de::processing()
{
    out.write(in.read());
}

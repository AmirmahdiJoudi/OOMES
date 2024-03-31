#include "squareWave.h"

void squareWave::wave()
{
	while(true)
	{
		out = (form == 0) ? 0 : -1;
		wait(T, SC_NS);
		out = 1;
		wait(T, SC_NS);
	}
}
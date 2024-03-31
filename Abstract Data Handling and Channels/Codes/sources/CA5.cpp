#include <systemc.h>
#include "System.h"

int sc_main(int argc, char* argv[])
{
	System SYSTEM("SYSTEM");
	sc_start();
}
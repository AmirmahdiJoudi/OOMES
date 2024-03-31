// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 3
// Revision: 2021-05-3

#include "sc_functionalTB.h"
#include <iostream>

using namespace std;

void SC_FUNCTIONALTB::inGenerating()
{
	while(true)
	{
		a = SC_LOGIC_1;
		b = SC_LOGIC_1;
		c = SC_LOGIC_1;
		d = SC_LOGIC_1;
		s = SC_LOGIC_1;
		wait(40, SC_NS);

		a = SC_LOGIC_0;
		b = SC_LOGIC_1;
		c = SC_LOGIC_0;
		d = SC_LOGIC_1;
		s = SC_LOGIC_1;
		wait(40, SC_NS);

		a = SC_LOGIC_1;
		b = SC_LOGIC_0;
		c = SC_LOGIC_1;
		d = SC_LOGIC_1;
		s = SC_LOGIC_1;
		wait(40, SC_NS);

		wait();
	}
}

void SC_FUNCTIONALTB::Displaying()
{
	while(true)
	{
		cout << "o is "<< o << " at "<< sc_time_stamp() << endl;
		wait();
	}
}
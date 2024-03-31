// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 2
// Revision: 2021-04-16

#include "wire.h"

Wire::Wire()
{
	value = new char('X');
	faultValue = new char('X');
	faultyWire = new bool(false);
	wire_identifier = number_of_wires;
	number_of_wires++;
	inp_for_nth_time = 0;
}

bool Wire::operator==(const Wire* w)
{
	if(wire_identifier == w-> wire_identifier)
		return true;
	return false;
}
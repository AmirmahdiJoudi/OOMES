// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 2
// Revision: 2021-04-16

#ifndef __WIRE__H
#define __WIRE__H "wire.h"

#include <string>

class Wire
{
public:
	std::string name;
	char* value;
	char* faultValue;
	bool* faultyWire;
	int wire_identifier;
	int inp_for_nth_time;
	Wire();
	bool operator==(const Wire* w);
private:
	static int number_of_wires;
};

#endif
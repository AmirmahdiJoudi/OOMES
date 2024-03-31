// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 1
// Revision: 2021-03-08

#ifndef __WIRE__H
#define __WIRE__H "wire.h"

#include <string>

struct event
{
	event() : value(' '), event_time(0) {}
	char value;
	int event_time;
};

struct wire
{
	wire() : value('X'), event_time(0) {}
	std::string name;
	char value;
	int event_time;
	event next_event;
};

#endif
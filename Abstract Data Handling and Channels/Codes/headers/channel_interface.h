#ifndef __CHANNEL__H
#define __CHANNEL__H "channel_interface.h"

#include <systemc.h>

class put_if : virtual public sc_interface
{
public:
	virtual bool put(sc_lv<8>) = 0;
};

class get_if : virtual public sc_interface
{
public:
	virtual bool get(sc_lv<8> &) = 0;
};

class fifo : public put_if, public get_if
{
	int head, elems;
	sc_lv<8> queue[4096];
public:
	fifo() {};
	~fifo() {};
	bool put(sc_lv<8> data);
	bool get(sc_lv<8> &data);
};

#endif
#include "channel_interface.h"

bool fifo::put(sc_lv<8> data)
{
	if(elems == 4096)
		return false;
	queue[(head+elems) % 4096] = data;
	elems ++;
	return true;
}

bool fifo::get(sc_lv<8> &data)
{
	if(elems == 0)
		return false;
	data = queue[head];
	elems--;
	head = (head + 1) % 4096;
	return true;
}

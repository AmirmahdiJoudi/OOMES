#ifndef __EDGEDETECTOR_H
#define __EDGEDETECTOR_H "EdgeDetector.h"

#include <systemc.h>
#include "channel_interface.h"

SC_MODULE(EdgeDetector)
{
	sc_port<get_if> in;

	std::vector<sc_lv<8>> gray_scaled_segment;
	std::vector<int> edge_detected;
	
	int segment_to_receive;
	int byte_to_receive;

	SC_CTOR(EdgeDetector)
	{
		SC_THREAD(EdgeDetect);
	}

	void EdgeDetect();
	void get_from_channel();
	void write_in_file();

};

#endif
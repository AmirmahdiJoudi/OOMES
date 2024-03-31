#ifndef __GRAYSCALER__H
#define __GRAYSCALER__H "GrayScaler.h"

#include <systemc.h>
#include "channel_interface.h"
#include <fstream>
#include <vector>

SC_MODULE(GrayScaler)
{
	sc_port<put_if> out;

	int segment_to_process;
	int segment_to_transmit;
	int byte_to_transmit;

	std::vector<sc_lv<8>> red_pixels;
	std::vector<sc_lv<8>> green_pixels;
	std::vector<sc_lv<8>> blue_pixels;
	std::vector<sc_lv<8>> gray_pixels;

	SC_CTOR(GrayScaler)
	{
		SC_THREAD(gray_scale);
	}

	void make_vectors();
	void gray_scale();
	void put_to_channel();
	void write_in_file();

};


#endif
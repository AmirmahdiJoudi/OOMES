#include "GrayScaler.h"
#include <sstream>
#include <fstream>
using namespace std;

void GrayScaler::make_vectors()
{
	string str;
	ifstream red_pixel("./Inputs/red_pixel.txt");
	ifstream green_pixel("./Inputs/green_pixel.txt");
	ifstream blue_pixel("./Inputs/blue_pixel.txt");
	while (getline(red_pixel, str))
	{
    	if(str.size() > 0)
        	red_pixels.push_back(stoi(str));
	}
	while (getline(green_pixel, str))
	{
    	if(str.size() > 0)
        	green_pixels.push_back(stoi(str));
	}
	while (getline(blue_pixel, str))
	{
    	if(str.size() > 0)
        	blue_pixels.push_back(stoi(str));
	}
	red_pixel.close();
	green_pixel.close();
	blue_pixel.close();
}

void GrayScaler::gray_scale()
{
	make_vectors();
	segment_to_transmit = 0;
	segment_to_process = 0;
	byte_to_transmit = 0;
	while(segment_to_process < 64 || segment_to_transmit < 64)
	{
		if(segment_to_process < 64)
		{
			for(int i = 4096 * segment_to_process; i <= 4095*(segment_to_process + 1) + segment_to_process; i++)
			{
				sc_uint<8> red_value = red_pixels[i].to_uint();
				sc_uint<8> green_value = green_pixels[i].to_uint();
				sc_uint<8> blue_value = blue_pixels[i].to_uint();
				sc_uint<8> gray_value = (red_value + green_value + blue_value) / 3;
				gray_pixels.push_back(gray_value);
				wait(10, SC_NS);
			}
			segment_to_process ++;
		}
		if(segment_to_transmit < 64)
		{
			put_to_channel();
		}
	}
	write_in_file();
}

void GrayScaler::put_to_channel()
{
	for(int i = 4096 * segment_to_transmit + byte_to_transmit; i <= 4095 * (segment_to_transmit + 1) + segment_to_transmit; i++)
	{
		wait(0.3, SC_NS);
		if(out->put(gray_pixels[i]))
		{
			byte_to_transmit++;
			if(i == 4095 * (segment_to_transmit + 1) + segment_to_transmit)
			{
				segment_to_transmit ++;
				byte_to_transmit = 0;
				break;
			}
		}
		else
			break;
	}	
}

void GrayScaler::write_in_file()
{
	ofstream out("gray_pixels.txt");
	for(auto line:gray_pixels)
		out<<line.to_uint()<<endl;
	out.close();
}
#include "EdgeDetector.h"

#define clip(i) ((i > 255) ? 255 : (i < 0) ? 0 : i)

void EdgeDetector::EdgeDetect()
{
	segment_to_receive = 0;
	byte_to_receive = 0;	
	while(segment_to_receive < 64)
	{
		get_from_channel();
		if(gray_scaled_segment.size() == 4096)
		{
			for(int row = 0; row < 8; row++)
			{
				for(int i = 512 * row; i < 512 * (row + 1); i++)
				{
					int val1 = gray_scaled_segment[i].to_uint();
					int val2 = (i % 512 == 0) ? 0 : gray_scaled_segment[i - 1].to_uint();
					int val3 = (i % 512 == 511) ? 0 : gray_scaled_segment[i + 1].to_uint();
					int val4 = (i < 512 || (i % 512 == 511)) ? ((segment_to_receive == 0) ? 0 : gray_scaled_segment[i].to_uint()) : gray_scaled_segment[i - 511].to_uint();
					int val5 = (i < 512 ) ? ((segment_to_receive == 0) ? 0 : gray_scaled_segment[i].to_uint()) : gray_scaled_segment[i - 512].to_uint();
					int val6 = (i < 512 ||(i % 512 == 0)) ? ((segment_to_receive == 0) ? 0 : gray_scaled_segment[i].to_uint()) : gray_scaled_segment[i - 513].to_uint();
					int val7 = (i % 512 == 0 || i > 3583) ? ((segment_to_receive == 63) ? 0 : gray_scaled_segment[i].to_uint()) : gray_scaled_segment[i + 511].to_uint();
					int val8 = (i > 3583) ? ((segment_to_receive == 63) ? 0 : gray_scaled_segment[i].to_uint()) : gray_scaled_segment[i + 512].to_uint();
					int val9 = (i % 512 == 511 || i > 3583) ? ((segment_to_receive == 63) ? 0 : gray_scaled_segment[i].to_uint()) : gray_scaled_segment[i + 513].to_uint();
					edge_detected.push_back(clip(8 * val1 - val2 - val3 - val4 - val5 - val6 - val7 - val8 - val9));
					wait(10, SC_NS);
				}
			}
			gray_scaled_segment.clear();
		}
	}
	write_in_file();
}

void EdgeDetector::get_from_channel()
{
	for(int i = byte_to_receive; i <= 4095; i++)
	{
		wait(0.75, SC_NS);
		sc_lv<8> data;
		if(in->get(data))
		{
			byte_to_receive++;
			gray_scaled_segment.push_back(data);
			if(i == 4095)
			{
				byte_to_receive = 0;
				segment_to_receive ++;
				break;
			}
		}
		else
			i--;
	}	
}

void EdgeDetector::write_in_file()
{
	ofstream out("edge_detected.txt");
	for(auto line:edge_detected)
		out<<line<<endl;
	out.close();
}
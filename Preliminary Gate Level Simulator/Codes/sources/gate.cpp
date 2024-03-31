// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 1
// Revision: 2021-03-16

#include "gate.h"

using namespace std;

Gate::Gate(int to1, int to0, vector<wire*> in, wire* out)
{
	to1_delay = to1;
	to0_delay = to0;
	inputs = in;
	output = out;
}

int Gate::find_fastest_zero_input()
{
	int min = numeric_limits<int>::max();
	for(int index = 0; index < inputs.size(); index++)
		if(inputs[index]->value == '0')
			if(inputs[index]->event_time < min)
				min = inputs[index]->event_time;
	return min;

}

int Gate::find_fastest_one_input()
{
	int min = numeric_limits<int>::max();
	for(int index = 0; index < inputs.size(); index++)
		if(inputs[index]->value == '1')
			if(inputs[index]->event_time < min)
				min = inputs[index]->event_time;
	return min;
}

int Gate::find_slowest_input()
{
	int max = 0;
	for(int index = 0; index < inputs.size(); index++)
		if(inputs[index]->event_time > max)
			max = inputs[index]->event_time;
	return max;
}


AND_n::AND_n(int to1, int to0, vector<wire*> in, wire* out)
        :Gate(to1, to0, in, out) {}

void AND_n::calc_output()
{
	new_val = 'X';
	for(int index = 0; index < inputs.size() - 1; index ++)
		and_2b(new_val, inputs[index], inputs[index + 1]);
	if(new_val != output->value)
	{
		output->next_event.value = new_val;
		if(new_val == '0')
			output->next_event.event_time = find_fastest_zero_input() + to0_delay;
		else
			output->next_event.event_time = find_slowest_input() + to1_delay;
	}
}

void AND_n::and_2b(char& val, wire* in1, wire* in2)
{
	if(in1->value == '0' || in2->value == '0')
		val = '0';
	else if(in1->value == '1' && in2->value == '1')
		val = '1';
	else val = 'X';
}

NAND_n::NAND_n(int to1, int to0, vector<wire*> in, wire* out)
        :Gate(to1, to0, in, out) {}

void NAND_n::calc_output()
{
	new_val = 'X';
	for(int index = 0; index < inputs.size() - 1; index ++)
		nand_2b(new_val, inputs[index], inputs[index + 1]);
	if(new_val != output->value)
	{
		output->next_event.value = new_val;
		if(new_val == '0')
			output->next_event.event_time = find_slowest_input() + to0_delay;
		else
			output->next_event.event_time = find_fastest_zero_input() + to1_delay;
	}
}

void NAND_n::nand_2b(char& val, wire* in1, wire* in2)
{
	if(in1->value == '0' || in2->value == '0')
		val = '1';
	else if(in1->value == '1' && in2->value == '1')
		val = '0';
	else val = 'X';
}

OR_n::OR_n(int to1, int to0, vector<wire*> in, wire* out)
        :Gate(to1, to0, in, out) {}

void OR_n::calc_output()
{
	new_val = 'X';
	for(int index = 0; index < inputs.size() - 1; index ++)
		or_2b(new_val, inputs[index], inputs[index + 1]);
	if(new_val != output->value)
	{
		output->next_event.value = new_val;
		if(new_val == '0')
			output->next_event.event_time = find_slowest_input() + to0_delay;
		else
			output->next_event.event_time = find_fastest_one_input() + to1_delay;
	}
}

void OR_n::or_2b(char& val, wire* in1, wire* in2)
{
	if(in1->value == '1' || in2->value == '1')
		val = '1';
	else if(in1->value == '0' && in2->value == '0')
		val = '0';
	else val = 'X';
}

NOR_n::NOR_n(int to1, int to0, vector<wire*> in, wire* out)
        :Gate(to1, to0, in, out) {}

void NOR_n::calc_output()
{
	new_val = 'X';
	for(int index = 0; index < inputs.size() - 1; index ++)
		nor_2b(new_val, inputs[index], inputs[index + 1]);
	if(new_val != output->value)
	{
		output->next_event.value = new_val;
		if(new_val == '0')
			output->next_event.event_time = find_fastest_one_input() + to0_delay;
		else
			output->next_event.event_time = find_slowest_input() + to1_delay;
	}

}

void NOR_n::nor_2b(char& val, wire* in1, wire* in2)
{
	if(in1->value == '1' || in2->value == '1')
		val = '0';
	else if(in1->value == '0' && in2->value == '0')
		val = '1';
	else val = 'X';
}

XOR_n::XOR_n(int to1, int to0, vector<wire*> in, wire* out)
        :Gate(to1, to0, in, out) {}

void XOR_n::calc_output()
{
	new_val = 'X';
	for(int index = 0; index < inputs.size() - 1; index ++)
		xor_2b(new_val, inputs[index], inputs[index + 1]);
	if(new_val != output->value)
	{
		output->next_event.value = new_val;
		if(new_val == '0')
			output->next_event.event_time = find_slowest_input() + to0_delay;
		else
			output->next_event.event_time = find_slowest_input() + to1_delay;
	}
}

void XOR_n::xor_2b(char& val, wire* in1, wire* in2)
{
	if(in1->value == '1' && in2->value == '0')
		val = '1';
	else if(in1->value == '0' && in2->value == '1')
		val = '1';
	else if(in1->value == '1' && in2->value == '1')
		val = '0';
	else if(in1->value == '0' && in2->value == '0')
		val = '0';
	else 
		val = 'X';
}
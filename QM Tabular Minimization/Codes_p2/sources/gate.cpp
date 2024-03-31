// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 1
// Revision: 2021-05-12

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
		else if(new_val == '1')
			output->next_event.event_time = find_slowest_input() + to1_delay;
	}
}

void AND_n::and_2b(char& val, wire* in1, wire* in2)
{
	if(in1->value == '0' || in2->value == '0')
		val = '0';
	else if(in1->value == '1' && in2->value == '1' && val != '0')
		val = '1';
	else if(in1->value == 'X' || in2->value == 'X')
	    val = 'X';
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
		else if(new_val == '1')
			output->next_event.event_time = find_fastest_one_input() + to1_delay;
	}
}

void OR_n::or_2b(char& val, wire* in1, wire* in2)
{
	if(in1->value == '1' || in2->value == '1')
		val = '1';
	else if(in1->value == '0' && in2->value == '0' && val != '1')
		val = '0';
	else if(in1->value == 'X' || in2->value == 'X')
	    val = 'X';
}

NOT::NOT(int to1, int to0, vector<wire*> in, wire* out)
        :Gate(to1, to0, in, out) {}

void NOT::calc_output()
{
	new_val = 'X';
	if(inputs[0]->value == '0')
		new_val = '1';
	else
		new_val = '0';
	if(new_val != output->value)
	{
		output->next_event.value = new_val;
		if(new_val == '0')
			output->next_event.event_time = find_slowest_input() + to0_delay;
		else
			output->next_event.event_time = find_slowest_input() + to1_delay;
	}
}
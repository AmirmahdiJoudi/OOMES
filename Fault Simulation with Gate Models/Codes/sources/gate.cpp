// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 2
// Revision: 2021-04-16

#include "gate.h"

using namespace std;

Gate::Gate()
{
	gate_identifier = number_of_gates;
	number_of_gates ++;	
}

Gate::Gate(Wire* in1, Wire* in2, Wire* out)
{
	input1 = in1;
	input1-> inp_for_nth_time ++;
	input2 = in2;
	input2-> inp_for_nth_time ++;
	output = out;
	gate_identifier = number_of_gates;
	number_of_gates ++;	
}

Gate::Gate(Wire* in1, Wire* out)
{
	input1 = in1;
	input1-> inp_for_nth_time ++;
	output = out;
	gate_identifier = number_of_gates;
	number_of_gates ++;
}

std::vector<Wire*> Gate::branch_fanout()
{
	vector<Wire*> ws;
	if(input1->inp_for_nth_time > 1)
	{
		Wire* inp_br = new Wire();
		inp_br-> name = input1-> name;
		inp_br-> value = input1-> value;
		inp_br-> faultValue = input1-> faultValue;
		inp_br-> faultyWire = input1-> faultyWire;
		input1 = inp_br;
	}
	if(input2->inp_for_nth_time > 1)
	{
		Wire* inp_br = new Wire();
		inp_br-> name = input2-> name;
		inp_br-> value = input2-> value;
		inp_br-> faultValue = input2-> faultValue;
		inp_br-> faultyWire = input2-> faultyWire;
		input2 = inp_br;
	}
	ws.push_back(input1);
	ws.push_back(input2);
	return ws;
}

std::vector<Wire*> Gate::get_inputs()
{
	vector<Wire*> inps;
	inps.push_back(input1);
	inps.push_back(input2);
	return inps;
}

Wire* Gate::get_output()
{
	return output;
}

Not::Not()
        :Gate() {}

Not::Not(Wire* in1, Wire* out)
		:Gate(in1, out) {}

void Not::eval()
{
	if(*(output->faultyWire))
		*(output->value) = *(output->faultValue);
	else
	{
		char value1;
		if(*(input1-> faultyWire))
			value1 = *(input1-> faultValue);
		else
			value1 = *(input1-> value);
		if(value1 == '1')
			*(output->value) = '0';
		else if(value1 == '0')
			*(output->value) = '1';
		else
			*(output->value) = 'X';
	}
}

std::vector<Wire*> Not::branch_fanout()
{
	vector<Wire*> ws;
	if(input1->inp_for_nth_time > 1)
	{
		Wire* inp_br = new Wire();
		inp_br-> name = input1-> name;
		inp_br-> value = input1-> value;
		inp_br-> faultValue = input1-> faultValue;
		inp_br-> faultyWire = input1-> faultyWire;
		input1 = inp_br;
	}
	ws.push_back(input1);
	return ws;
}

std::vector<std::string> Not::get_faults()
{
	vector<string> faults;
	return faults;
}

std::vector<Wire*> Not::get_inputs()
{
	vector<Wire*> inps;
	inps.push_back(input1);
	return inps;
}


Nand::Nand()
        :Gate() {}

Nand::Nand(Wire* in1, Wire* in2, Wire* out)
		:Gate(in1, in2, out) {}

void Nand::eval()
{
	if(*(output->faultyWire))
		*(output->value) = *(output->faultValue);
	else
	{
		char value1, value2;
		if(*(input1-> faultyWire))
			value1 = *(input1-> faultValue);
		else
			value1 = *(input1-> value);
		if(*(input2-> faultyWire))
			value2 = *(input2-> faultValue);
		else
			value2 = *(input2-> value);
		if(value1 == '0' || value2 == '0')
			*(output->value) = '1';
		else if(value1 == '1' && value2 == '1')
			*(output->value) = '0';
		else
			*(output->value) = 'X';
	}
}

std::vector<std::string> Nand::get_faults()
{
	vector<string> faults;
	faults.push_back(input1-> name + " " + to_string(input1-> wire_identifier) + " 1");
	faults.push_back(input2-> name + " " + to_string(input2-> wire_identifier) + " 1");
	return faults;
}

Nor::Nor()
        :Gate() {}

Nor::Nor(Wire* in1, Wire* in2, Wire* out)
		:Gate(in1, in2, out) {}

void Nor::eval()
{
	if(*(output->faultyWire))
		*(output->value) = *(output->faultValue);
	else
	{
		char value1, value2;
		if(*(input1-> faultyWire))
			value1 = *(input1-> faultValue);
		else
			value1 = *(input1-> value);
		if(*(input2-> faultyWire))
			value2 = *(input2-> faultValue);
		else
			value2 = *(input2-> value);
		if(value1 == '1' || value2 == '1')
			*(output->value) = '0';
		else if(value1 == '0' && value2 == '0')
			*(output->value) = '1';
		else
			*(output->value) = 'X';
	}
}

std::vector<std::string> Nor::get_faults()
{
	vector<string> faults;
	faults.push_back(input1-> name + " " + to_string(input1-> wire_identifier) + " 0");
	faults.push_back(input2-> name + " " + to_string(input2-> wire_identifier) + " 0");
	return faults;
}
// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 1
// Revision: 2021-03-16

#include "logic.h"

using namespace std;

bool operator==(const wire& w1, const wire& w2)
{
	if(w1.name == w2.name)
		return true;
	return false;
}

Logic::Logic()
{}

Logic::~Logic()
{
	for(auto gate:gates)
		delete gate;
}

void Logic::L_AND(int to1, int to0, wire* output, vector<wire*> inputs)
{
	gates.push_back(new AND_n(to1, to0, inputs, output));
}

void Logic::L_NAND(int to1, int to0, wire* output, vector<wire*> inputs)
{
	gates.push_back(new NAND_n(to1, to0, inputs, output));	
}

void Logic::L_OR(int to1, int to0, wire* output, vector<wire*> inputs)
{
	gates.push_back(new OR_n(to1, to0, inputs, output));
}

void Logic::L_NOR(int to1, int to0, wire* output, vector<wire*> inputs)
{
	gates.push_back(new NOR_n(to1, to0, inputs, output));
}

void Logic::L_XOR(int to1, int to0, wire* output, vector<wire*> inputs)
{
	gates.push_back(new XOR_n(to1, to0, inputs, output));
}

void Logic::set_inputs(std::vector<wire*> inputs)
{
	logic_inputs = inputs;
}

void Logic::set_outputs(vector<wire*> outputs)
{
	logic_outputs = outputs;
}

void Logic::set_intermediates(std::vector<wire*> intermediates)
{
	logic_intermediates = intermediates;
}

vector<string> Logic::calculate(string input_values)
{
	all_wires.insert(all_wires.end(), logic_inputs.begin(), logic_inputs.end());
	all_wires.insert(all_wires.end(), logic_outputs.begin(), logic_outputs.end());
	all_wires.insert(all_wires.end(), logic_intermediates.begin(), logic_intermediates.end());
	ifstream input_file(input_values);
	vector<string> results;
	int input_event_time = 0;
	string line;
	results.push_back(get_outputs_values(AT_FIRST));
	while(getline(input_file, line))
	{
		set_inputs_events(line, input_event_time);
		while(get_events_num() != 0)
		{
			vector<string> res = apply_events();
			results.insert(results.end(), res.begin(), res.end());
		}
	}
	results = pretty(results);
	input_file.close();
	return results;
}

void Logic::set_inputs_events(std::string line, int& input_event_time)
{
	int index1 = line.find(SYMBOLS[SHP]);
	int index2 = line.find(" ");
	int changing_time = stoi(line.substr(index1 + 1, index2 - index1 - 1));
	input_event_time += changing_time;
	for(int index = 0; index < logic_inputs.size(); index++)
	{
		if(logic_inputs[index]->value != (line.substr(index2 + 1 + index, 1))[0])
		{
			logic_inputs[index]->next_event.value = (line.substr(index2 + 1 + index, 1))[0];
			logic_inputs[index]->next_event.event_time = input_event_time;
		}
	}
}

vector<string> Logic::apply_events()
{
	vector<string> results;
	vector<char> last_val;
	vector<int> last_tim;
	for(auto out:logic_outputs)
	{
		last_val.push_back(out->value);
		last_tim.push_back(out->event_time);
	}
	int current_time = find_nearest_event();
	go_to_time(current_time);
	for(auto gate:gates)
		gate->calc_output();
	for(int i=0; i < logic_outputs.size(); i++)
	{
		if(last_val[i] != logic_outputs[i]->value)
		{
			results.push_back(get_outputs_values(last_tim[i]));
			break;
		}
	}
	return results;
}

int Logic::get_events_num()
{
	int num = 0;
	for(auto wire:all_wires)
		if(wire->next_event.value != ' ')
			num ++;
	return num;
}

int Logic::find_nearest_event()
{
	int min = numeric_limits<int>::max();
	for(auto wire:all_wires)
		if(wire->next_event.value != ' ')
			if(wire->next_event.event_time < min)
				min = wire->next_event.event_time;
	return min;
}

void Logic::go_to_time(int curr_time)
{
	for(auto wire:all_wires)
		if(wire->next_event.event_time == curr_time && wire->next_event.value != ' ')
		{
			wire->value = wire->next_event.value;
			wire->event_time = wire->next_event.event_time;
			wire->next_event.value = ' ';
		}
}

string Logic::get_outputs_values(int input_event_time)
{
	string result1 = "";
	string result2 = "";
	int max = 0;
	for(auto output:logic_outputs)
	{
		result2.push_back(output->value);
		if(output->event_time > max)
			max = output->event_time;
	}
	result1 += to_string(max - input_event_time);
	return result1 + " " + result2;
}


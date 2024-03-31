// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 1
// Revision: 2021-04-16

#include "logic.h"

using namespace std;

Logic::Logic()
{
	
}

Logic::~Logic()
{
	for(auto gate:gates)
		delete gate;
}

void Logic::L_NAND(Wire* output, vector<Wire*> inputs)
{
	gates.push_back(new Nand(inputs[ZERO], inputs[ONE], output));	
}

void Logic::L_NOR(Wire* output, vector<Wire*> inputs)
{
	gates.push_back(new Nor(inputs[ZERO], inputs[ONE], output));
}

void Logic::L_NOT(Wire* output, vector<Wire*> inputs)
{
	gates.push_back(new Not(inputs[ZERO], output));
}

void Logic::set_inputs(std::vector<Wire*> inputs)
{
	logic_inputs = inputs;
}

void Logic::set_outputs(vector<Wire*> outputs)
{
	logic_outputs = outputs;
}

void Logic::set_intermediates(std::vector<Wire*> intermediates)
{
	logic_intermediates = intermediates;
}

void Logic::calculate()
{
	all_wires.insert(all_wires.end(), logic_inputs.begin(), logic_inputs.end());
	all_wires.insert(all_wires.end(), logic_outputs.begin(), logic_outputs.end());
	all_wires.insert(all_wires.end(), logic_intermediates.begin(), logic_intermediates.end());
	sort_gates();
}

FC* Logic::get_fc()
{
	FC* logic_fc = new FC(gates, all_wires, logic_outputs, logic_inputs);
	return logic_fc;
}

void Logic::sort_gates()
{
	vector<Gate*> sorted_gates;
	for(auto out:logic_outputs)
	{
		rec_sort(out, sorted_gates);
	}
	gates = sorted_gates;
}

void Logic::rec_sort(Wire* gate_output, std::vector<Gate*> &sorted_gates)
{
	Gate* gate = find_gate_with_output(gate_output);
	if(gate == nullptr)
		throw invalid_argument("Wrong Wiring!\n");
	vector<Wire*> gate_inputs = gate-> get_inputs();
	for(auto input:gate_inputs)
	{
		if(!did_reach_to_first_level(input))
		    rec_sort(input, sorted_gates);
	}
	if(find(sorted_gates.begin(), sorted_gates.end(), gate) == sorted_gates.end())
		sorted_gates.push_back(gate);
}

Gate* Logic::find_gate_with_output(Wire* output)
{
	for(auto gate:gates)
		if(gate->get_output() == output)
			return gate;
	return nullptr;
}

bool Logic::did_reach_to_first_level(Wire* input)
{
	for(int index = 0; index < logic_inputs.size(); index ++)
		if(logic_inputs[index] == input)
			return true;
	return false;
}
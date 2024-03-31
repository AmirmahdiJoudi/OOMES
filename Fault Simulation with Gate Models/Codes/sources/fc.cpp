// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 2
// Revision: 2021-04-16

#include "fc.h"

using namespace std;

FC::FC(std::vector<Gate*> _gates, std::vector<Wire*> _all_wires, std::vector<Wire*> _outputs, std::vector<Wire*> _inputs)
{
	gates = _gates;
	all_wires = _all_wires;
	outputs = _outputs;
	inputs = _inputs;
}

std::vector<string> FC::fault_collapse()
{
	vector<string> faults;
	branch_fanout();
	for(auto gate:gates)
	{
		vector<string> fs = gate-> get_faults();
		if(fs.size() != 0)
			faults.insert(faults.end(), fs.begin(), fs.end());
	}
	for(auto wire:all_wires)
		if(wire-> inp_for_nth_time > 1)
		{
			faults.push_back(wire-> name + " " + to_string(wire-> wire_identifier) + " 0");
			faults.push_back(wire-> name + " " + to_string(wire-> wire_identifier) + " 1");
		}
	for(auto out:outputs)
	{
		faults.push_back(out-> name + " " + to_string(out-> wire_identifier) + " 0");
		faults.push_back(out-> name + " " + to_string(out-> wire_identifier) + " 1");
	}
	faults = pretty(faults);
	l_faults = faults;
	return faults;
}

FS* FC::get_fs()
{
	FS* l_fs = new FS(gates, all_wires, outputs, inputs, l_faults);
	return l_fs;
}

void FC::branch_fanout()
{
	for(auto gate:gates)
	{
		vector<Wire*> ws = gate-> branch_fanout();
		if(ws.size() != 0)
			all_wires.insert(all_wires.end(), ws.begin(), ws.end());
	}
    for(auto out:outputs)
    {
 	    if(out-> inp_for_nth_time != 0)
 	    {
 	    	Wire* out_br = new Wire();
			out_br-> name = out-> name;
			out_br-> value = out-> value;
			out_br-> faultValue = out-> faultValue;
			out_br-> faultyWire = out-> faultyWire;
			all_wires.push_back(out_br);
			out->inp_for_nth_time ++;
 	    } 
 	}
}
// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 2
// Revision: 

#include "fs.h"

#include <fstream>
#include <sstream>

using namespace std;

FS::FS(std::vector<Gate*> _gates, std::vector<Wire*> _all_wires, std::vector<Wire*> _outputs, std::vector<Wire*> _inputs, std::vector<std::string> _faults)
{
	gates = _gates;
	all_wires = _all_wires;
	outputs = _outputs;
	inputs = _inputs;
	faults = _faults;
}

std::vector<std::string> FS::calculate(std::string input_values)
{
	ifstream input_file(input_values);
	string line;
	vector<string> calculations;
	while(getline(input_file, line))
	{
		set_inputs_events(line);
		vector<string> true_vals = eval_true_values();
		calculations.insert(calculations.end(), true_vals.begin(), true_vals.end());
		for(auto line:faults)
		{	
			vector<string> a = separate_line_by_first_token(line);
			a = separate_line_by_first_token(a[ONE]);
			for(auto wire:all_wires)
			{
				stringstream geek(a[ZERO]);
				int x;
				geek >> x;
				if(wire-> wire_identifier == x)
				{
					vector<string> calcs;
					*(wire-> faultValue) = a[ONE][ZERO];
					*(wire-> faultyWire) = true;
					calculations.push_back(line + "   ");
					calcs = eval_gates();
					for(int i = 0; i < calcs.size(); i++)
						calculations.back() += calcs[i];
					*(wire-> faultyWire) = false;
					break;
				}
			}
		}
	}
	input_file.close();
	return calculations;
}

std::vector<std::string> FS::eval_true_values()
{
	vector<string> calculations;
	vector<string> calcs;
	calculations.push_back("Output values without fault: ");
	calcs = eval_gates();
	for(int i = 0; i < calcs.size(); i++)
		calculations.back() += calcs[i];
	return calculations;
}

std::vector<std::string> FS::eval_gates()
{
	vector<string> calculations;
	for(auto gate:gates)
		gate-> eval();
	for(auto out:outputs)
		calculations.push_back (string(1,*(out-> value)));
	return calculations;
}

void FS::set_inputs_events(std::string line)
{
	int index = 0;
	for(int index = 0; index < inputs.size(); index++)
		*(inputs[index]->value) = (line.substr(index, 1))[ZERO];
}
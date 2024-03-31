// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 2
// Revision: 

#include "wire.h"
#include "gate.h"
#include "functions.h"

#include <string>
#include <vector>

#ifndef __FS__H
#define __FS__H "fs.h"

#include <string>

class FS
{
public:
	FS(std::vector<Gate*> _gates, std::vector<Wire*> _all_wires, std::vector<Wire*> _outputs, std::vector<Wire*> inputs, std::vector<std::string> _faults);
	std::vector<std::string> calculate(std::string input_values);
private:
	std::vector<Gate*> gates;
	std::vector<Wire*> all_wires;
	std::vector<Wire*> outputs;
	std::vector<Wire*> inputs;
	std::vector<std::string> faults;
	std::vector<std::string> eval_true_values();
	std::vector<std::string> eval_gates();
	void set_inputs_events(std::string line);
};

#endif
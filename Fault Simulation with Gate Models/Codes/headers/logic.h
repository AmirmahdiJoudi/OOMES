// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 1
// Revision: 2021-04-16

#ifndef __LOGIC__H
#define __LOGIC__H "logic.h"

#include "gate.h"
#include "wire.h"
#include "functions.h"
#include "magic_values.h"
#include "fc.h"

#include <vector>
#include <string>
#include <fstream>
#include <exception>
#include <algorithm>
#include <limits>
#include <iostream>

class Logic
{
public:
	Logic();
	~Logic();
	void calculate();
	void L_NAND(Wire* output, std::vector<Wire*> inputs);
	void L_NOR(Wire* output, std::vector<Wire*> inputs);
	void L_NOT(Wire* output, std::vector<Wire*> inputs);
	void set_inputs(std::vector<Wire*> inputs);
	void set_outputs(std::vector<Wire*> outputs);
	void set_intermediates(std::vector<Wire*> intermediates);
	FC* get_fc();
private:
	std::vector<Wire*> logic_inputs;
	std::vector<Wire*> logic_outputs;
	std::vector<Wire*> logic_intermediates;
	std::vector<Wire*> all_wires;
	std::vector<Gate*> gates;
	Gate* find_gate_with_output(Wire* output);
	void sort_gates();
	void rec_sort(Wire* gate_output, std::vector<Gate*> &sorted_gates);
	bool did_reach_to_first_level(Wire* input);
};

#endif
// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 1
// Revision: 2021-03-16

#ifndef __LOGIC__H
#define __LOGIC__H "logic.h"

#include "gate.h"
#include "wire.h"
#include "functions.h"
#include "magic_values.h"

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
	std::vector<std::string> calculate(std::string input_values);
	void L_AND(int to1, int to0, wire* output, std::vector<wire*> inputs);
	void L_NAND(int to1, int to0, wire* output, std::vector<wire*> inputs);
	void L_OR(int to1, int to0, wire* output, std::vector<wire*> inputs);
	void L_NOR(int to1, int to0, wire* output, std::vector<wire*> inputs);
	void L_XOR(int to1, int to0, wire* output, std::vector<wire*> inputs);
	void set_inputs(std::vector<wire*> inputs);
	void set_outputs(std::vector<wire*> outputs);
	void set_intermediates(std::vector<wire*> intermediates);
private:
	std::vector<wire*> logic_inputs;
	std::vector<wire*> logic_outputs;
	std::vector<wire*> logic_intermediates;
	std::vector<wire*> all_wires;
	std::vector<Gate*> gates;
	std::vector<std::string> apply_events();
	std::string get_outputs_values(int input_event_time);
	int get_events_num();
	int find_nearest_event();
	void go_to_time(int curr_time);
	void set_inputs_events(std::string line, int& input_event_time);
};

#endif
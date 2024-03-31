// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 2
// Revision: 2021-04-13

#ifndef __COMPILER__H
#define __COMPILER__H "compiler.h"

#include "logic.h"
#include "functions.h"
#include "magic_values.h"
#include "wire.h"

#include <vector>
#include <string>
#include <fstream>
#include <exception>
#include <algorithm>

class Compiler
{
public:
	Compiler(std::string sv_file_address);
	~Compiler();
	void compile();
	Logic* get_logic();
private:
	Logic* logic;
	std::vector<std::string> sv_lines;
	std::vector<Wire*> io;
	std::vector<Wire*> inputs;
	std::vector<Wire*> outputs;
	std::vector<Wire*> wires;
	void assign_variables(std::string data, int line_num);
	void assign_iow_variables(std::string data, int line_num, std::string io);
	void form_gate(std::string data, std::string gate, int line_num);
	void add_io_to_logic();
	void check_sem_comm_syntax(std::string data, int line_num);
	void check_module_line_syntax(std::vector<std::string> tokens, int line_num);
	void check_io_line_syntax(std::string line, int line_num);
	void check_io_correctness(std::string variable, int line_num, std::string io);
	void check_gate_line_syntax(std::string data, int line_num);
	Wire* find_output(std::vector<std::string> output);
	std::vector<Wire*> find_inputs(std::vector<std::string> _inputs);
	std::vector<int> find_delay_values(std::string data);
	std::vector<std::string> find_gate_io(std::string data);	
};

#endif
// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 1
// Revision: 2021-03-08

#ifndef __COMPILER__H
#define __COMPILER__H "compiler.h"

#include "logic.h"
#include "functions.h"
#include "magic_values.h"
#include "wire.h"
#include "QM.h"

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
	std::vector<wire*> io;
	std::vector<wire*> inputs;
	std::vector<wire*> outputs;
	std::vector<wire*> wires;
	std::vector<wire*> or_inps;
	void assign_variables(std::string data, int line_num);
	void assign_iow_variables(std::string data, int line_num, std::string io);
	void form_gate(std::string data);
	void make_gates(std::vector<std::string> tokens);
	void form_and_gates(std::string term);
	void form_cond_gates(std::string o_name, std::string term);
	void add_io_to_logic();
	void check_sem_comm_syntax(std::string data, int line_num);
	void check_module_line_syntax(std::vector<std::string> tokens, int line_num);
	void add_wires(std::string term);
	std::vector<wire*> get_wires(std::string term);
	std::string find_assign_output(std::string stm);
};

#endif
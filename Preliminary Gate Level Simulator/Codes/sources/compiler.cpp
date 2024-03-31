// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 1
// Revision: 2021-03-15

#include "compiler.h"

using namespace std;

Compiler::Compiler(string sv_file_address)
{
	sv_lines = get_sv_lines(sv_file_address);
	logic = new Logic();
}

Compiler::~Compiler()
{
	delete logic;
	for(auto val:io)
		delete val;
	for(auto val:inputs)
		delete val;
	for(auto val:outputs)
		delete val;
	for(auto val:wires)
		delete val;
}

void Compiler::compile()
{
	int line_num = 1;
	for (auto line:sv_lines)
	{
		if(line.size() == 0)
		{
			line_num ++;
			continue;
		}
		vector<string> tokens = separate_line_by_first_token(line);
		if(tokens[KEYWORD_INDEX] != END_MODULE)
			check_sem_comm_syntax(tokens[DATA_INDEX], line_num);
		if (tokens[KEYWORD_INDEX] == MODULE)
			assign_variables(tokens[DATA_INDEX], line_num);
		else if (tokens[KEYWORD_INDEX] ==  INPUT)
			assign_iow_variables(tokens[DATA_INDEX], line_num, INPUT);
		else if (tokens[KEYWORD_INDEX] == OUTPUT)
			assign_iow_variables(tokens[DATA_INDEX], line_num, OUTPUT);
		else if (tokens[KEYWORD_INDEX] == WIRE)
			assign_iow_variables(tokens[DATA_INDEX], line_num, WIRE);
		else if (tokens[KEYWORD_INDEX] == AND)
			form_gate(tokens[DATA_INDEX], AND, line_num);
		else if (tokens[KEYWORD_INDEX] == NAND)
			form_gate(tokens[DATA_INDEX], NAND, line_num);
		else if (tokens[KEYWORD_INDEX] == OR)
			form_gate(tokens[DATA_INDEX], OR, line_num);
		else if (tokens[KEYWORD_INDEX] == NOR)
			form_gate(tokens[DATA_INDEX], NOR, line_num);
		else if (tokens[KEYWORD_INDEX] == XOR)
			form_gate(tokens[DATA_INDEX], XOR, line_num);	
		else if (tokens[KEYWORD_INDEX] == END_MODULE)
			if(tokens.size() > 1 || sv_lines.size() > line_num )
				throw invalid_argument("Invalid values after 'endmodule'\n");
			else
			{
				add_io_to_logic();
				break;
			}
		else
			throw invalid_argument("Line " + to_string(line_num) + ": undefined syntax\n");
		line_num ++;
	}
}

Logic* Compiler::get_logic()
{
	return logic;
}

void Compiler::form_gate(string data, string gate, int line_num)
{
	check_gate_line_syntax(data, line_num);
	int index1 = data.find(SYMBOLS[L_PAR]);
	int index2 = data.find(SYMBOLS[R_PAR]);
	int index3 = data.find(SYMBOLS[L_PAR], index2 + 1);
	int index4 = data.find(SYMBOLS[R_PAR], index2 + 1);
	int index5 = data.find(SYMBOLS[COMM], index2 + 1);
	vector<int> delay_values = find_delay_values(data.substr(index1 + 1, index2 - index1 - 1));
	vector<string> _output = find_gate_io(data.substr(index3 + 1, index5 -index3 - 1));
	vector<string> _inputs = find_gate_io(data.substr(index3 + 1, index4 - index3 - 1));
	wire* out = find_output(_output);
	vector<wire*> ins = find_inputs(_inputs);
	if(gate == AND)
		logic->L_AND(delay_values[0], delay_values[1], out, ins);
	else if(gate == NAND)	
		logic->L_NAND(delay_values[0], delay_values[1], out, ins);
	else if(gate == OR)
		logic->L_OR(delay_values[0], delay_values[1], out, ins);
	else if(gate == NOR)
		logic->L_NOR(delay_values[0], delay_values[1], out, ins);
	else if(gate == XOR)
		logic->L_XOR(delay_values[0], delay_values[1], out, ins);	
}

wire* Compiler::find_output(vector<string> output)
{
	for(auto out:inputs)
		if(out->name == output[0])
			return out;
	for(auto out:outputs)
		if(out->name == output[0])
			return out;
	for(auto out:wires)
		if(out->name == output[0])
			return out;
}

vector<wire*> Compiler::find_inputs(vector<string> _inputs)
{
	vector<wire*> ins;
	for(auto l_in:_inputs)
		for(auto in:inputs)
			if(l_in == in->name)
				ins.push_back(in);
	for(auto l_in:_inputs)
		for(auto in:wires)
			if(l_in == in->name)
				ins.push_back(in);
	for(auto l_in:_inputs)
		for(auto in:outputs)
			if(l_in == in->name)
				ins.push_back(in);
	return ins;
}

vector<int> Compiler::find_delay_values(string data)
{
	vector<int> delay;
	int index = data.find(SYMBOLS[COMM]);
	if(index == string::npos)
	{
		delay.push_back(stoi(data));
		delay.push_back(stoi(data));
	}
	else
	{
		delay.push_back(stoi(data.substr(0, index)));
		delay.push_back(stoi(data.substr(index + 1, data.size() - index - 1)));
	}
	return delay;
}

vector<string> Compiler::find_gate_io(string data)
{
	vector<string> elements;
	while(find(data.begin(), data.end(), SYMBOLS[COMM]) != data.end())
	{
		int index1 = data.find(SYMBOLS[COMM]);
		int index2 = data.find(SYMBOLS[COMM], index1 + 1);
		if(index2 != string::npos)
		    elements.push_back(data.substr(index1 + 1, index2 - index1 - 1));
		else
			elements.push_back(data.substr(index1 + 1, data.size() - index1 - 1));
		data = data.substr(index2 + 1, data.size() - index2 - 1);
	}
	elements.push_back(data);
	return elements;
}

void Compiler::add_io_to_logic()
{
	logic->set_inputs(inputs);
	logic->set_outputs(outputs);
	logic->set_intermediates(wires);
}

void Compiler::assign_variables(string data, int line_num)
{
	vector<string> tokens = separate_line_by_first_token(data);
	check_module_line_syntax(tokens, line_num);
	int index = 0;
	string variable = "";
	data = tokens[DATA_INDEX];
	while(index != data.size())
	{
		if(data[index] != SPACE && find(SYMBOLS, SYMBOLS + 5, data[index]) == SYMBOLS + 5)
			variable.push_back(data[index]);
		else if(variable != "")
		{
			wire* var = new wire;
			var->name = variable;
			io.push_back(var);
			variable = "";
		}
		index ++;
	}
}

void Compiler::assign_iow_variables(string data, int line_num, string io)
{
	check_io_line_syntax(data, line_num);
	string variable;
	vector<string> variables;
	int index = 0;
	while(index != data.size())
	{
		if(data[index] != SPACE && data[index] != SYMBOLS[COMM] && data[index] != SYMBOLS[SEM_COMM])
			variable.push_back(data[index]);
		else if(variable != "")
		{
			check_io_correctness(variable, line_num, io);
			wire* var = new wire;
			var->name = variable;
			if(io == INPUT)
				inputs.push_back(var);
			else if(io == OUTPUT)
				outputs.push_back(var);
			else
				wires.push_back(var);
			variable = "";
		}
		index ++;
	}
}

void Compiler::check_sem_comm_syntax(string data, int line_num)
{
	if(*(data.end() - 1) != SYMBOLS[SEM_COMM])
		throw invalid_argument("Line " + to_string(line_num) + ": missing ;\n");
}

void Compiler::check_module_line_syntax(vector<string> tokens, int line_num)
{
	if(tokens.size() <= 1)
		throw invalid_argument("Line " + to_string(line_num) + ": missing module name\n");
	string data = tokens[DATA_INDEX];
	if(find(KEY_WORDS.begin(), KEY_WORDS.end(), tokens[KEYWORD_INDEX]) != KEY_WORDS.end())
		throw invalid_argument("Line " + to_string(line_num) + ": unacceptable module name\n");
	else if(data[0] != SYMBOLS[L_PAR])
		throw invalid_argument("Line " + to_string(line_num) + ": missing '('\n");
	else if(find(data.begin(), data.end(), SPACE) != data.end())
		throw invalid_argument("Line " + to_string(line_num) + ": missing ','\n");
	else if(*(data.end() - 2) != SYMBOLS[R_PAR])
		throw invalid_argument("Line " + to_string(line_num) + ": missing ')'\n");
}

void Compiler::check_io_line_syntax(string data, int line_num)
{
	data = delete_extra_spaces(data);
	if(find(data.begin(), data.end(), SPACE) != data.end())
		throw invalid_argument("Line " + to_string(line_num) + ": missing ','\n");
	else if(find(data.begin(), data.end(), SYMBOLS[L_PAR]) != data.end())
		throw invalid_argument("Line " + to_string(line_num) + ": undefined '('\n");
	else if(find(data.begin(), data.end(), SYMBOLS[R_PAR]) != data.end())
		throw invalid_argument("Line " + to_string(line_num) + ": undefined ')'\n");
	else if(find(data.begin(), data.end(), SYMBOLS[SHP]) != data.end())
		throw invalid_argument("Line " + to_string(line_num) + ": undefined '#'\n");
}

void Compiler::check_io_correctness(string variable, int line_num, string _io)
{
	bool fault = false;
	bool fault2 = true;
	vector<vector<wire*>> iow;
	if(_io != WIRE)
		for(auto val:io)
			if(val->name == variable)
				fault2 = false;
	if(fault2 && _io != WIRE)
		throw invalid_argument("Line " + to_string(line_num) + ": variable '" + variable + "' is not defined\n");
	for(auto vec:iow)
	{
		for(auto val:vec)
			if(val->name == variable)
			{
				fault = true;
				break;
			}
		if(fault)
			throw invalid_argument("Line " + to_string(line_num) + ": cannot declare variable '" + variable + "' again\n");
	}					
}

void Compiler::check_gate_line_syntax(string data, int line_num)
{
	data = delete_extra_spaces(data);
	if(data[0] != SYMBOLS[SHP])
		throw invalid_argument("Line " + to_string(line_num) + ": missing '#'\n");
	else if(data[1] != SYMBOLS[L_PAR])
		throw invalid_argument("Line " + to_string(line_num) + ": missing '('\n");
	else if(find(data.begin(), data.end() - 2, SYMBOLS[R_PAR]) == data.end() - 2)
		throw invalid_argument("Line " + to_string(line_num) + ": missing ')'\n");
	else if(find(data.begin() + 2, data.end(), SYMBOLS[L_PAR]) == data.end())
		throw invalid_argument("Line " + to_string(line_num) + ": missing '('\n");
	else if(*(data.end() - 2) != SYMBOLS[R_PAR])
		throw invalid_argument("Line " + to_string(line_num) + ": missing ')'\n");
	else if(find(data.begin(), data.end(), SPACE) != data.end())
		throw invalid_argument("Line " + to_string(line_num) + ": missing ','\n");
}

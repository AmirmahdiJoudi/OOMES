// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 1
// Revision: 2021-05-12

#include "compiler.h"
#include <math.h>

using namespace std;

Compiler::Compiler(string sv_file_address)
{
	sv_lines = get_sv_lines(sv_file_address);
	logic = new Logic();
}

Compiler::~Compiler()
{
	delete logic;
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
		else if(tokens[KEYWORD_INDEX] == ASSIGN)
			form_gate(tokens[DATA_INDEX]);	
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

void Compiler::form_gate(string data)
{
	vector<string> tokens = separate_by(data, '=');	
	make_gates(tokens);
}

void Compiler::make_gates(std::vector<std::string> tokens)
{
	QM qm;
	vector<string> terms = separate_by(qm.minimize(tokens[DATA_INDEX].substr(0,tokens[DATA_INDEX].size() - 1)), '|');
	string o_name = find_assign_output(tokens[KEYWORD_INDEX]);
	if(find(terms[0].begin(), terms[0].end(), '?') == terms[0].end())
	{
		for(auto term:terms)
		{
			form_and_gates(term);
		}
		add_wires(o_name);
		vector<wire*> w = get_wires(o_name);
		int or_delay = int(log(or_inps.size())/log(2)) * OR_DELAY;
		logic->L_OR(or_delay, or_delay, w[0], or_inps);
		or_inps.clear();
	}
	else
	{
		form_cond_gates(o_name, terms[0]);
	}
}

void Compiler::add_wires(std::string term)
{
	vector<string> w = separate_by(term, '&');
	for(auto s:w)
	{
		bool found = false;
		for(auto x:wires)
			if(x->name == s)
			{
				found = true;
				break;
			}
		if(!found)
		{
			wire* wi = new wire;
			wi->name = s;
			wires.push_back(wi);
		}
	}
}

std::vector<wire*> Compiler::get_wires(std::string term)
{
	vector<string> w = separate_by(term, '&');
	vector<wire*> out;
	for(auto x:wires)
		if(find(w.begin(), w.end(), x->name) != w.end())
			out.push_back(x);
	return out;
}

void Compiler::form_and_gates(std::string term)
{

	add_wires(term);
	vector<wire*> and_inps = get_wires(term);
	vector<wire*> new_and_inps;
	int and_delay = int(log(and_inps.size())/log(2)) * AND_DELAY;
	for(int i = 0; i < and_inps.size(); i++)
	{
		if((and_inps[i]->name)[0] == '~')
		{
			vector<wire*> in = get_wires((and_inps[i]->name).substr(1, (and_inps[i]->name).size() - 1));
			logic->L_NOT(NOT_DELAY, NOT_DELAY, and_inps[i], in);
			new_and_inps.push_back(and_inps[i]);
			in.clear();
		}
		else
		{
			new_and_inps.push_back(and_inps[i]);
		}
	}
	wire* out = new wire;
	out->name = term;
	logic->L_AND(and_delay, and_delay, out, new_and_inps);
	wires.push_back(out);
	or_inps.push_back(out);
}

void Compiler::form_cond_gates(std::string o_name, std::string term)
{
	int index1;
	int index2;
	for(int i = 0; i < term.size(); i++)
		if(term[i] == '?')
			index1 = i;
	for(int i = 0; i < term.size(); i++)
		if(term[i] == ':')
			index2 = i;
	string s0 = term.substr(0, index1);
	string s1 = term.substr(index1 + 1, index2 - index1 - 1);
	string s2 = term.substr(index2 + 1, term.size() - index2 - 1);
	vector<wire*> sel = get_wires(s0);
	vector<wire*> f1 = get_wires(s1);
	vector<wire*> f2 = get_wires(s2);
	wire* seln = new wire;
	seln->name = "seln";
	wire* o1 = new wire;
	o1->name = "o1";
	wire* o2 = new wire;
	o2->name = "o2";
	add_wires(o_name);
	vector<wire*> o = get_wires(o_name);
	logic->L_NOT(NOT_DELAY, NOT_DELAY, seln, sel);
	f1.insert(f1.end(), sel.begin(), sel.end());
	f2.push_back(seln);
	logic->L_AND(AND_DELAY, AND_DELAY, o1, f1);
	logic->L_AND(AND_DELAY, AND_DELAY, o2, f2);
	vector<wire*> f_inp;
	f_inp.push_back(o1);
	f_inp.push_back(o2);
	wires.push_back(o1);
	wires.push_back(o2);
	wires.push_back(seln);
	logic->L_OR(OR_DELAY, OR_DELAY, o[0], f_inp);
}

std::string Compiler::find_assign_output(std::string stm)
{
	string o_name = delete_extra_spaces(stm);
	for(int i = 0; i < o_name.size(); i++)
		if(o_name[i] == SPACE)
		{
			o_name = o_name.substr(i + 1,o_name.size() - i - 1);
			break;
		}
	return o_name;
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
	string variable;
	vector<string> variables;
	int index = 0;
	while(index != data.size())
	{
		if(data[index] != SPACE && data[index] != SYMBOLS[COMM] && data[index] != SYMBOLS[SEM_COMM])
			variable.push_back(data[index]);
		else if(variable != "")
		{
			wire* var = new wire;
			var->name = variable;
			if(io == INPUT)
			{
				inputs.push_back(var);
				wires.push_back(var);
			}
			else if(io == OUTPUT)
			{
				outputs.push_back(var);
				wires.push_back(var);
			}
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
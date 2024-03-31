// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 2
// Revision: 2021-04-16

#ifndef __gate__H
#define __gate__H "gate.h"

#include "wire.h"
#include <vector>
#include <string>
#include <iostream>

class Gate
{
public:
	int gate_identifier;
	Gate();
	Gate(Wire* in1, Wire* in2, Wire* out);  
	Gate(Wire* in1, Wire* out);   
	virtual void eval() = 0; 
	virtual std::vector<std::string> get_faults() = 0;  
    virtual std::vector<Wire*> branch_fanout();
    virtual std::vector<Wire*> get_inputs();   
    Wire* get_output();      
protected:
	Wire* input1;
	Wire* input2;
	Wire* output;
	static int number_of_gates;
};

class Not : public Gate
{
public:
	Not();
	Not(Wire* in1, Wire* out);
	void eval();
	std::vector<std::string> get_faults();
	std::vector<Wire*> branch_fanout();
	std::vector<Wire*> get_inputs();  
};

class Nand : public Gate
{
public:
	Nand();
	Nand(Wire* in1, Wire* in2, Wire* out);
	void eval();
	std::vector<std::string> get_faults();
};

class Nor : public Gate
{
public:
	Nor();
	Nor(Wire* in1, Wire* in2, Wire* out);
	void eval();
	std::vector<std::string> get_faults();
};

#endif
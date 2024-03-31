// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 1
// Revision: 2021-03-16

#ifndef __GATE__H
#define __GATE__H "gate.h"

#include "wire.h"
#include <vector>
#include <string>
#include <limits>
#include <iostream>

class Gate
{
public:
	Gate(int to1, int to0, std::vector<wire*> in, wire* out);   
	virtual void calc_output() = 0;                
protected:
	std::vector<wire*> inputs;
	wire* output;
	int to1_delay;
	int to0_delay;
	int find_fastest_zero_input();
	int find_fastest_one_input();
	int find_slowest_input();
	char new_val;
};

class AND_n : public Gate
{
public:
	AND_n(int to1, int to0, std::vector<wire*> in, wire* out);
	void calc_output();
private:
	void and_2b(char& val, wire* in1, wire* in2);
};

class NAND_n : public Gate
{
public:
	NAND_n(int to1, int to0, std::vector<wire*> in, wire* out);
	void calc_output();
private:
	void nand_2b(char& val, wire* in1, wire* in2);
};

class OR_n : public Gate
{
public:
	OR_n(int to1, int to0, std::vector<wire*> in, wire* out);
	void calc_output();
private:
	void or_2b(char& val, wire* in1, wire* in2);
};

class NOR_n : public Gate
{
public:
	NOR_n(int to1, int to0, std::vector<wire*> in, wire* out);
	void calc_output();
private:
	void nor_2b(char& val, wire* in1, wire* in2);
};

class XOR_n : public Gate
{
public:
	XOR_n(int to1, int to0, std::vector<wire*> in, wire* out);
	void calc_output();
private:
	void xor_2b(char& val, wire* in1, wire* in2);
};

#endif
// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 2
// Revision: 

#include "wire.h"
#include "gate.h"
#include "functions.h"
#include "fs.h"

#include <string>
#include <vector>

#ifndef __FC__H
#define __FC__H "fc.h"

#include <string>

class FC
{
public:
	FC(std::vector<Gate*> _gates, std::vector<Wire*> _all_wires, std::vector<Wire*> _outputs, std::vector<Wire*> _inputs);
	std::vector<std::string> fault_collapse();
	FS* get_fs();
private:
	std::vector<Gate*> gates;
	std::vector<Wire*> all_wires;
	std::vector<Wire*> outputs;
	std::vector<Wire*> inputs;
	std::vector<std::string> l_faults;
	void branch_fanout();
};

#endif
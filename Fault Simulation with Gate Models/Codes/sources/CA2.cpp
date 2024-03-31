// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 2
// Revision: 2021-04-16

#include "wire.h"
#include "gate.h"
#include "compiler.h"
#include "logic.h"
#include "fc.h"
#include "fs.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>

int Wire::number_of_wires = ZERO;
int Gate::number_of_gates = ZERO;

using namespace std;

int main(int argc, char* argv[])
{
	if(argc >= TWO)
	{
		Compiler compiler(argv[ONE]);
    	try
    	{
    	    compiler.compile();
    		if(argc >= THREE)
    		{
    			vector<string> faults;
                vector<string> sim;
    			ofstream fc_output_file("fc_output_file.txt");
                ofstream fs_output_file("fs_output_file.txt");
    			Logic* logic = compiler.get_logic();
    			logic->calculate();
    			FC* fc = logic-> get_fc();
    			faults = fc-> fault_collapse();
    			for(auto line:faults)
    				fc_output_file << line << endl;
	    		fc_output_file.close();
	    		FS* fs = fc-> get_fs();
                sim = fs-> calculate(argv[TWO]);
                for(auto line:sim)
                    fs_output_file << line << endl;
                fs_output_file.close();
    		}
    	}
    	catch (invalid_argument& ex)
    	{
    	    cerr << ex.what();
    	}
    }
}
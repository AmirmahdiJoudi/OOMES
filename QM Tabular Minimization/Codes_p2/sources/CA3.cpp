// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 3
// Revision: 2021-05-10

#include "compiler.h"
#include "logic.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <exception>

using namespace std;

int main(int argc, char* argv[])
{
	if(argc >= 2)
	{
		Compiler compiler(argv[1]);
    	try
    	{
    	    compiler.compile();
    		if(argc >= 3)
    		{
    			ofstream output_file("output_file.txt");
    			Logic* logic = compiler.get_logic();
    			vector<string> results = logic->calculate(argv[2]);
    			for(auto line:results)
	    			output_file << "#" << line << endl;
	    		output_file.close();
    		}
    	}
    	catch (invalid_argument& ex)
    	{
    	    cerr << ex.what();
    	}
    }
}
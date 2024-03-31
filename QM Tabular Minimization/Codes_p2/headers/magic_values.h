// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 1
// Revision: 2021-03-08

#ifndef __MAGIC_VALUES__
#define __MAGIC_VALUES__ "magic_values.h"

#include <vector>
#include <string>

const std::string MODULE = "module";
const std::string INPUT = "input";
const std::string OUTPUT = "output";
const std::string ASSIGN = "assign";
const std::string WIRE = "wire";
const std::string END_MODULE = "endmodule";

const std::vector<std::string> KEY_WORDS = {MODULE, INPUT, OUTPUT, ASSIGN, WIRE, END_MODULE};

const char SPACE = ' ';
const char SYMBOLS[5] = {'(', ')', ',', '#', ';'};
const int SYMBOLS_NUM = 5;

const int L_PAR = 0;
const int R_PAR = 1;
const int COMM = 2;
const int SHP = 3;
const int SEM_COMM = 4;
const int KEYWORD_INDEX = 0;
const int DATA_INDEX = 1;
const int AT_FIRST = 0;

const int AND_DELAY = 5;
const int OR_DELAY = 5;
const int NOT_DELAY = 3;
#endif
// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 1
// Revision: 2021-03-08

#ifndef __FUNCTIONS__H
#define __FUNCTIONS__H "functions.h"

#include "magic_values.h"

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

std::vector<std::string> get_sv_lines(std::string sv_file_address);
std::vector<std::string> separate_line_by_first_token(std::string line);
std::vector<std::string> pretty(std::vector<std::string> lines);
std::string delete_extra_spaces(std::string data);

#endif
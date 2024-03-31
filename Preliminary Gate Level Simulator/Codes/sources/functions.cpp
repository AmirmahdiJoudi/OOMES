// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 1
// Revision: 2021-03-08

#include "functions.h"

using namespace std;

vector<string> get_sv_lines(string sv_file_address)
{
	vector<string> sv_lines;
	ifstream sv_file(sv_file_address);
	string line;
	while(getline(sv_file , line))
		sv_lines.push_back(line);
	sv_file.close();
	return sv_lines;
}

vector<string> separate_line_by_first_token(string line)
{
	vector <string> tokens;
	string token;
	int index = 0;
	while(line[0] == SPACE)
    	line = line.substr(1, line.size() - 1);
	while(line[index] != SPACE && find(SYMBOLS, SYMBOLS + 5, line[index]) == SYMBOLS + 5 && index < line.size())
		index ++;
	token = delete_extra_spaces(line.substr(0, index));
	tokens.push_back(token);
	if(line.size() != index)
	{
		token = delete_extra_spaces(line.substr(index, line.size() - index));
	    tokens.push_back(token);
	}
	return tokens;
}

std::vector<std::string> pretty(std::vector<std::string> lines)
{
	vector<int> digits;
	int max;
	for(auto line:lines)
	{
		int index1 = 0;
		int index2 = line.find(" ");
		digits.push_back(index2 - index1 - 1);
	}
	max = *max_element(digits.begin(), digits.end());
	for(int index = 0; index < lines.size(); index++)
	{
		int index1 = 0;
		int index2 = lines[index].find(" ");
		for(int time = 0; time < max - digits[index]; time++)
			lines[index].insert(lines[index].begin(), '0');
	}
	return lines;
}

string delete_extra_spaces(string line)
{
    while(line[0] == SPACE)
    	line = line.substr(1, line.size() - 1);
    while(*(line.end() - 1) == SPACE)
    	line = line.substr(0, line.size() - 1);
    if(line.size() == 1)
    	return line;
    for(int index = 0; index <= line.size() - 1; index ++)
    	if(line[index] == SPACE && (line[index + 1] == SPACE || find(SYMBOLS, SYMBOLS + SYMBOLS_NUM, line[index + 1]) != SYMBOLS + SYMBOLS_NUM))
    		line = line.substr(0, index) + line.substr(index + 1, line.size() - index - 1);
    	else if(find(SYMBOLS, SYMBOLS + SYMBOLS_NUM, line[index]) != SYMBOLS + SYMBOLS_NUM  && line[index + 1] == SPACE)
    		line = line.substr(0, index + 1) + line.substr(index + 2, line.size() - index - 2);
    return line;
}
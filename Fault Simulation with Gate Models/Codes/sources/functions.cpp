// Amirmahdi Joudi
// Object Oriented Modeling of Electronic Circuits
// Computer Assignment 1
// Revision: 2021-04-16

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
	while(line[ZERO] == SPACE)
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

std::vector<std::string> sort(std::vector<std::string> lines, std::vector<int> first_space)
{
	for(int i = 0; i < lines.size(); i++)
		for(int j = 0; j < lines.size() - 1; j++)
		{
			if(lines[j].substr(0, first_space[j]) > lines[j + 1].substr(0, first_space[j+1]))
			{
				iter_swap(lines.begin() + j, lines.begin() + j + 1);
				iter_swap(first_space.begin() + j, first_space.begin() + j + 1);
			}
		}
	return lines;
}

std::vector<std::string> pretty(std::vector<std::string> lines)
{
	vector<int> first_space;
	vector<int> second_space;
	vector<int> size;
	for(auto line:lines)
	{
		int index1 = line.find(SPACE);
		int index2 = line.find(SPACE, index1 + 1);
		first_space.push_back(index1);
		second_space.push_back(index2);
		size.push_back(index2 - index1 - 1);
	}
	int max1 = *max_element(begin(first_space), end(first_space));
	int max2 = *max_element(begin(size), end(size));
	for(int i = 0; i < lines.size(); i++)
	{
		for(int j = 0; j < max2 - size[i]; j++)
			lines[i].insert(second_space[i], " ");
		for(int j = 0; j < max1 - first_space[i]; j++)
			lines[i].insert(first_space[i], " ");
	}
	lines = sort(lines, first_space);
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
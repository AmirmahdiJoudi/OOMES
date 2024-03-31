#ifndef __QM__H
#define __QM__h "QM.h"

#include <string>
#include <vector>
#include <iostream>

class QM
{
public:
	QM();
	std::string minimize(std::string expr);
private:
	std::string expression;
	std::vector<std::string> and_exprs;
	std::vector<std::string> removed_exprs;
	std::vector<std::vector<std::vector<std::string>>> cubes;
	std::vector<std::vector<std::string>> form_zero_cube();
	std::vector<std::vector<std::string>> form_other_cubes();
	std::string delete_extra_spaces(std::string line);
	std::vector<std::string> separate_by(std::string sentence, char c);
	std::vector<std::string> diff(std::string f, std::string s);
	std::vector<std::string> set_similarities(std::vector<std::string>& v, std::vector<std::string>& d);
	std::vector<std::string> select(std::vector<std::string> f);
	std::vector<std::string> sel_pis(std::vector<std::string> f, std::vector<std::vector<std::string>> c);
	std::string finalize();
	std::string beautify(std::vector<std::string> expr);
	std::string find_unique_pi(std::vector<std::vector<std::string>> c);
	void separate_and_exprs();
	int largest_sentece();
	int x_elements(std::string s);
	int count_char(std::string expr, char c);
};

#endif
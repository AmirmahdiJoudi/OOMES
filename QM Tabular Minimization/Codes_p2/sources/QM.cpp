#include "QM.h"
#include <algorithm>

using namespace std;

QM::QM()
{
	expression = "";
}

std::string QM::minimize(std::string expr)
{
	string minimized_expr;
	expression = expr;
	separate_and_exprs();
	vector<vector<string>> ones;
	for(int i = 0; i < largest_sentece(); i++)
	{
		ones = form_other_cubes();
		if(ones.size() != 0)
			cubes.push_back(ones);
	}
	minimized_expr = finalize();
	cout << minimized_expr<<endl;
	return minimized_expr;
}

void QM::separate_and_exprs()
{
	string sentence = expression;
	and_exprs = separate_by(sentence, '|');
	vector<vector<string>> ones = form_zero_cube();
	cubes.push_back(ones);
}

std::vector<std::string> QM::separate_by(std::string sentence, char c)
{
	vector<string> exprs;
	while(true)
	{
		int index = sentence.find(c);
		if(index != string::npos)
		{
			string expr = delete_extra_spaces(sentence.substr(0, index));
			exprs.push_back(expr);
			sentence = sentence.substr(index + 1, sentence.size() - index - 1);
		}
		else
		{
			string expr = delete_extra_spaces(sentence);
			exprs.push_back(expr);
			break;
		}
	}
	return exprs;
}

std::string QM::delete_extra_spaces(std::string line)
{
	char SPACE = ' ';
    while(line[0] == SPACE)
    	line = line.substr(1, line.size() - 1);
    while(*(line.end() - 1) == SPACE)
    	line = line.substr(0, line.size() - 1);
    if(line.size() == 1)
    	return line;
    for(int index = 0; index <= line.size() - 1; index ++)
    	if(line[index] == SPACE)
    		line = line.substr(0, index) + line.substr(index + 1, line.size() - index - 1);
    return line;
}

std::vector<std::vector<std::string>> QM::form_zero_cube()
{
	int n = largest_sentece();
	vector<vector<string>> ones;
	vector<string> one;
	for(int i = 0; i <= n; i++)
	{	
		one.clear();
		for(auto expr:and_exprs)
		{
			if(count_char(expr, '&') - count_char(expr, '~') == i - 1)
				one.push_back(expr);
		}
		ones.push_back(one);
	}
	return ones;
}

std::vector<std::vector<std::string>> QM::form_other_cubes()
{
	vector<vector<string>> previous_cube = *(cubes.end() - 1);
	vector<vector<string>> new_cube;
	for(int i = 0; i < previous_cube.size() - 1; i++)
	{
		vector<string> first = previous_cube[i];
		vector<string> second = previous_cube[i + 1];
		vector<string> df;
		for(auto f:first)
		{
			for(auto s:second)
			{
				vector<string> df1 = diff(f,s);
				if(df1.size() != 0)
					df.insert(df.end(), df1.begin(), df1.end());
			}
		}
		df.erase( unique( df.begin(), df.end() ), df.end() );
		if(df.size() != 0)
			new_cube.push_back(df);
	}
	return new_cube;
}

std::vector<std::string> QM::diff(std::string f, std::string s) 
{
	vector<string> sim;
	vector<string> f_actors = separate_by(f, '&');
	vector<string> s_actors = separate_by(s, '&');
	vector<string> diff1(10);
	vector<string> diff2(10);
	vector<string> ff = f_actors;
	vector<string> ss = s_actors;
	sort(ff.begin(), ff.end());
	sort(ss.begin(), ss.end());
	vector<string>::iterator it1 = set_difference(ff.begin(), ff.end(), ss.begin(), ss.end(), diff1.begin());
	vector<string>::iterator it2 = set_difference(ss.begin(), ss.end(), ff.begin(), ff.end(), diff2.begin());
	diff1.resize(it1 - diff1.begin());
	diff2.resize(it2 - diff2.begin());
	if(diff1.size() == 1 && diff2.size() == 1)
	{
		if(diff1[0][0] == '~')
			if(diff1[0].substr(1, diff1[0].size()) == diff2[0])
			{	
				removed_exprs.push_back(f);
				removed_exprs.push_back(s);
				sim = set_similarities(f_actors, diff1);
			}
		else if(diff2[0][0] == '~')
			if(diff2[0].substr(1, diff2[0].size()) == diff1[0])
			{
				removed_exprs.push_back(f);
				removed_exprs.push_back(s);
				sim = set_similarities(s_actors, diff2);
			}
	}
	return sim;
}

std::vector<std::string> QM::set_similarities(std::vector<std::string>& v, std::vector<std::string>& d)
{
	vector<string> sim;
	for(int i = 0; i < v.size(); i++)
		if(v[i] == d[0])
		{
			v[i] = 'x';
			break;
		}
	string s;
	for (vector<string>::const_iterator i = v.begin(); i != v.end(); ++i)
   		s += (*i + "&");
   	s.pop_back();
   	sim.push_back(s);
   	return sim;
}

std::string QM::finalize()
{
	vector<string> final;
	string s;
	for(auto x:cubes)
		for(auto y:x)
			for(auto z:y)
				if(find(removed_exprs.begin(), removed_exprs.end(), z) == removed_exprs.end())
					final.push_back(z);
	final = select(final);
	s = beautify(final);
   	expression.clear();
   	and_exprs.clear();
   	removed_exprs.clear();
   	cubes.clear();
   	return s;
}

std::string QM::beautify(std::vector<std::string> expr)
{
	string s;
	for(auto& x:expr)
		for(int i = 0; i < x.size(); i++)
			if(x[i] == 'x')
				x = x.substr(0,i) + x.substr(i+1, x.size());
	for(auto& x:expr)
		while(x[0] == '&')
			x = x.substr(1, x.size() - 1);
	for(auto& x:expr)
		while(*(x.end() - 1) == '&')
			x = x.substr(0, x.size() - 1);
	for(auto& x:expr)
		for(int i = 0; i < x.size() - 1; i++)
			while(x[i] == '&' && x[i + 1] == '&')
				x = x.substr(0,i) + x.substr(i+1, x.size());
	for (vector<string>::const_iterator i = expr.begin(); i != expr.end(); ++i)
   		s += (*i + " | ");
   	s.pop_back();
   	s.pop_back();
   	return s;
}

std::vector<std::string> QM::select(std::vector<std::string> f)
{
	vector<vector<string>> covered;
	vector<string> PIs;
	vector<string> diff1(10);
	vector<string> diff2(10);
	for(auto ff:f)
	{
		vector<string> layer;
		vector<string> fff = separate_by(ff, '&');
		for(auto z:cubes[0])
		{
			for(auto zz:z)
			{
				vector<string> zzz = separate_by(zz, '&');
				vector<string> ffff = fff;
				vector<string> zzzz = zzz;
				sort(ffff.begin(), ffff.end());
				sort(zzzz.begin(), zzzz.end());
				vector<string>::iterator it1 = set_difference(ffff.begin(), ffff.end(), zzzz.begin(), zzzz.end(), diff1.begin());
				vector<string>::iterator it2 = set_difference(zzzz.begin(), zzzz.end(), ffff.begin(), ffff.end(), diff2.begin());
				int allowed_diff = x_elements(ff);
				diff1.resize(it1 - diff1.begin());
				diff2.resize(it2 - diff2.begin());
				if(diff1.size() == allowed_diff && diff2.size() == allowed_diff)
					layer.push_back(zz);
			}
		}
		covered.push_back(layer);
	}
	PIs = sel_pis(f, covered);
	return PIs;
}

std::vector<std::string> QM::sel_pis(std::vector<std::string> f, std::vector<std::vector<std::string>> c) /////// I AM HERE
{
	vector<string> final;
	int n;
	do
	{
		n = 0;
		vector<string> all;
		string uni = find_unique_pi(c);;
		vector<vector<int>> del;
		for(int i = 0; i < c.size(); i++)
		{
			vector<string>::iterator itn = find(c[i].begin(), c[i].end(), uni);
			if(itn != c[i].end())
			{
				for(int k = 0; k < c.size(); k++)
				{
					for(int j = 0; j < c[k].size(); j++)
					{
						if(find(c[i].begin(), c[i].end(), c[k][j]) != c[i].end())
						{
							vector<int> n;
							n.push_back(k);
							n.push_back(j);
							del.push_back(n);
						}
					}
				}
				for(auto n:del)
					c[n[0]].erase(c[n[0]].begin() + n[1]);
				for(int i = 0; i < c.size(); i++)
					if(c[i].size() == 0)
						c.erase(c.begin() + i);
				final.push_back(f[i]);
				f.erase(f.begin() + i);
				del.clear();
			}
		}
		for(auto x:c)
			n += x.size();
	}while(n!=0);
	final.erase(unique(final.begin(), final.end() ), final.end() );
	return final;
}

std::string QM::find_unique_pi(std::vector<std::vector<std::string>> c)
{
	vector<string> all;
	string uni;
	for(auto el:c)
		all.insert(all.end(), el.begin(), el.end());
	sort(all.begin(), all.end());
	int u = -1;
	for(int i = 0;i<all.size() - 1; i++)
	{
		if(all[i] != all[i+1])
		{
			if(i == 0)
			{
				u=i;
				break;
			}
			else if(i!=0)
				if(all[i] != all[i-1])
				{
					u = i;
					break;
				}		
			}
		}
	if(u==-1)
		u = 0;
	return all[u];
}

int QM::largest_sentece()
{
	int max = 0;
	for(auto expr:and_exprs)
	{
		int count = count_char(expr, '&');
		if(count > max)
			max = count;
	}
	return max + 1;
}

int QM::x_elements(std::string s)
{
	int count = 0;
	for(int i = 0; i < s.size(); i++)
		if(s[i] == 'x')
			count++;
	return count;
}

int QM::count_char(std::string expr, char c)
{
	int count = 0;
	for(int i = 0; i < expr.size(); i++)
		if(expr[i] == c)
			count ++;
	return count;
}
#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <iostream>
# include <cstdlib>
# include <iterator>
# include <list>
# include <vector>

using std::string;

class PmergeMe
{
	private:
		std::list<unsigned int>		lst;
		std::vector<unsigned int>	vec;
		string				arg;

	public:
		PmergeMe(char** arg);
		PmergeMe(const PmergeMe& cpy);
		~PmergeMe();

		PmergeMe&		operator=(const PmergeMe& cpy);
		void			add_arguments(char** arg);
		void			print_lst();
		void			print_vec();
		std::list<unsigned int>	list_merge(std::list<unsigned int> param);
};

#endif

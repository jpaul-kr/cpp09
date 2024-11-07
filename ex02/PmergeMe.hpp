#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# include <iostream>
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
		PmergeMe();
		PmergeMe(const PmergeMe& cpy);
		~PmergeMe();

		PmergeMe&	operator=(const PmergeMe& cpy);
}

#endif

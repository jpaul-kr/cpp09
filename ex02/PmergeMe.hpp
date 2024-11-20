#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# define MICROSEC 1000000
# include <iostream>
# include <cstdlib>
# include <iterator>
# include <list>
# include <vector>
# include <sys/time.h>
# include <iomanip>

using std::string;

class PmergeMe
{
	private:
		std::list<unsigned int>		lst;
		std::vector<unsigned int>	vec;
		string				arg;
		unsigned int			amount;
		float				vecTime;
		float				lstTime;

	public:
		PmergeMe(char** arg);
		PmergeMe(const PmergeMe& cpy);
		~PmergeMe();

		PmergeMe&			operator=(const PmergeMe& cpy);
		void				add_arguments(char** arg);
		void				print_result();
		void				print_time();
		void				print_vec();
		void				merge_process();
		std::list<unsigned int>		list_merge(std::list<unsigned int>& param1, std::list<unsigned int>& param2);
		std::list<unsigned int>		merge_lists(std::list<unsigned int> param1, std::list<unsigned int> param2);
		std::list<unsigned int>		getList();
		std::vector<unsigned int>	vector_merge(std::vector<unsigned int>& param1, std::vector<unsigned int>& param2);
		std::vector<unsigned int>	merge_vectors(std::vector<unsigned int> param1, std::vector<unsigned int> param2);

		class errorException : public std::logic_error
		{
			public:
				errorException();
		};

};

#endif

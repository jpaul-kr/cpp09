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
		//static int			jacobs[15];

	public:
		PmergeMe(char** arg);
		PmergeMe(const PmergeMe& cpy);
		~PmergeMe();

		PmergeMe&			operator=(const PmergeMe& cpy);
		void				add_arguments(char** arg);
		void				print_result();
		void				print_time();
		void				print_vec();
		void				print_vec(std::vector<unsigned int> aux);
		void				merge_process();
		std::list<unsigned int>		getList();
		std::vector<unsigned int>	vector_merge(std::vector<unsigned int>& src);
		std::vector<unsigned int>	merge_vectors(std::vector<unsigned int> src, size_t groupsize);
		std::vector<unsigned int>	jacob_sort(std::vector<unsigned int> src, size_t groupsize);
		void				insert_group(std::vector<unsigned int>& main, std::vector<unsigned int> src, size_t init, size_t end);

		class errorException : public std::logic_error
		{
			public:
				errorException();
		};

};

#endif

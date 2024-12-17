#ifndef PMERGEME_HPP
# define PMERGEME_HPP
# define MICROSEC 1000000
# include <iostream>
# include <cstdlib>
# include <iterator>
# include <deque>
# include <vector>
# include <sys/time.h>
# include <iomanip>

using std::string;

class PmergeMe
{
	private:
		std::deque<unsigned int>	deq;
		std::vector<unsigned int>	vec;
		string				arg;
		unsigned int			amount;
		float				vecTime;
		float				deqTime;
		int				jacob[15];

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
		void				print_vec(std::vector<unsigned int> aux, size_t groupsize);
		bool				is_repeat(int n, std::vector<unsigned int> vec);
		bool				is_valid(string arg);
		void				merge_process();

		void				compare_and_insert(std::vector<unsigned int>& main, std::vector<unsigned int> src, size_t pos, size_t groupsize);
		std::vector<unsigned int>	vector_merge(std::vector<unsigned int>& src);
		std::vector<unsigned int>	merge_vectors(std::vector<unsigned int> src, size_t groupsize);
		std::vector<unsigned int>	jacob_sort(std::vector<unsigned int> src, size_t groupsize);
		void				insert_group(std::vector<unsigned int>& main, std::vector<unsigned int> src, size_t init, size_t end, std::vector<unsigned int>::iterator pos);

		void				compare_and_insert(std::deque<unsigned int>& main, std::deque<unsigned int> src, size_t pos, size_t groupsize);
		std::deque<unsigned int>	deque_merge(std::deque<unsigned int>& src);
		std::deque<unsigned int>	merge_deques(std::deque<unsigned int> src, size_t groupsize);
		std::deque<unsigned int>	jacob_sort(std::deque<unsigned int> src, size_t groupsize);
		void				insert_group(std::deque<unsigned int>& main, std::deque<unsigned int> src, size_t init, size_t end, std::deque<unsigned int>::iterator pos);


		class errorException : public std::logic_error
		{
			public:
				errorException();
		};

};

#endif

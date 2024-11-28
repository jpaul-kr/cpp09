#include "PmergeMe.hpp"

static int	jacobs = {0, 2, 2, 6, 10, 22, 42, 87, 170, 342, 682, 1366, 2730, 5462, 10922};

PmergeMe::PmergeMe(char** arg) 
{
	int	n;
	int	i;

	for (i = 0; arg[i]; i++)
	{
		n = atoi(arg[i]);
		if (n < 0)
			throw errorException();
		this->lst.push_back(n);
		this->vec.push_back(n);
	}
	this->amount = i;
}

PmergeMe::PmergeMe(const PmergeMe& cpy)
{
	*this = cpy;
}

PmergeMe::~PmergeMe() {}

PmergeMe&	PmergeMe::operator=(const PmergeMe& cpy)
{
	this->lst = cpy.lst;
	this->vec = cpy.vec;
	this->arg = cpy.arg;
	return *this;
}

std::list<unsigned int>		PmergeMe::getList()
{
	return this->lst;
}

void		PmergeMe::print_vec()
{
	for (size_t i = 0; i < this->vec.size(); i++)
		std::cout << this->vec[i] << " ";
	std::cout << std::endl;
}

void		PmergeMe::print_result()
{
	std::cout << "Before: ";
	for (size_t i = 0; i < this->vec.size(); i++)
		std::cout << this->vec[i] << " ";
	std::cout << std::endl;

	std::cout << "After:  ";
	std::list<unsigned int>::iterator	it;
	std::list<unsigned int>::iterator	ite = this->lst.end();

	for (it = this->lst.begin(); it != ite; it++)
		std::cout << *it << " ";
	std::cout << std::endl;
		
}

std::list<unsigned int>		PmergeMe::merge_lists(std::list<unsigned int>& src, size_t& groupsize, size_t& groups)
{
	std::list<unsigned int>	aux = src;

	if (groupsize * groups < src.size())
	{
		for (size_t i = 0; i < groups; i++)
		{
			if (src)
		}
	}
}

std::list<unsigned int>		PmergeMe::list_merge(std::list<unsigned int> src, size_t& groupsize)
{
	std::list<unsigned int>		main;
	size_t				groups = src.size() / groupsize;

	if (groups * groupsize < src.size())
	{
		groupsize *= 2;
	}
}

std::vector<unsigned int>		PmergeMe::merge_vectors(std::vector<unsigned int>& src, size_t&	groupsize)
{
	size_t				groups = src.size() / groupsize;
	std::vector<unsigned int>	aux = src;

	if (groups * groupsize < src.size())
	{
	}
}

std::vector<unsigned int>		PmergeMe::vector_merge(std::vector<unsigned int>& src)
{
	std::vector<unsigned int>	main = src;
	size_t				groupsize = 1;

	merge_vectors(main, groupsize);
}

void	PmergeMe::print_time()
{
	std::cout << "Time to process a range of " << this->amount << " elements with std::vector : " << std::setprecision(5)  << this->vecTime << " us" << std::endl;
	std::cout << "Time to process a range of " << this->amount << " elements with std::list   : " << std::setprecision(5)  << this->lstTime << " us" << std::endl;
}

void	PmergeMe::merge_process()
{
	std::list<unsigned int>		auxlst;
	std::vector<unsigned int>	auxvec;
	struct timeval	start, end;

	/*gettimeofday(&start, NULL);
	this->lst = list_merge(this->lst);
	gettimeofday(&end, NULL);
	this->lstTime = (end.tv_sec - start.tv_sec) * MICROSEC + end.tv_usec - start.tv_usec;

	print_result();*/

	gettimeofday(&start, NULL);
	this->vec = vector_merge(this->vec, auxvec);
	gettimeofday(&end, NULL);
	this->vecTime = (end.tv_sec - start.tv_sec) * MICROSEC + end.tv_usec - start.tv_usec;
}

PmergeMe::errorException::errorException() : std::logic_error("\terror") {}


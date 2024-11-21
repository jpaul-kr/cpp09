#include "PmergeMe.hpp"

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

std::list<unsigned int>		PmergeMe::merge_lists(std::list<unsigned int> param1, std::list<unsigned int> param2)
{
	std::list<unsigned int>			aux;
	std::list<unsigned int>::iterator	it1 = param1.begin();
	std::list<unsigned int>::iterator	it2 = param2.begin();

	while (it1 != param1.end() && it2 != param2.end())
	{
		if (*it1 < *it2)
			aux.push_back(*(it1++));
		else
			aux.push_back(*(it2++));
	}
	while (it1 != param1.end())
		aux.push_back(*(it1++));
	while (it2 != param2.end())
		aux.push_back(*(it2++));
	return aux;
}

std::list<unsigned int>		PmergeMe::list_merge(std::list<unsigned int>& param1, std::list<unsigned int>& param2)
{
	std::list<unsigned int>			first;
	std::list<unsigned int>			second;
	std::list<unsigned int>::iterator	it;

	if (param1.size() > 1)
	{
		it = param1.begin();
		std::advance(it, param1.size() / 2);
		first.insert(first.begin(), param1.begin(), it);
		second.insert(second.begin(), it, param1.end());
		param1 = list_merge(first, second);
	}
	first.clear();
	second.clear();
	if (param2.size() > 1)
	{
		it = param2.begin();
		std::advance(it, param2.size() / 2);
		first.insert(first.begin(), param2.begin(), it);
		second.insert(second.begin(), it, param2.end());
		param2 = list_merge(first, second);
	}
	param1 = merge_lists(param1, param2);
	return param1;
}

std::vector<unsigned int>		PmergeMe::merge_vectors(std::vector<unsigned int> param1, std::vector<unsigned int> param2)
{
	std::vector<unsigned int>		aux;
	size_t					i = 0;
	size_t					j = 0;

	while (i < param1.size() && j < param2.size())
	{
		if (param1[i] < param2[j])
			aux.push_back(param1[i++]);
		else
			aux.push_back(param2[j++]);
	}
	while (i < param1.size())
		aux.push_back(param1[i++]);
	while (j < param2.size())
		aux.push_back(param2[j++]);
	return aux;
}

std::vector<unsigned int>		PmergeMe::vector_merge(std::vector<unsigned int>& param1, std::vector<unsigned int>& param2)
{
	std::vector<unsigned int>			first;
	std::vector<unsigned int>			second;
	std::vector<unsigned int>::iterator		it;

	if (param1.size() > 1)
	{
		it = param1.begin();
		std::advance(it, param1.size() / 2);
		first.insert(first.begin(), param1.begin(), it);
		second.insert(second.begin(), it, param1.end());
		param1 = vector_merge(first, second);
	}
	first.clear();
	second.clear();
	if (param2.size() > 1)
	{
		it = param2.begin();
		std::advance(it, param2.size() / 2);
		first.insert(first.begin(), param2.begin(), it);
		second.insert(second.begin(), it, param2.end());
		param2 = vector_merge(first, second);
	}
	param1 = merge_vectors(param1, param2);
	return param1;
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

	gettimeofday(&start, NULL);
	this->lst = list_merge(this->lst, auxlst);
	gettimeofday(&end, NULL);
	this->lstTime = (end.tv_sec - start.tv_sec) * MICROSEC + end.tv_usec - start.tv_usec;

	print_result();

	gettimeofday(&start, NULL);
	this->vec = vector_merge(this->vec, auxvec);
	gettimeofday(&end, NULL);
	this->vecTime = (end.tv_sec - start.tv_sec) * MICROSEC + end.tv_usec - start.tv_usec;
}

PmergeMe::errorException::errorException() : std::logic_error("\terror") {}


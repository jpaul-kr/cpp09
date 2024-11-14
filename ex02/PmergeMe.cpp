#include "PmergeMe.hpp"

PmergeMe::PmergeMe(char** arg) 
{
	unsigned int	n;

	for (int i = 0; arg[i]; i++)
	{
		n = std::strtoul(arg[i], NULL, 0);
		this->lst.push_back(n);
		this->vec.push_back(n);
	}
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

void		PmergeMe::print_lst()
{
	std::list<unsigned int>::iterator	it;
	std::list<unsigned int>::iterator	ite = this->lst.end();

	for (it = this->lst.begin(); it != ite; it++)
		std::cout << *it << " ";
	std::cout << std::endl;
		
}

void		PmergeMe::print_vec()
{
	for (size_t i = 0; i < this->vec.size(); i++)
		std::cout << this->vec[i] << " ";
	std::cout << std::endl;
		
}

std::list<unsigned int>		PmergeMe::list_merge(std::list<unsigned int> param1, std::list<unsigned int> param2)
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
	if (param2.size() > 1)
	{
		it = param2.begin();
		std::advance(it, param2.size() / 2);
		first.insert(first.begin(), param2.begin(), it);
		second.insert(second.begin(), it, param2.end());
		param1 = list_merge(first, second);
	}
	first.merge(second);
	return first;
}

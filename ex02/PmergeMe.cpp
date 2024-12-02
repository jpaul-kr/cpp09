#include "PmergeMe.hpp"

//static int	jacobs[15] = {0, 2, 2, 6, 10, 22, 42, 87, 170, 342, 682, 1366, 2730, 5462, 10922};

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

void		PmergeMe::print_vec(std::vector<unsigned int> aux)
{
	for (size_t i = 0; i < aux.size(); i++)
		std::cout << aux[i] << " ";
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

void		PmergeMe::insert_group(std::vector<unsigned int>& main, std::vector<unsigned int> src, size_t init, size_t end)
{
	for (size_t i = init; i <= end; i++)
		main.push_back(src[i]);
}

std::vector<unsigned int>		PmergeMe::jacob_sort(std::vector<unsigned int> src, size_t groupsize)
{
	std::vector<unsigned int>	main;
	size_t				groups = src.size() / groupsize;

	(void)groups;
	return main;
}

std::vector<unsigned int>		PmergeMe::merge_vectors(std::vector<unsigned int>& src, size_t&	groupsize)
{
	size_t				groups = src.size() / (groupsize * 2);
	size_t				pos;
	std::vector<unsigned int>	aux;

	groupsize *= 2;
	if (groups * groupsize + 1 < src.size())
		aux = src;
	else
	{
		for (size_t i = 1; i  <= groups; i++)
		{
			pos = i * groupsize - 1;

			if (src[pos] < src[pos - groupsize / 2])
			{
				insert_group(aux, src, pos - groupsize / 2 + 1, pos);
				insert_group(aux, src, pos - groupsize  + 1, pos - groupsize / 2);
			}
			else
			{
				insert_group(aux, src, pos - groupsize + 1, pos - groupsize / 2);
				insert_group(aux, src, pos - groupsize / 2 + 1, pos);
			}
		}
		insert_group(aux, src, pos + 1, src.size() - 1);
		aux = merge_vectors(aux, groupsize);
	}
	return aux;
}

std::vector<unsigned int>		PmergeMe::vector_merge(std::vector<unsigned int>& src)
{
	std::vector<unsigned int>	main = src;
	size_t				groupsize = 1;

	main = merge_vectors(main, groupsize);
	return main;
}

void	PmergeMe::print_time()
{
	std::cout << "Time to process a range of " << this->amount << " elements with std::vector : " << std::setprecision(5)  << this->vecTime << " us" << std::endl;
	std::cout << "Time to process a range of " << this->amount << " elements with std::list   : " << std::setprecision(5)  << this->lstTime << " us" << std::endl;
}

void	PmergeMe::merge_process()
{
	//struct timeval	start, end;

	/*gettimeofday(&start, NULL);
	this->lst = list_merge(this->lst);
	gettimeofday(&end, NULL);
	this->lstTime = (end.tv_sec - start.tv_sec) * MICROSEC + end.tv_usec - start.tv_usec;

	print_result();*/

	//gettimeofday(&start, NULL);
	this->vec = vector_merge(this->vec);
//	gettimeofday(&end, NULL);
//	this->vecTime = (end.tv_sec - start.tv_sec) * MICROSEC + end.tv_usec - start.tv_usec;
}

PmergeMe::errorException::errorException() : std::logic_error("\terror") {}


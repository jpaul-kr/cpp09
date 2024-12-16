#include "PmergeMe.hpp"

PmergeMe::PmergeMe(char** arg)
{
	int	n;
	int	i;

	int jacobs[15] = {0, 2, 2, 6, 10, 22, 42, 87, 170, 342, 682, 1366, 2730, 5462, 10922};
	for(int j = 0; j < 15; j++)
		this->jacob[j] = jacobs[j];
	for (i = 0; arg[i]; i++)
	{
		n = atoi(arg[i]);
		if (!is_valid(arg[i]) || is_repeat(n, vec))
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

bool		PmergeMe::is_valid(string arg)
{
 	for (size_t i = 0; i < arg.size(); i++)
	{
		if (arg[i] < '0' || arg[i] > '9')
			return false;
	}
	return true;
}

bool		PmergeMe::is_repeat(int n, std::vector<unsigned int> vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		if ((unsigned int)n == vec[i])
			return true;
	}
	return false;
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

void		PmergeMe::print_vec(std::vector<unsigned int> aux, size_t groupsize)
{
	for (size_t i = 0; i < aux.size(); i++)
	{
		if (i % groupsize == 0)
			std::cout << "| ";
		std::cout << aux[i] << " ";
	}
	std::cout << "|";
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

void		PmergeMe::insert_group(std::vector<unsigned int>& main, std::vector<unsigned int> src, size_t init, size_t end, std::vector<unsigned int>::iterator pos)
{
	if (end >= src.size())
		return ;
	std::vector<unsigned int>::iterator	it = src.begin();
	std::vector<unsigned int>::iterator	ite = src.begin();
	std::advance(it, init);
	std::advance(ite, end + 1);
	main.insert(pos, it, ite);
}

void		PmergeMe::compare_and_insert(std::vector<unsigned int>& main, std::vector<unsigned int> src, size_t pos, size_t groupsize)
{
	int					compare = 0;
	int					groupindex;
	int					pair;
	bool					flag = false;
	std::vector<unsigned int>::iterator	it = main.begin();

	if (pos + groupsize >= src.size())
		compare = main.size() - 1;
	else
	{
		while (main[compare] != src[pos + groupsize])
			compare++;
	}
	pair = (compare + 1) / groupsize;
	while (!flag && ((src[pos] < main[compare]) || (compare == (int)(main.size() - 1) || src[pos] > main[compare + groupsize])))
	{
		while (compare != -1 && src[pos] < main[compare])
		{
			groupindex = (compare + 1) / groupsize;
			pair = groupindex;
			compare = (((groupindex - 1) / 2) + 1) * groupsize - 1;
			if (groupindex == 1 && src[pos] < main[compare])
			{
				flag = true;
				compare = -1;
			}
		}
		while (compare != -1 && src[pos] > main[compare])
		{
			if (compare == (int)(main.size() - 1))
			{
				flag = true;
				break ;
			}
			groupindex = (compare + 1) / groupsize;
			compare = (((pair - groupindex) / 2) + groupindex) * groupsize - 1;
			if (groupindex == pair - 1)
			{
				flag = true;
				break ;
			}
			if (src[pos] < main[compare])
			{
				compare -= groupsize;
				break ;
			}
		}
	}
	std::advance(it, compare + 1);
	insert_group(main, src, pos - groupsize + 1, pos, it);
}

std::vector<unsigned int>		PmergeMe::jacob_sort(std::vector<unsigned int> src, size_t groupsize)
{
	std::vector<unsigned int>	main;
	size_t				groups = src.size() / groupsize;
	size_t				prevpos = groupsize - 1;

		//std::cout << "\tgroupsize: " << groupsize << std::endl;
		//	std::cout << "src:  ";
		//	print_vec(src, groupsize);
	for (size_t i = 1; i <= groups; i += 2)
		insert_group(main, src, i * groupsize, i * groupsize + groupsize - 1, main.end());

		//	std::cout << "main: ";
		//	print_vec(main, groupsize);
	insert_group(main, src, 0, groupsize - 1, main.begin());
		//	std::cout << "main: ";
		//	print_vec(main, groupsize);
	for(size_t i = 1; main.size() < src.size(); i++)
	{
		size_t pos = ((jacob[i] + jacob[i - 1]) * 2 + 1) * groupsize - 1;
		if (pos >= src.size())
			pos = (groups % 2 == 0 ? src.size() - groupsize - 1 : src.size() - 1);
		size_t aux = pos;
		while (pos > prevpos)
		{
			compare_and_insert(main, src, pos, groupsize);
			pos -= groupsize * 2;
		//	std::cout << "main: ";
		//	print_vec(main, groupsize);
		}
		prevpos = aux;
	}
	return main;
}

std::vector<unsigned int>		PmergeMe::merge_vectors(std::vector<unsigned int> src, size_t	groupsize)
{
	size_t				groups = src.size() / (groupsize * 2);
	size_t				pos;
	std::vector<unsigned int>	aux;

	if (!groups)
		groups = 1;
	groupsize *= 2;
	//std::cout << "groupsize: " << groupsize << std::endl;
	if (groups * groupsize > src.size())
		return src;
	else
	{
		for (size_t i = 1; i  <= groups; i++)
		{
			pos = i * groupsize - 1;

			if (src[pos] < src[pos - groupsize / 2])
			{
				insert_group(aux, src, pos - groupsize / 2 + 1, pos, aux.end());
				insert_group(aux, src, pos - groupsize  + 1, pos - groupsize / 2, aux.end());
			}
			else
			{
				insert_group(aux, src, pos - groupsize + 1, pos - groupsize / 2, aux.end());
				insert_group(aux, src, pos - groupsize / 2 + 1, pos, aux.end());
			}
		}
	//	std::cout << "aux: ";
	//	print_vec(aux, groupsize);
		aux = merge_vectors(aux, groupsize);	
		aux = jacob_sort(aux, groupsize);
		insert_group(aux, src, pos + 1, pos + groupsize / 2, aux.end());
	}
	if (groupsize == 2)
		aux = jacob_sort(aux, 1);
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


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
	//TODO 
	//en el container de main:
	//encontrar la posicion de la pareja del grupo de pos
	//si no tiene pues se empieza en el final.
	//y pillar la poosicion del grupo y divivr entre 2 comparando con el grupo de en medio o de la derecha hasta que el grupo de nuestro pos sea menor
	//y insertarlo ahi
	while (true)
	{
		insert_group(main, src, pos - groupsize + 1, pos,);
	}
}

std::vector<unsigned int>		PmergeMe::jacob_sort(std::vector<unsigned int> src, size_t groupsize)
{
	std::vector<unsigned int>	main;
	size_t				groups = src.size() / groupsize;
	size_t				prevpos = groupsize - 1;

	for (size_t i = 1; i <= groups; i += 2)
		insert_group(main, src, i * groupsize, i * groupsize + groupsize - 1, main.end());

	insert_group(main, src, 0, groupsize - 1, main.begin());
	for(size_t i = 1; main.size() != src.size(); i++)
	{
		size_t pos = ((jacob[i] + jacob[i - 1]) * 2 + 1) * groupsize - 1;
		size_t aux = pos;
		while (pos > prevpos)
		{
			compare_and_insert(main, src, pos, groupsize);	
		}
		prevpos = aux;
	}
	std::cout << "main: ";
	print_vec(main);
	return main;
}

std::vector<unsigned int>		PmergeMe::merge_vectors(std::vector<unsigned int> src, size_t	groupsize)
{
	size_t				groups = src.size() / (groupsize * 2);
	size_t				pos;
	std::vector<unsigned int>	aux;

	groupsize *= 2;
	if (groups == 1)
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
		//std::cout << "groupsize: " << groupsize << std::endl;
		//std::cout << "aux: ";
		//print_vec(aux);
		aux = merge_vectors(aux, groupsize);	
		//std::cout << pos << std::endl;
		//jacob_sort(aux, groupsize);
		insert_group(aux, src, pos + 1, pos + groupsize / 2, aux.end());
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


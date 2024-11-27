#include "PmergeMe.hpp"

int	main(int argc, char** argv)
{
	try
	{
		if (argc < 2)
			throw PmergeMe::errorException();

		PmergeMe		merge(&argv[1]);

		merge.merge_process();
		merge.print_time();
	}
	catch (PmergeMe::errorException&	e)
	{
		std::cout << e.what() << std::endl;
	}
}
/*		RECURSIVA:
 *	IDA:
 *ordenar por parejas -> groupsize *= 2;
 hasta que solo haya un grupo del tamanyo de groupsize

 	VUELTA:
ordenamos los grupos comparando con el numero mas grande de cada pareja de grupos (lo que seria la pareja b)
luego se utiliza jacobs zahl x2 para anyadir las parejas a en funcion del indice de jacobs = 0 2 2 6 10 ...
primero va la pareja a[0] indice: 0

luego va el siguiente indice de la pareja (0 + 2 = 2): a[2]
y despues va el indice - 1 : a[1]

luego el siguiente que es (2 + 2 = 4): a[4]
despues va el indice - 1 (4 - 1 = 3) : a[3]

... asi sucesivamente.*/


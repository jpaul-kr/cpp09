NAME = PmergeMe

CC = c++ -std=c++98
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra -O3 #-g -fsanitize=address

SRC = main.cpp PmergeMe.cpp

OBJ = $(SRC:.cpp=.o)

%.o : %.cpp
	$(CC) $(CFLAGS) -c $<

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean $(NAME)

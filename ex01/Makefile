NAME = RPN

CC = c++ -std=c++98
RM = rm -rf
CFLAGS = -Wall -Werror -Wextra -fsanitize=address

SRC = main.cpp RPN.cpp

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

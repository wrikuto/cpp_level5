SRC		= main.cpp RPN.cpp
OBJ		= ${SRC:.cpp=.o}
NAME	= RPN

CC		= c++
CFLAGS	= -std=c++98 -Wall -Wextra -Werror

RM		= rm -f

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
		$(RM) -r $(OBJ)

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re

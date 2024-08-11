SRC		= main.cpp Bureaucrat.cpp AForm.cpp ShrubberyCreationForm.cpp RobotomyRequestForm.cpp PresidentialPardonForm.cpp Intern.cpp
OBJ		= ${SRC:.cpp=.o}
NAME	= Form

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

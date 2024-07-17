# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wrikuto <wrikuto@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/16 00:22:56 by wrikuto           #+#    #+#              #
#    Updated: 2024/07/16 00:26:34 by wrikuto          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= main.cpp Bureaucrat.cpp
OBJ		= ${SRC:.cpp=.o}
NAME	= Bureaucrat

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

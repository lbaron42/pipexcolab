# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbaron <lbaron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 12:42:30 by lbaron            #+#    #+#              #
#    Updated: 2022/12/04 20:56:54 by lbaron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CFLAGS = -Wall -Wextra -Werror

AR = ar -rc

CC = cc


SRC= pipexutils.c pipex.c

OBJ=$(SRC:.c=.o)


all:$(NAME)

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) -c $?
	$(CC) $(CFLAGS) $? -o $(NAME)


clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

ct: fclean
	rm -f test	
	
test: all 
	$(CC) $(CFLAGS) main.c $(NAME) -o test

re: fclean all

.PHONY: all clean fclean re test ct

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inskim <inskim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 08:02:44 by inskim            #+#    #+#              #
#    Updated: 2023/03/24 19:25:42 by inskim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra 

SRC = main.c
OBJ = $(SRC:.c=.o)
HEADER = minishell.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	cc -o $(NAME) $(OBJ) -lreadline -L/Users/inskim/.brew/opt/readline/lib  -I/Users/inskim/.brew/opt/readline/include
clean:
	rm -f $(OBJ)

fclean:clean
	rm -f $(NAME)

re: fclean
	make all

.phony: all clean fclean re bonus

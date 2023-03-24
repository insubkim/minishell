# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inskim <inskim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 08:02:44 by inskim            #+#    #+#              #
#    Updated: 2023/03/25 08:34:39 by inskim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

EXECUTE_SRC = execute_cmd_list.c path_name.c
PARSE_SRC = 
PRINT_SRC = print_term.c
SIGNAL_SRC = #signal.c
STRING_SRC = ft_split.c ft_strlen.c ft_strncmp.c get_last_str.c
SRC = main.c handle_line.c \
$(addprefix execute/, $(EXECUTE_SRC)) $(addprefix parse/, $(PARSE_SRC)) \
$(addprefix print/, $(PRINT_SRC)) $(addprefix signal/, $(SIGNAL_SRC)) \
$(addprefix string/, $(STRING_SRC))
SR = $(addprefix ./srcs/, $(SRC))
OBJ = $(SR:.c=.o)
HEADER = minishell.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I.

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	cc -o $(NAME) $(OBJ) \
	-lreadline \
	-L/Users/inskim/.brew/opt/readline/lib \
	-I/Users/inskim/.brew/opt/readline/include -I.
clean:
	rm -f $(OBJ)

fclean:clean
	rm -f $(NAME)

re: fclean
	make all

.phony: all clean fclean re bonus

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 08:02:44 by inskim            #+#    #+#              #
#    Updated: 2023/04/01 17:46:12 by inskim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall  -Wextra -Werror -g

EXECUTE_SRC = execute_cmd_list.c path_name.c file_redirection.c 
PARSE_SRC = add_list.c count_word.c init_list.c separate_line.c env_parse.c \
			quote.c
PRINT_SRC = print_term.c
SIGNAL_SRC = signal.c term.c
STRING_SRC = ft_split.c ft_strlen.c ft_strncmp.c get_last_str.c ft_is_space.c \
			 ft_strcmp.c ft_strdup.c ft_putstr_fd.c
SRC = main.c handle_line.c handle_heredoc.c \
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

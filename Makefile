# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 08:02:44 by inskim            #+#    #+#              #
#    Updated: 2023/04/05 04:38:02 by skim2            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall  -Wextra -Werror -g

EXECUTE_SRC = execute_cmd_list.c path_name.c file_redirection.c 
PARSE_SRC = add_list.c count_word.c init_list.c separate_line.c env_parse.c \
			quote.c parse.c separate_line_utils.c add_cmd_list.c \
			quote_utils.c
PRINT_SRC = print_term.c
SIGNAL_SRC = signal.c term.c
STRING_SRC = ft_split.c ft_strlen.c ft_strncmp.c get_last_str.c ft_is_space.c \
			 ft_strcmp.c ft_strdup.c ft_putstr_fd.c ft_itoa.c \
			 ft_is_char_space.c ft_substr.c ft_is_printable.c \
			 heredoc_strjoin.c ft_atoi.c env_strjoin.c
HANDLE_SRC = handle_line.c handle_heredoc.c handle_line_utils.c handle_free.c \
			handle_error.c
ENV_SRC = env.c add_delete_env.c get_env.c set_pwd.c
BUILTIN_SRC = builtin.c echo.c export.c unset.c run_env.c run_pwd.c cd.c
SRC = main.c \
$(addprefix execute/, $(EXECUTE_SRC)) $(addprefix parse/, $(PARSE_SRC)) \
$(addprefix print/, $(PRINT_SRC)) $(addprefix signal/, $(SIGNAL_SRC)) \
$(addprefix string/, $(STRING_SRC)) $(addprefix handle/, $(HANDLE_SRC)) \
$(addprefix env/, $(ENV_SRC)) $(addprefix builtin/, $(BUILTIN_SRC))  
SR = $(addprefix ./srcs/, $(SRC))
OBJ = $(SR:.c=.o)
HEADER = minishell.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I.

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	cc -o $(NAME) $(OBJ) \
    -lreadline \
    -L/Users/skim2/.brew/opt/readline/lib \
    -I/Users/skim2/.brew/opt/readline/include -I.
clean:
	rm -f $(OBJ)

fclean:clean
	rm -f $(NAME)

re: fclean
	make all

.phony: all clean fclean re bonus

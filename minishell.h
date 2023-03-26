/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:53:12 by inskim            #+#    #+#             */
/*   Updated: 2023/03/26 17:41:03 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <fcntl.h>
#include <sys/errno.h>



// forbidden functions
# include <string.h>
//-----------------------------------

typedef struct s_cmd
{
    char    *cmd;
    char    **args;
    char    **file_redirection;
    int     pid;
}    t_cmd;

typedef struct s_list
{
    t_cmd           *data;
    struct s_list   *next;
}   t_list;

void	handle_line(char *line, char **envp);
void    rl_replace_line (const char *text, int clear_undo);
void	execute_cmd_list(t_list *cmd_list, char **envp);
char	**ft_split(char const *s, char c);
int     ft_strlen(char *s);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_pathname(char *command, char **envp);
void	print_term(char *str);
void	print_term_exit(char *str, int exit_code);
char	*get_last_str(char **arr);
int    ft_is_space(char *str);

#endif
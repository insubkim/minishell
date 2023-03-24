/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:53:12 by inskim            #+#    #+#             */
/*   Updated: 2023/03/24 23:06:57 by inskim           ###   ########.fr       */
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
#include <termios.h>
// has to delete, forbidden functions
# include <string.h>
//-----------------------------------

typedef struct s_cmd
{
    char    *cmd;
    char    **args;
    char    **file_in;
    char    **file_in_heredoc;
    char    **file_out;
    char    **file_out_append;
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

#endif
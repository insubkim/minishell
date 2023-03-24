/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:53:12 by inskim            #+#    #+#             */
/*   Updated: 2023/03/24 19:38:27 by inskim           ###   ########.fr       */
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
    char    **file_redirect_in;
    char    **file_redirect_out;
    int     is_heredoc;//Boolean type
    int     is_append_mode;//Boolean type
}   t_cmd;

typedef struct s_list
{
    void            *data;
    struct s_list   *next;
}   t_list;

void	handle_line(char *line, char **envp);
void rl_replace_line (const char *text, int clear_undo);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:53:12 by inskim            #+#    #+#             */
/*   Updated: 2023/03/21 21:41:41 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

// has to delete, forbidden functions
# include <string.h>
//-----------------------------------

typedef struct s_cmd
{
    char    *cmd;
    char    **args;
    int     file_in;
    int     file_out;
    int     is_heredoc;
    int     is_append_mode;
}   t_cmd;

typedef struct s_pid
{
    pid_t   pid;
    struct s_pid    *next;
}   t_pid;

typedef struct s_list
{
    void            *data;
    struct s_list   *next;
}   t_list;

void	handle_line(char *line);

#endif
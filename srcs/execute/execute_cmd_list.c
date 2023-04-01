/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 19:48:54 by inskim            #+#    #+#             */
/*   Updated: 2023/04/01 18:39:59 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_pipe(t_cmd *cmd, int read_end, int std_fd[2])
{
	int		pipe_fd[2];

	if (cmd->next)
	{
		pipe(pipe_fd);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
	}
	else
		dup2(std_fd[1], 1);
	if (read_end != -1)
	{
		dup2(read_end, 0);
		close(read_end);
	}
	return (pipe_fd[0]);
}

void	redirect_file(char **redirection, char *heredoc)
{
	while (redirection && *redirection)
	{
		if ((*redirection)[0] == '<' && (*redirection)[1] == '<')
			redirection_heredoc(heredoc);
		else if ((*redirection)[0] == '<')
			redirection_input(&((*redirection)[1]));
		else if ((*redirection)[0] == '>' && (*redirection)[1] == '>')
			redirection_output_append(&((*redirection)[2]));
		else if ((*redirection)[0] == '>')
			redirection_output(&((*redirection)[1]));	
		redirection++;
	}
}

void    execute_cmd_list(t_list *cmd_list, char **envp, int *std_fd)
{
    char    *path_name;
    int     read_end;
    t_cmd   *cmd;
    std_fd[0] = dup(0);
    std_fd[1] = dup(1);
    read_end = -1;
    cmd = cmd_list->data;
    while (cmd)
    {
        read_end = set_pipe(cmd, read_end, std_fd);
        cmd->pid  = fork();
        if (cmd->pid  == 0)
        {
            redirect_file(cmd->file_redirection, \
            cmd->heredoc);
            path_name = get_pathname(cmd->cmd, envp);
            execve(path_name, cmd->args, envp);
            free(path_name);
            ft_putstr_fd("execve error\n", 2);
            exit(126);
        }
        cmd = cmd->next;
    }
}
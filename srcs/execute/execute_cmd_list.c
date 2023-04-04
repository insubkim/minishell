/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 19:48:54 by inskim            #+#    #+#             */
/*   Updated: 2023/04/04 20:29:09 by inskim           ###   ########.fr       */
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

void	redirect_file(char **redirection, char *heredoc, int status)
{
	while (redirection && *redirection)
	{
		if ((*redirection)[0] == '<' && (*redirection)[1] == '<')
			redirection_heredoc(heredoc);
		else if ((*redirection)[0] == '<')
			redirection_input(&((*redirection)[1]), status);
		else if ((*redirection)[0] == '>' && (*redirection)[1] == '>')
			redirection_output_append(&((*redirection)[2]), status);
		else if ((*redirection)[0] == '>')
			redirection_output(&((*redirection)[1]), status);
		redirection++;
	}
}

void	execute_cmd_list(t_list *cmd_list, char **envp, int *std_fd, int status)
{
	char	*path_name;
	int		read_end;
	t_cmd	*cmd;

	read_end = -1;
	cmd = cmd_list->data;
	while (cmd)
	{
		read_end = set_pipe(cmd, read_end, std_fd);
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			redirect_file(cmd->file_redirection, \
					cmd->heredoc, status);
			if (is_builtin(cmd))
				run_builtin(cmd, &(std_fd[2]), envp);
			path_name = get_pathname(cmd->cmd, envp);
			execve(path_name, cmd->args, envp);
			exit(126);
		}
		cmd = cmd->next;
	}
}

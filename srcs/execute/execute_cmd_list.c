/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 19:48:54 by inskim            #+#    #+#             */
/*   Updated: 2023/03/31 18:38:14 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_pipe(t_list *cmd_list, int read_end, int std_fd[2])
{
	int		pipe_fd[2];

	if (cmd_list->next)
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

void	execute_cmd_list(t_list *cmd_list, char **envp, int *std_fd)
{
	char	*path_name;
	int		read_end;

	std_fd[0] = dup(0);
	std_fd[1] = dup(1);
	read_end = -1;
	while (cmd_list)
	{
		read_end = set_pipe(cmd_list, read_end, std_fd);
		cmd_list->data->pid  = fork();
		if (cmd_list->data->pid  == 0)
		{
			redirect_file(cmd_list->data->file_redirection, \
			cmd_list->data->heredoc);
			path_name = get_pathname(cmd_list->data->cmd, envp);
			execve(path_name, cmd_list->data->args, envp);
			free(path_name);
			ft_putstr_fd("execve error\n", 2);
			exit(126);
		}
		cmd_list = cmd_list->next;
	}
}
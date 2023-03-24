/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 19:48:54 by inskim            #+#    #+#             */
/*   Updated: 2023/03/25 01:45:47 by inskim           ###   ########.fr       */
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
	{
		dup2(std_fd[1], 1);
	}
	if (read_end != -1)
	{
		dup2(read_end, 0);
		close(read_end);
	}
	else
	{
		dup2(std_fd[0], 0);
	}
	return (pipe_fd[0]);
}

void	execute_cmd_list(t_list *cmd_list, char **envp)
{
	int		pid;
	char	*path_name;
	int		std_fd[2];
	int		read_end;

	std_fd[0] = dup(0);
	std_fd[1] = dup(1);
	read_end = 0;
	while (cmd_list)
	{
		//open files
		//만약 파일 open 안되면 해당 명령 실행 x, 그리고 readend 닫고, pipe후, 바로 close(pipe[1]); eof보내야함. 
		//set pipe
		//read_end = set_pipe(cmd_list, read_end, std_fd);
		pid = fork();
		if (pid == 0)
		{
			//execute
			path_name = get_pathname(cmd_list->data->cmd, envp);
			if (!path_name)
				exit(127);
			execve(path_name, cmd_list->data->args, envp);
		}
		cmd_list->data->pid = pid;
		cmd_list = cmd_list->next;
	}
}
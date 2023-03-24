/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_command_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 22:08:10 by inskim            #+#    #+#             */
/*   Updated: 2022/12/27 10:21:21 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	set_pipe(int read_end, int file2_fd, int index, int command_count)
{
	int	pipe_fd[2];

	dup2(read_end, 0);
	if (index != 0)
		close(read_end);
	pipe(pipe_fd);
	if (index == command_count - 1 && file2_fd >= 0)
	{
		dup2(file2_fd, 1);
		close(pipe_fd[0]);
	}
	else
		dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	make_process(int command_count, int file1_fd, int file2_fd)
{
	int		i;
	pid_t	pid;
	int		read_end;

	i = 0;
	read_end = file1_fd;
	while (i < command_count)
	{
		read_end = set_pipe(read_end, file2_fd, i, command_count);
		pid = fork();
		if (!pid)
			break ;
		i++;
	}
	if (pid)
	{
		waitpid(pid, &i, 0);
		exit(0);
	}
	return (i);
}

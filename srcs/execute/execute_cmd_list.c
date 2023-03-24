/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 19:48:54 by inskim            #+#    #+#             */
/*   Updated: 2023/03/25 08:56:23 by inskim           ###   ########.fr       */
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

int	access_files(t_cmd *cmd)
{
	//이상함. out은 파일 없더라고 정상일수 있음.
	while (*(cmd->file_in))
	{
		if (access(*(cmd->file_in), F_OK | R_OK))
			return (0);
		cmd->file_in++;
	}
	while (*(cmd->file_out))
	{
		if (access(*(cmd->file_out), F_OK | R_OK | W_OK))
			return (0);
		if (*(cmd->file_out + 1))
			open(*(cmd->file_out), O_WRONLY | O_TRUNC | O_CREAT, 0644);
		cmd->file_out++;
	}
	while (*(cmd->file_out_append))
	{
		if (access(*(cmd->file_out_append), F_OK | R_OK | W_OK))
			return (0);
		if (*(cmd->file_out_append + 1))
			open(*(cmd->file_out_append), O_WRONLY | O_APPEND | O_CREAT, 0644);
		cmd->file_out_append++;
	}
	return (1);
}

int	redirect_file(t_cmd *cmd, int std_fd[2])
{
	if (!access_files(cmd))
	{
		print_term("file access error");//error code에 따라 다르게 display
		return (0);
	}
	//if (cmd->is_heredoc)
		//gnl until heredoc
	else if (*(cmd->file_in))
		dup2(open(get_last_str(cmd->file_in), O_RDONLY), 0);
	else
		dup2(std_fd[0], 0);
	if (cmd->is_append)
		dup2(open(get_last_str(cmd->file_out_append), O_WRONLY | O_CREAT | O_APPEND, 0644), 1);
	else if (*(cmd->file_out))
		dup2(open(get_last_str(cmd->file_out), O_WRONLY | O_CREAT | O_TRUNC, 0644), 1);
	else
		dup2(std_fd[1], 1);
	return (1);
}

void	execute_cmd_list(t_list *cmd_list, char **envp)
{
	int		pid;
	char	*path_name;
	int		std_fd[2];
	int		read_end;

	std_fd[0] = dup(0);
	std_fd[1] = dup(1);
	read_end = -1;
	while (cmd_list)
	{
		//mode => read files, write files
		//만약 파일 open 안되면 해당 명령 실행 x, 그리고 readend 닫고, pipe후, 바로 close(pipe[1]); eof보내야함. 
		//set pipe
		read_end = set_pipe(cmd_list, read_end, std_fd);
		pid = fork();
		//부모 프로세스 시그널 끄기
		if (pid == 0)
		{
			//redirect file
			if (!redirect_file(cmd_list->data, std_fd))
				exit(1);
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
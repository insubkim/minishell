/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 19:48:54 by inskim            #+#    #+#             */
/*   Updated: 2023/03/24 23:06:19 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		//set pipe
		//read_end = set_pipe(cmd_list, read_end, std_fd);
		//참고 !
		//on redirectiong file descriptor, 
		//if we don't have permission, the command stops and moves to other piped commands
		pid = fork();
		if (pid == 0)
		{
			//execute
			path_name = get_pathname(cmd_list->data->cmd, envp);
			if (!path_name)
				exit(127);
			execve(path_name, cmd_list->data->args, envp);
		}
		//[test] 
		//waitpid(pid,0,0);
		cmd_list->data->pid = pid;
		cmd_list = cmd_list->next;
	}
}
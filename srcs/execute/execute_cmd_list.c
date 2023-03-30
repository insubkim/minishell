/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 19:48:54 by inskim            #+#    #+#             */
/*   Updated: 2023/03/30 21:37:23 by inskim           ###   ########.fr       */
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

void	redirect_file(char **redirection, int std_fd[2])
{
	//access() 함수를 이용해서 파일이 존재, 권한 확인
	//access 실패시 에러 메시지 출력 후 명령 실행 안함. 0,1 파이프 닫기.
	//open() 함수를 필요한 권한 이용해서 파일을 열고 fd를 얻어옴
	//dup2() 함수를 이용해서 fd를 0, 1로 복사
	//안쓰면 close() 함수를 이용해서 fd를 닫아줌
	// while (redirection)
	// {
	// 	if ((*redirection)[0] == '<' && (*redirection)[1] == '<')
	// 		heredoc(&((*redirection)[2]), std_fd);
	// 	else if ((*redirection)[0] == '<')
	// 		redirection_input(&((*redirection)[1]), std_fd);
	// 	else if ((*redirection)[0] == '>' && (*redirection)[1] != '>')
	// 		redirection_output_append(&((*redirection)[2]), std_fd);
	// 	else
	// 		redirection_output(&((*redirection)[1]), std_fd);	
	// 	redirection++;
	// }
	redirection++;
	std_fd++;
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
		read_end = set_pipe(cmd_list, read_end, std_fd);
		pid = fork();
		if (pid == 0)
		{
			redirect_file(cmd_list->data->file_redirection, std_fd);
			path_name = get_pathname(cmd_list->data->cmd, envp);
			//if (!path_name)
				//handle_error();
			execve(path_name, cmd_list->data->args, envp);
			free(path_name);
			print_term("execve error");
			exit(126);
		}
		cmd_list->data->pid = pid;
		cmd_list = cmd_list->next;
	}
}
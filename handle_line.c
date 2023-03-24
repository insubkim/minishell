/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 20:37:44 by insub             #+#    #+#             */
/*   Updated: 2023/03/24 19:37:52 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  참고
        ls ||| ls  같은 경우 에러만 나와야함. 앞의 명령어가 실행되지 않아야함.
        에러 코드 반영 해야함.
*/


            /*
            cmd1 | cmd2 | cmd3 | cmd4 | cmd5

            cmd1

            ls <file1 "<file2 >file3" -a >file4 -l << "DELMITER" >>file5

            command = "ls"
            file redirection in = "file1" "file2"
            file redirection out = "file3" "file4 file5"
            args = "-a" "-l"
            is_heredoc = 1
            */

void	handle_line(char *line, char **envp)
{
    //t_list  *cmd_list;
    int     *pid_list;
    //parse line
    //cmd_list = parse_line(line);
    

    //test case 
    t_cmd   cmd[3];
    t_list  cmd_list[3];

    cmd[0].command = "ls";
    cmd[0].file_in = NULL;
    cmd[0].file_out = NULL;

    //execute command
    pid_list = execute_cmd_list(cmd_list);
    
    //wait child processes
    //wait_child(pid_list);

    //free
    //free_cmd_list(cmd_list);
    //free_pid_list(pid_list);
}


/*

    //test code
    //split line by pipe
    //put cmd in cmd_list
    cmd_list = split_line_by_pipe(line);
*/
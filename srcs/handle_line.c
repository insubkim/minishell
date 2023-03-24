/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 20:37:44 by insub             #+#    #+#             */
/*   Updated: 2023/03/25 01:57:27 by inskim           ###   ########.fr       */
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

void    wait_child(t_list *cmd_list)
{
    t_list  *node;
    int     status;
    int     pid;

    node = cmd_list;
    while (node)
    {
        pid = node->data->pid;
        if (pid)
            waitpid(pid, &status, 0);
        node = node->next;
    }
}

void    free_str_arr(char **str_arr)
{
    int i;

    i = 0;
    while (str_arr[i])
    {
        free(str_arr[i]);
        i++;
    }
    free(str_arr);
}

void    free_cmd_list(t_list *cmd_list)
{
    t_list  *node;
    t_cmd   *cmd;

    node = cmd_list;
    while (node)
    {
        cmd = node->data;
        free(cmd->cmd);
        free_str_arr(cmd->args);
        free_str_arr(cmd->file_in);
        free_str_arr(cmd->file_out);
        free_str_arr(cmd->file_in_heredoc);
        free_str_arr(cmd->file_out_append);
        free(cmd);
        node = node->next;
    }
    free(cmd_list);
}

void	handle_line(char *line, char **envp)
{
    //t_list  *cmd_list;
    //parse line
    //cmd_list = parse_line(line);
    

    //test case 
    line++;
    t_cmd   cmd[3];
    t_list  *cmd_list = malloc(sizeof(t_list) * 3);

    cmd_list[0].data = malloc(sizeof(t_cmd));
    cmd_list[1].data = &cmd[1];
    cmd_list[2].data = &cmd[2];
    cmd_list[0].next = 0;
    cmd_list[1].next = &cmd_list[2];
    cmd_list[2].next = NULL;
    
    cmd_list[0].data->cmd = malloc(3);
    cmd_list[0].data->cmd[0] = 'l';
    cmd_list[0].data->cmd[1] = 's';
    cmd_list[0].data->cmd[2] = 0;
    
    cmd_list[0].data->args = ft_split("ls -a -l", ' ');
    cmd_list[0].data->file_in = ft_split("file1 file2", ' ');
    cmd_list[0].data->file_out = ft_split("file3 file4 file5", ' ');
    cmd_list[0].data->file_in_heredoc = ft_split("heredoc", ' ');
    cmd_list[0].data->file_out_append = ft_split("file_append", ' ');
    cmd_list[0].data->pid = 0;

    execute_cmd_list(cmd_list, envp);
    wait_child(cmd_list);
    free_cmd_list(cmd_list);
}


/*

    //test code
    //split line by pipe
    //put cmd in cmd_list
    cmd_list = split_line_by_pipe(line);
*/
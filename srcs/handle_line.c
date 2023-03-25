/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 20:37:44 by insub             #+#    #+#             */
/*   Updated: 2023/03/25 15:44:22 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  파싱 참고
    ls | ls ||| ls  같은 경우 에러만 나와야함. 앞의 명령어가 실행되지 않아야함.
    에러 코드 반영 해야함.
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
    //선언
    t_list  *cmd_list;
    
    //파싱
    //cmd_list = parse_line(line);
    //SKIM2 화이팅~!(1) ^ ~ ^
    

    //테스트 케이스======================================================= 
    line++;
    cmd_list = malloc(sizeof(t_list) * 3);
    
    cmd_list[0].data = malloc(sizeof(t_cmd));
    cmd_list[1].data = malloc(sizeof(t_cmd));
    cmd_list[2].data = malloc(sizeof(t_cmd));
    cmd_list[0].next = 0;
    cmd_list[1].next = 0;
    cmd_list[2].next = 0;

    cmd_list[0].data->cmd = strdup("ls");
    
    cmd_list[0].data->args = ft_split("ls -a -l", ' ');
    cmd_list[0].data->file_in = ft_split("<file1 <<file2", ' ');
    cmd_list[0].data->file_out = ft_split(">file3 >file4 >>file5", ' ');
    cmd_list[0].data->pid = 0;
    //==================================================================

    //명령 실행
    execute_cmd_list(cmd_list, envp);
    //자식 프로세스 종료 대기
    wait_child(cmd_list);
    //부모 프로세스 시그널 켜기
    //킹갓 SKIM2 화이팅~!(2) > o <
    
    //동적 할당 해제
    free_cmd_list(cmd_list);
}

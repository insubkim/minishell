/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 20:37:44 by insub             #+#    #+#             */
/*   Updated: 2023/03/31 18:36:40 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    wait_child(t_list *cmd_list, int *status)
{
    t_list  *node;
    int     pid;
    int     tmp;

    node = cmd_list;
    while (node)
    {
        pid = node->data->pid;
        if (pid)
            waitpid(-1, &tmp, 0);
        if (FT_WIFEXITED(tmp))
            *status = FT_WEXITSTATUS(tmp);
        else if (FT_WIFSIGNALED(tmp)) 
            *status = FT_WTERMSIG(tmp);
        else
            *status = 124;
        node = node->next;
    }
}

void    free_str_arr(char **str_arr)
{
    int i;

    i = 0;
    while (str_arr && str_arr[i])
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

    while (cmd_list)
    {
        node = cmd_list;
        cmd = node->data;
        free(cmd->cmd);
        free(cmd->heredoc);
        free_str_arr(cmd->args);
        free_str_arr(cmd->file_redirection);
        free(cmd);
        cmd_list = cmd_list->next;
        free(node);
    }
}

void	handle_line(char *line, char **envp, int *status)
{
    t_list  *cmd_list;
    int std_fd[2];
    
    //cmd_list = parse_line(line);
    
    //테스트 케이스======================================================= 
    line++;
    cmd_list = malloc(sizeof(t_list));
    cmd_list->data = malloc(sizeof(t_cmd));
    cmd_list->data->cmd = strdup("cat");
    cmd_list->data->args = ft_split("cat -l", ' ');
    cmd_list->data->file_redirection = ft_split("<<file2", ' ');
    cmd_list->data->pid = 0;
    cmd_list->next = 0;
    cmd_list->data->heredoc=0;
    //==================================================================
    
    handle_heredoc(cmd_list);
    execute_cmd_list(cmd_list, envp, std_fd);
    wait_child(cmd_list, status);
    dup2(std_fd[0], 0);
    dup2(std_fd[1], 1);
    free_cmd_list(cmd_list);
}

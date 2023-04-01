/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 05:08:43 by skim2             #+#    #+#             */
/*   Updated: 2023/04/01 03:10:15 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list  *init_list()
{
    t_list  *list;

    list = malloc(sizeof(t_list));
    if (!list)
        exit (1);
    list->data = NULL;
    return (list);
}

t_parse  *init_parse()
{
    t_parse  *parse;

    parse = malloc(sizeof(t_parse));
    if (!parse)
        exit (1);
    parse->next = NULL;
    parse->redir_count = 0;
    parse->args_count = 0;
    return (parse);
}

void    init_cmd(t_cmd *cmd)
{
    cmd->cmd = NULL;
    cmd->args = NULL;
    cmd->file_redirection = NULL;
    cmd->heredoc = NULL;
    cmd->next = NULL;
    cmd->pid = 0;
}

t_separate_list    *init_cmd_list()
{
    t_separate_list *cmd_list;
    
    cmd_list = malloc(sizeof(t_separate_list));
    if (!cmd_list)
        exit (1);
    cmd_list->data = NULL;
    return (cmd_list);
}

void    init_separate(t_separate_cmd *cmd)
{
    cmd->endline = 0;
    cmd->startline = 0;
    cmd->next = NULL;
    cmd->prev = NULL;
    cmd->str = NULL;
}

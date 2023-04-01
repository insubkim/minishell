/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 05:08:15 by skim2             #+#    #+#             */
/*   Updated: 2023/04/01 10:02:59 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    create_cmd_list(t_separate_list *cmd_list, char *line)
{
    int i;
    int count;
    
    i = 0;
    count = count_word(line);
    if (count > 0)
        add_first_separate(cmd_list);
    while (++i < count)
        add_separate_cmd(cmd_list);
}

void    add_first_cmd(t_list *cmd_list)
{
    t_cmd   *tmp;
    t_cmd   *cmd;

    tmp = (t_cmd *)malloc(sizeof(t_cmd));
    if (!tmp)
        exit (1);
    init_cmd(tmp);
    cmd = tmp;
    cmd_list->data = cmd;
}

void    add_cmd(t_list *cmd_list)
{
    t_cmd   *tmp;
    t_cmd   *cur;

    tmp = (t_cmd *)malloc(sizeof(t_cmd));
    if(!tmp)
        exit (1);
    init_cmd(tmp);
    cur = cmd_list->data;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = tmp;
}

void    add_first_separate(t_separate_list *cmd_list)
{
    t_separate_cmd   *tmp;
    t_separate_cmd   *cmd;

    tmp = (t_separate_cmd *)malloc(sizeof(t_separate_cmd));
    if (!tmp)
        exit (1);
    init_separate(tmp);
    cmd = tmp;
    cmd_list->data = cmd;
}

void    add_parse(t_parse *parse, t_separate_list *list)
{
    t_parse         *tmp;
    t_separate_cmd  *cmd;

    cmd = list->data;
    while (cmd)
    {
        if (cmd->str && cmd->str[0] == '|')
        {
            tmp = init_parse();
            parse->next = tmp;
            parse = parse->next;
        }
        cmd = cmd->next;
    }
}


void    add_separate_cmd(t_separate_list *cmd_list)
{
    t_separate_cmd   *tmp;
    t_separate_cmd   *cur;

    tmp = (t_separate_cmd *)malloc(sizeof(t_separate_cmd));
    if(!tmp)
        exit (1);
    init_separate(tmp);
    cur = cmd_list->data;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = tmp;
    tmp->prev = cur;
}

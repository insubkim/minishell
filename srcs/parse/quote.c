/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:59:24 by skim2             #+#    #+#             */
/*   Updated: 2023/04/01 16:17:57 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    erase_quote(t_list *list)
{
    t_cmd *cur;
    int i;

    cur = list->data;
    while (cur)
    {
        i = -1;
        while (cur->args[++i])
            cur->args[i] = delete_quote(cur->args[i]);
        cur = cur->next;
    }
    cur = list->data;
    int y;

    i = 0;
    y = 0;
    while (cur)
    {
        i = 0;
        while (cur->args && cur->args[i])
        {
            printf("cur[%d] args[%d]: %s\n", y, i, cur->args[i]);
            i++;
        }
        i = 0;
        while (cur->file_redirection && cur->file_redirection[i])
        {
            printf("cur[%d] redir[%d]: %s\n", y, i, cur->file_redirection[i]);
            i++;
        }
        cur = cur->next;
        y++;
    }
}


  // int y;
    // i = 0;
    // y = 0;
    // while (cur)
    // {
    //     i = 0;
    //     while (cur->args && cur->args[i])
    //     {
    //         printf("cur[%d] args[%d]: %s\n", y, i, cur->args[i]);
    //         i++;
    //     }
    //     i = 0;
    //     while (cur->file_redirection && cur->file_redirection[i])
    //     {
    //         printf("cur[%d] redir[%d]: %s\n", y, i, cur->file_redirection[i]);
    //         i++;
    //     }
    //     cur = cur->next;
    //     y++;
    // }

int flag_switch(int flag)
{
    return (!flag);
}

char    *delete_quote(char *s)
{
    int single_flag;
    int double_flag;
    int i;

    single_flag = 0;
    double_flag = 0;
    i = -1;
    while (s[++i])
    {
        if (!double_flag && s[i] == '\'')
        {
            single_flag = flag_switch(single_flag);
            s[i] = 0;
            s = heredoc_strjoin(s, &(s[i-- + 1]));
        }
        if (!single_flag && s[i] == '\"')
        {
            double_flag = flag_switch(single_flag);
            s[i] = 0;
            s = heredoc_strjoin(s, &(s[i-- + 1]));
        }
    }
    return (s);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:51:46 by skim2             #+#    #+#             */
/*   Updated: 2023/04/01 17:13:17 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_char_space(char c)
{
    return (c == 32 || (c >= 9 && c <= 13));
}

int get_env_len(char *str, int start)
{
    int end;
    int len;
    end = start+1;
    len = 0;
    while(str[end])
    {
        if (str[end] == '\'' || str[end] == '\"' || str[end] == '<' \
        || str[end] == '>' || str[end] == '|' || str[end] == ' ' || \
        str[end] == '$' || is_char_space(str[end]))
            break;
        end++;
        len++;
    }
    return (len);
}

char    *ft_substr(char *s, int start, int len)
{
    char            *sub;
    int         str_len;
    int i;
    if (!s)
        return (0);
    str_len = ft_strlen(s);
    if (start > str_len)
        return (0);
    s = s + start;
    i = 0;
    while (s[i] && len-- > 0)
        i++;
    sub = (char *)malloc(sizeof(char) * (i + 1));
    if (!sub)
        exit(120);
    len = i;
    i = 0;
    while (len-- > 0)
    {
        sub[i] = s[i];
        i++;
    }
    sub[i] = 0;
    return (sub);
}

char    *set_env_symbol(char *str, int start, int *del)
{
    int env_len;
    char    *env;
    char    *front;
    char    *back;
    char    *tmp;
    
    env_len = get_env_len(str, start);
    env = ft_substr(str, start + 1, env_len);
    tmp = getenv(env);
    if (!tmp)
        *del = 1;
    free(env);
    env = tmp;
    front = 0;
    if (start > 0)
        front = ft_substr(str, 0, start);
    back = 0;
    if (str[start + env_len + 1])
        back = ft_substr(str, start + env_len + 1, ft_strlen(str));
    front = heredoc_strjoin(front, env);
    if (back)
        front = heredoc_strjoin(front, back);
    free(back);
    free(str);
    return (front);
}

void    check_env_symbol(t_cmd *cmd)
{
    int i;
    int single_flag;
    int double_flag;
    int del;
    int y;
    
    single_flag = 0;
    double_flag = 0;
    i = 0;
    while (cmd->args && cmd->args[i])
    {
        y = 0;
        while (cmd->args[i] && cmd->args[i][y])
        {
            del = 0;
            if ((double_flag || !single_flag) && cmd->args[i][y] == '$')
                cmd->args[i] = set_env_symbol(cmd->args[i], y, &del);
            if (!double_flag && cmd->args[i][y] == '\'' && !del)
                single_flag = flag_switch(single_flag);
            if (!single_flag && cmd->args[i][y] == '\"' && !del)
                double_flag = flag_switch(double_flag);
            if (!del)
                y++;
        }
        i++;
    }
}

void    env_handle(t_list  *list)
{
    int flag;
    t_cmd  *cmd;
    
    flag = 0;
    cmd = list->data;
    while (cmd)
    {
        check_env_symbol(cmd);
        cmd = cmd->next;
    }
}
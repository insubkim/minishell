/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 05:09:41 by skim2             #+#    #+#             */
/*   Updated: 2023/04/01 00:11:01 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int spaces(char **line)
{
    while (**line == ' ' || **line == '\t')
        (*line)++;
    if (!**line)
        (*line)--;
    return (1);
}

int is_token(char *line, int flag)
{
    if (((*(line + 1) == ' ' || *(line + 1) == '<' || *(line + 1) == '>'
        || *(line + 1) == '|' ) && flag == 0)
        || ((*line == '|' && *(line + 1) != '\0') && flag == 0))
        return (1);
    return (0);
}

int count_word(char *line)
{
    int     count;
    int     flag;
    char    startline;

    count = 0;
    flag = 0;
    startline = 0;
    spaces(&line);
    while (*line)
    {
        spaces(&line);
        if ((flag == 0 && *line == '\'') || (flag == 0 && *line == '\"'))
        {
            flag = 1;
            startline = *line;
        }
        else if (flag == 1 && (startline == *line))
            flag = 0;
        while (((*line == '<' && *(line + 1) == '<') || (*line == '>' && *(line + 1) == '>')) && flag == 0)
            line++;
        if (is_token(line, flag))
            count++;
        line++;
    }
    return (++count);
}

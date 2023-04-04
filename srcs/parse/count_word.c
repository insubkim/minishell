/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 05:09:41 by skim2             #+#    #+#             */
/*   Updated: 2023/04/05 03:16:10 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	spaces(char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
	if (!**line)
		(*line)--;
	return (1);
}

int	is_token(char *line, int flag)
{
	if (((*line == '<' && *(line + 1) == '<')
			|| (*line == '>' && *(line + 1) == '>')) && flag == 0)
		return (0);
	if (((*(line + 1) == ' ' || *(line + 1) == '<' || *(line + 1) == '>'
				|| *(line + 1) == '|' ) && flag == 0)
		|| ((*line == '|' && *(line + 1) != '\0') && flag == 0))
		return (1);
	return (0);
}

int	is_count_token(char *line)
{
	return ((*line == '<' && *(line + 1) == '<')
		|| (*line == '>' && *(line + 1) == '>'));
}

int	check_null(char *line, int count)
{
	if (is_char_space(*line))
		return (count);
	return (++count);
}

int	count_word(char *line)
{
	int		count;
	int		flag;
	char	startline;

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
		while (is_count_token(line) && flag)
			line++;
		if (is_token(line, flag))
			count++;
		line++;
	}
	return (check_null(--line, count));
}

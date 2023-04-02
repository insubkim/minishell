/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:13:33 by inskim            #+#    #+#             */
/*   Updated: 2023/04/02 20:51:23 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	separate_spaces(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (!line[i])
		i--;
	return (i);
}

int	separate_is_token(char *line, int i, int flag)
{
	return (((line[i + 1] == ' ' || line[i + 1] == '<'
				|| line[i + 1] == '>' || (line[i + 1] == '|'))
			&& flag == 0) || ((line[i] == '|' && line[i + 1] != '\0')
			&& flag == 0));
}

int	separate_is_token2(char *line, int i, int flag)
{
	return (((line[i] == '<' && line[i + 1] == '<')
			|| (line[i] == '>' && line[i + 1] == '>')) && flag == 0);
}

t_separate_cmd	*save_start_end(t_separate_cmd *cur, char *line, int i)
{
	cur = cur->next;
	cur->startline = separate_spaces(line, i + 1);
	return (cur);
}

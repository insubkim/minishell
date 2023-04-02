/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 19:05:06 by skim2             #+#    #+#             */
/*   Updated: 2023/04/02 20:51:42 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	separate_calculator(t_separate_cmd *cur, char *line, int i, int flag)
{
	char	quote;

	quote = 0;
	while (line[i] != '\0')
	{
		i = separate_spaces(line, i);
		if ((flag == 0 && line[i] == '\'') || (flag == 0 && line[i] == '\"'))
		{
			flag = 1;
			quote = line[i];
		}
		else if (flag == 1 && (quote == line[i]))
			flag = 0;
		while (separate_is_token2(line, i, flag))
			i++;
		if (separate_is_token(line, i, flag))
		{
			cur->endline = i + 1;
			if (cur->next)
				cur = save_start_end(cur, line, i);
		}
		i++;
	}
	if (cur->endline == 0)
		cur->endline = i;
}

void	set_separate(t_separate_list *cmd_list, char *line)
{
	int				i;
	int				flag;
	t_separate_cmd	*cur;

	i = 0;
	flag = 0;
	cur = cmd_list->data;
	i = separate_spaces(line, i);
	cur->startline = i;
	separate_calculator(cur, line, i, flag);
}

void	check_double_pipe(t_separate_cmd *cur, int *status)
{
	if (cur->prev && cur->str[0] == '|' && cur->prev->str[0] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token `||'\n", 2);
		*status = 258;
	}
}

void	check_pipe(t_separate_list *list, int *status)
{
	t_separate_cmd	*cur;

	cur = list->data;
	if (cur->str[0] == '|' && cur->next == NULL && *status != 258)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		*status = 258;
	}
	while (cur->next)
		cur = cur->next;
	if (cur->str[0] == '|' && cur->next == NULL && *status != 258)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		*status = 258;
	}
}

void	separate_line(t_separate_list *list, char *line, int *status)
{
	t_separate_cmd	*cur;
	char			*tmp;
	int				i;

	cur = list->data;
	while (cur)
	{
		i = 0;
		tmp = (char *)malloc(sizeof(char) * (cur->endline - cur->startline));
		if (!tmp)
			exit (1);
		while (cur->startline < cur->endline)
		{
			tmp[i++] = line[cur->startline++];
			tmp[i] = '\0';
		}
		cur->str = tmp;
		check_double_pipe(cur, status);
		cur = cur->next;
	}
	check_pipe(list, status);
}

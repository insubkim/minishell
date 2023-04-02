/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:59:24 by skim2             #+#    #+#             */
/*   Updated: 2023/04/02 18:23:00 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	erase_quote(t_list *list)
{
	t_cmd	*cur;
	int		i;

	cur = list->data;
	while (cur)
	{
		i = -1;
		while (cur->args[++i])
			cur->args[i] = delete_quote(cur->args[i]);
		cur = cur->next;
	}
}

int	flag_switch(int flag)
{
	return (!flag);
}

char	*delete_quote(char *s)
{
	int	single_flag;
	int	double_flag;
	int	i;

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:49:31 by inskim            #+#    #+#             */
/*   Updated: 2023/04/05 03:18:55 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_quote(char *str, int *single_quote, int *double_quote)
{
	if (str && *str == '\'')
		*single_quote = 1;
	else if (str && *str == '\"')
		*double_quote = 1;
}

int	check_quote(char *str)
{
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (str && *str)
	{
		while (str && *str && *str != '\'' && *str != '\"' )
			str++;
		is_quote(str, &single_quote, &double_quote);
		if (str && *str)
			str++;
		while (str && *str && ((single_quote && *str != '\'')
				|| (double_quote && *str != '\"')))
			str++;
		if (str && single_quote && *str == '\'')
			single_quote = 0;
		if (str && double_quote && *str == '\"')
			double_quote = 0;
		if (single_quote || double_quote)
			return (0);
		if (*str)
			str++;
	}
	return (1);
}

int	check_list_quote(t_separate_list *list, int *status)
{
	t_separate_cmd	*node;

	node = list->data;
	while (node)
	{
		if (!check_quote(node->str))
		{
			ft_putstr_fd("minishell: quote error\n", 2);
			*status = 120;
			return (0);
		}
		node = node->next;
	}
	return (1);
}

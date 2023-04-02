/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 05:08:15 by skim2             #+#    #+#             */
/*   Updated: 2023/04/02 18:09:55 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_first_separate(t_separate_list *cmd_list)
{
	t_separate_cmd	*tmp;
	t_separate_cmd	*cmd;

	tmp = (t_separate_cmd *)malloc(sizeof(t_separate_cmd));
	if (!tmp)
		exit (1);
	init_separate(tmp);
	cmd = tmp;
	cmd_list->data = cmd;
}

void	add_parse(t_parse *parse, t_separate_list *list)
{
	t_parse			*tmp;
	t_separate_cmd	*cmd;

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

void	add_separate_cmd(t_separate_list *cmd_list)
{
	t_separate_cmd	*tmp;
	t_separate_cmd	*cur;

	tmp = (t_separate_cmd *)malloc(sizeof(t_separate_cmd));
	if (!tmp)
		exit (1);
	init_separate(tmp);
	cur = cmd_list->data;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = tmp;
	tmp->prev = cur;
}

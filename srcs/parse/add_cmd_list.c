/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:30:05 by inskim            #+#    #+#             */
/*   Updated: 2023/04/02 18:08:36 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_cmd_list(t_separate_list *cmd_list, char *line)
{
	int	i;
	int	count;

	i = 0;
	count = count_word(line);
	if (count > 0)
		add_first_separate(cmd_list);
	while (++i < count)
		add_separate_cmd(cmd_list);
}

void	add_first_cmd(t_list *cmd_list)
{
	t_cmd	*tmp;
	t_cmd	*cmd;

	tmp = (t_cmd *)malloc(sizeof(t_cmd));
	if (!tmp)
		exit (1);
	init_cmd(tmp);
	cmd = tmp;
	cmd_list->data = cmd;
}

void	add_cmd(t_list *cmd_list)
{
	t_cmd	*tmp;
	t_cmd	*cur;

	tmp = (t_cmd *)malloc(sizeof(t_cmd));
	if (!tmp)
		exit (1);
	init_cmd(tmp);
	cur = cmd_list->data;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = tmp;
}

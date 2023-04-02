/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:12:34 by inskim            #+#    #+#             */
/*   Updated: 2023/04/03 05:22:03 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_cmd(t_list *list)
{
	t_cmd	*cur;

	cur = list->data;
	while (cur)
	{
		cur->cmd = ft_strdup(cur->args[0]);
		cur = cur->next;
	}
}

void	ready_separate(t_separate_list *separate_list, char *line, int *status)
{
	create_cmd_list(separate_list, line);
	set_separate(separate_list, line);
	separate_line(separate_list, line, status);
	separate_dup(separate_list);
}

void	reset_handle(int *std_fd, t_parse *parse, \
		t_list *list, t_separate_list *slist)
{
	dup2(std_fd[0], 0);
	close(std_fd[0]);
	close(std_fd[1]);
	free_parse(parse);
	free_cmd_list(list);
	free_separate_list(slist);
}

void	set_parse(t_list *list, t_separate_list *slist, \
		t_parse *parse, int status)
{
	add_parse(parse, slist);
	args_count(slist, parse);
	parsing(list, slist, parse);
	env_handle(list, status);
	erase_quote(list);
}

char	*delete_char(char *line)
{
	write(0, "\b \b", 3);
	line[ft_strlen(line) - 1] = 0;
	if (ft_strlen(line) == 0)
	{
		free(line);
		line = 0;
	}
	return (line);
}

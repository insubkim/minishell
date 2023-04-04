/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 14:12:34 by inskim            #+#    #+#             */
/*   Updated: 2023/04/05 03:20:06 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_cmd(t_list *list, int *std_fd)
{
	t_cmd	*cur;

	cur = list->data;
	std_fd[0] = dup(0);
	std_fd[1] = dup(1);
	pipe(&(std_fd[2]));
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
	dup2(std_fd[1], 1);
	close(std_fd[0]);
	close(std_fd[1]);
	free_parse(parse);
	free_cmd_list(list);
	free_separate_list(slist);
}

void	set_parse(t_list *list, t_separate_list *slist, t_parse *parse)
{
	add_parse(parse, slist);
	args_count(slist, parse);
	parsing(list, slist, parse);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:46:56 by inskim            #+#    #+#             */
/*   Updated: 2023/04/02 18:42:52 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_arr(char **str_arr)
{
	int	i;

	i = 0;
	if (!str_arr)
		return ;
	while (str_arr[i])
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}

void	free_parse(t_parse *parse)
{
	t_parse	*tmp;

	while (parse)
	{
		tmp = parse->next;
		parse->redir_count = 0;
		parse->args_count = 0;
		free(parse);
		parse = tmp;
	}
	free(parse);
}

void	free_separate_list(t_separate_list *separate_list)
{
	t_separate_cmd	*node;
	t_separate_cmd	*cmd;

	node = separate_list->data;
	while (node)
	{
		cmd = node->next;
		node->endline = 0;
		node->startline = 0;
		free(node->str);
		free(node);
		node = cmd;
	}
	free(separate_list);
}

void	free_cmd_list(t_list *cmd_list)
{
	t_cmd	*tmp;
	t_cmd	*cmd;

	cmd = cmd_list->data;
	while (cmd)
	{
		tmp = cmd->next;
		free(cmd->cmd);
		free(cmd->heredoc);
		free_str_arr(cmd->args);
		free_str_arr(cmd->file_redirection);
		free(cmd);
		cmd = tmp;
	}
	free(cmd_list);
}

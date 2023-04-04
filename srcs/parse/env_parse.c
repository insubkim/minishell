/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:51:46 by skim2             #+#    #+#             */
/*   Updated: 2023/04/04 20:55:19 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_len(char *str, int start)
{
	int	end;
	int	len;

	end = start + 1;
	len = 0;
	while (str[end])
	{
		if (str[end] == '\'' || str[end] == '\"' || str[end] == '<' \
				|| str[end] == '>' || str[end] == '|' || str[end] == ' '
			|| str[end] == '$' || is_char_space(str[end]))
			break ;
		end++;
		len++;
	}
	return (len);
}

char	*ft_get_env(char *env, int status)
{
	if (!ft_strcmp(env, "?"))
		return (ft_itoa(status));
	return (getenv(env));
}

char	*set_env_symbol(char *str, int start, int *del, int status)
{
	int		env_len;
	char	*env;
	char	*front;
	char	*back;
	char	*tmp;

	env_len = get_env_len(str, start);
	env = ft_substr(str, start + 1, env_len);
	tmp = ft_get_env(env, status);
	if (!tmp)
		*del = 1;
	free(env);
	env = tmp;
	front = 0;
	if (start > 0)
		front = ft_substr(str, 0, start);
	back = 0;
	if (str[start + env_len + 1])
		back = ft_substr(str, start + env_len + 1, ft_strlen(str));
	front = heredoc_strjoin(front, env);
	if (back)
		front = heredoc_strjoin(front, back);
	free(back);
	free(str);
	return (front);
}

void	check_env_symbol(t_cmd *cmd, int status)
{
	int	i;
	int	single_flag;
	int	double_flag;
	int	del;
	int	y;

	single_flag = 0;
	double_flag = 0;
	i = -1;
	while (cmd->args && cmd->args[++i])
	{
		y = 0;
		while (cmd->args[i] && cmd->args[i][y])
		{
			del = 0;
			if ((double_flag || !single_flag) && cmd->args[i][y] == '$')
				cmd->args[i] = set_env_symbol(cmd->args[i], y, &del, status);
			if (!double_flag && cmd->args[i][y] == '\'' && !del)
				single_flag = flag_switch(single_flag);
			if (!single_flag && cmd->args[i][y] == '\"' && !del)
				double_flag = flag_switch(double_flag);
			if (!del)
				y++;
		}
	}
}


void	env_handle(t_list *list, int status)
{
	t_cmd	*cmd;

	cmd = list->data;
	while (cmd)
	{
		if (ft_strcmp(cmd->args[0], "awk"))
			check_env_symbol(cmd, status);
		cmd = cmd->next;
	}
}

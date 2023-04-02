/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 17:00:17 by inskim            #+#    #+#             */
/*   Updated: 2023/04/03 02:02:01 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_error(char *s)
{
	ft_putstr_fd("minishell: export:", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("not a valid identifier\n", 2);
	exit(1);
}

int	is_valid_export_name(char c)
{
	return (('0' <= c && c <= '9')
		|| ('a' <= c && c <= 'z')
		|| ('A' <= c && c <= 'Z')
		|| (c == '_'));
}

void	export_check_name(t_cmd *cmd)
{
	int	i;
	int	j;
	
	i = 1;
	while (cmd->args[i])
	{
		if ('0' <= cmd->args[i][0] && cmd->args[i][0] <= '9')
			export_error(cmd->args[i]);
		j = 0;
		while (cmd->args[i][0] && cmd->args[i][++j])
		{
			if (is_valid_export_name(cmd->args[i][j]))
				continue ;
			else if (cmd->args[i][j] == '=')
				break ;
			export_error(cmd->args[i]);	
		}
		if (cmd->args[i][j] != '=')
			export_error(cmd->args[i]);
		i++;
	}
}

void	export_check_val(t_cmd *cmd)
{
	int	i;
	int	j;
	
	i = 1;
	while (cmd->args[i])
	{
		j = 0;
		while (cmd->args[i][0] && cmd->args[i][++j])
		{
			if (cmd->args[i][j] == '=')
				return ;
		}
		i++;
	}
	exit(0);
}

void	ft_export(t_cmd *cmd, int *pipe)
{
	int	i;
	char	c;

	//if null print 
	export_check_name(cmd);
	export_check_val(cmd);
	write(pipe[1], "M", 1);
	i = 1;
	c = 1;
	while (cmd->args[i])
	{
		write(pipe[1], cmd->args[i], ft_strlen(cmd->args[i]));
		write(pipe[1], &c, 1);
		i++;
	}
	exit(0);
}
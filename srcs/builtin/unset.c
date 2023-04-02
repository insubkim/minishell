/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 18:09:38 by inskim            #+#    #+#             */
/*   Updated: 2023/04/03 02:02:10 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_error(char *s)
{
	ft_putstr_fd("minishell: unset:", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("not a valid identifier\n", 2);
	exit(1);
}

void	unset_check_name(t_cmd *cmd)
{
	int	i;
	int	j;
	
	i = 1;
	while (cmd->args[i])
	{
		if ('0' <= cmd->args[i][0] && cmd->args[i][0] <= '9')
			unset_error(cmd->args[i]);
		j = 0;
		while (cmd->args[i][0] && cmd->args[i][++j])
		{
			if (is_valid_export_name(cmd->args[i][j]))
				continue ;
			unset_error(cmd->args[i]);
		}
		i++;
	}
}

void	unset(t_cmd *cmd, int *pipe)
{
	int	i;
	char	c;

	unset_check_name(cmd);
	write(pipe[1], "D", 1);
	i = 1;
	c = 1;
	while (cmd->args[i])
	{
		write(pipe[1], cmd->args[i], ft_strlen(cmd->args[i]));
		write(pipe[1], "=", 1);
		write(pipe[1], &c, 1);
		i++;
	}
	exit(0);
}
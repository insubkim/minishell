/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 22:24:39 by inskim            #+#    #+#             */
/*   Updated: 2023/04/03 05:50:18 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_error(int	cd_error, char *arg)
{
	if (cd_error == 0)
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	else if (cd_error == 1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(" No such file or directory", 2);
	}
	else if (cd_error == 2) 
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(" Permission denied", 2);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(" Not a directory", 2);
	}
	exit(1);
}

void	get_dest(char *dest)
{
	//is absolute

	//is relative
	
	dest++;


	//1.check file
	//2.check is dir
	//3.check permission
}

void	cd(t_cmd *cmd, int *pipe, char **envp)
{
	char	*home;
	char	*dest;

	home = get_pwd(envp);
	if (!home && !cmd->args[1])
		cd_error(0, "");
	dest = 0;
	if (!cmd->args[1])
		dest = home;
	else
		dest = get_dest(cmd->args[1]);
	write(pipe[1], "C", 1);
	write(pipe[1], dest, ft_strlen(dest));
	exit(0);
}

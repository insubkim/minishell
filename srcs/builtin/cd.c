/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 22:24:39 by inskim            #+#    #+#             */
/*   Updated: 2023/04/05 05:53:01 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_error(int cd_error)
{
	if (cd_error == 0)
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	else if (cd_error == 1)
		ft_putstr_fd("minishell: cd: OLDHOME not set\n", 2);
	exit(1);
}

void	cd(t_cmd *cmd, int *pipe, char **envp)
{
	char	*home;
	char	*old_home;
	char	*dest;

	home = get_pwd(envp);
	dest = cmd->args[1];
	if (!cmd->args[1])
		dest = &(home[4]);
	if (!home && !cmd->args[1])
		cd_error(0);
	old_home = get_old_pwd(envp);
	if (!ft_strncmp(cmd->args[1], "-", 1) && !old_home)
		cd_error(1);
	if (!ft_strncmp(cmd->args[1], "-", 1))
		dest = &(old_home[7]);
	write(pipe[1], "C", 1);
	write(pipe[1], dest, ft_strlen(dest));
	exit(0);
}

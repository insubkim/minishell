/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 23:45:48 by skim2             #+#    #+#             */
/*   Updated: 2023/04/05 06:15:47 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_pwd(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!strncmp(envp[i], "PWD=", 4))
			break ;
		i++;
	}
	printf("%s\n", envp[i] + 4);
	exit(0);
}

char	*get_pwd(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!strncmp(envp[i], "PWD=", 4))
			return (envp[i]);
		i++;
	}
	return (0);
}

char	*get_old_pwd(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!strncmp(envp[i], "OLDPWD=", 7))
			return (envp[i]);
		i++;
	}
	return (0);
}

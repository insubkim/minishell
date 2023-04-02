/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 23:45:48 by skim2             #+#    #+#             */
/*   Updated: 2023/04/03 03:46:12 by inskim           ###   ########.fr       */
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
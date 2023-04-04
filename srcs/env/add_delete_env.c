/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_delete_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:26:00 by skim2             #+#    #+#             */
/*   Updated: 2023/04/05 06:23:31 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_env(int fd, char ***envp)
{
	char	*name;
	char	*line;
	int		i;

	line = get_line(fd);
	while (line)
	{
		name = get_name(line);
		i = 0;
		while ((*envp)[i])
		{
			if (!strncmp((*envp)[i], name, ft_strlen(name))
				&& ((*envp)[i])[ft_strlen(name)] == '=')
				break ;
			i++;
		}
		if ((*envp)[i])
			*envp = reset_envp(*envp, i);
		free(name);
		line = set_line(line);
	}
}

void	add_env(int fd, char ***envp)
{
	char	*name;
	char	*line;
	char	*var;

	line = get_line(fd);
	while (line)
	{
		name = get_name(line);
		var = get_var(line);
		if (check_name(*envp, name))
			substitute_envp(*envp, name, var);
		else
			change_envp(envp, name, var);
		line = set_line(line);
	}
}

void	change_dir(int fd, char ***envp, int *status)
{
	char	*line;

	line = get_line(fd);
	if (chdir(line) == -1)
	{
		ft_putstr_fd("minishell : ", 2);
		perror(line);
		free(line);
		*status = 1;
		return ;
	}
	set_old_pwd(envp);
	set_pwd(envp);
	*status = 0;
	free(line);
}

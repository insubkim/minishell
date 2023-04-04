/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 18:37:26 by inskim            #+#    #+#             */
/*   Updated: 2023/04/05 04:37:06 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_name(char **envp, char *name)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!strncmp(envp[i], name, ft_strlen(name))
			&& envp[i][ft_strlen(name)] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	substitute_envp(char **envp, char *name, char *var)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!strncmp(envp[i], name, ft_strlen(name))
			&& envp[i][ft_strlen(name)] == '=')
		{
			free(envp[i]);
			envp[i] = heredoc_strjoin(name, "=");
			envp[i] = heredoc_strjoin(envp[i], var);
			free(var);
			return ;
		}
		i++;
	}
	exit(1);
}

char	*set_line(char *line)
{
	char	*tmp;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 1)
			break ;
		i++;
	}
	if (!line[i])
		exit(1);
	if (line[i + 1] == NULL)
	{
		free(line);
		return (0);
	}
	tmp = ft_strdup(line + i + 1);
	free(line);
	return (tmp);
}

void	change_envp(char ***p_envp, char *name, char *var)
{
	int		cnt;
	char	**envp;
	char	**new_envp;

	cnt = 0;
	envp = *p_envp;
	while (envp[cnt])
		cnt++;
	new_envp = (char **)malloc(sizeof(char *) * (cnt + 2));
	if (!new_envp)
		exit(1);
	new_envp[cnt + 1] = 0;
	new_envp[cnt] = heredoc_strjoin(name, "=");
	new_envp[cnt] = heredoc_strjoin(new_envp[cnt], var);
	free(var);
	cnt = 0;
	while (*envp)
		new_envp[cnt++] = ft_strdup(*envp++);
	free_str_arr(*p_envp);
	*p_envp = new_envp;
}

char	**reset_envp(char **envp, int i)
{
	char	**rtn;
	int		cnt;
	int		j;

	cnt = 0;
	while (envp[cnt++])
		;
	rtn = (char **)malloc(sizeof(char *) * (cnt));
	cnt = 0;
	j = 0;
	while (envp[cnt])
	{
		if (cnt != i)
			rtn[j] = ft_strdup(envp[cnt]);
		else
			j--;
		cnt++;
		j++;
	}
	rtn[j] = 0;
	free_str_arr(envp);
	return (rtn);
}

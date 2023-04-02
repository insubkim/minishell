/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 18:37:26 by inskim            #+#    #+#             */
/*   Updated: 2023/04/03 05:07:47 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_line(int fd)
{
	char	*tmp;
	char	*line;
	int		read_byte;

	tmp = (char *)malloc(sizeof(char) * 101);
	if (!tmp)
		exit(1);
	read_byte = 1;
	line = 0;
	while (read_byte)
	{
		read_byte = read(fd, tmp, 100);
		tmp[read_byte] = 0;
		line = heredoc_strjoin(line, tmp);
	}
	free(tmp);
	return (line);
}

char	*get_name(char *line)
{
	int	i;
	char	*name;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
		{
			line[i] = 0;
			name = ft_strdup(line);
			line[i] = '=';
			return (name);
		}
		i++;
	}
	exit(1);
}

char	*get_var(char *line)
{
	int	i;
	char	*var;

	while (*line && *line != '=')
		line++;
	line++;
	i = 0;
	if (!line[i])
		return (ft_strdup(""));
	while (line[i])
	{
		if (line[i] == 1)
		{
			line[i] = 0;
			var = ft_strdup(line);
			line[i] = 1;
			return (var);
		}
		i++;
	}
	exit(1);
}

int	check_name(char **envp, char *name)
{
	int	i;
	i = 0;
	while (envp[i])
	{
		if (!strncmp(envp[i], name, ft_strlen(name)))
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
		if (!strncmp(envp[i], name, ft_strlen(name)))
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

char    *set_line(char *line)
{
    char    *tmp;
    int     i;
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
	int	cnt;
	char	**envp;
	char	**new_envp;

	cnt = 0;
	envp = *p_envp;
	while (envp[cnt])
		cnt++;
	new_envp = (char**)malloc(sizeof(char *) * (cnt + 2));
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

void    delete_env(int fd, char **envp)
{
    char    *line;
    char    *name;
    int     envp_len;
    int     i;
	
    line = get_line(fd);
    name = get_name(line);
    envp_len = 0;
    while (envp[envp_len])
        envp_len++;
    envp_len--;
    i = 0;
    while (envp[i])
    {
        if (!strncmp(envp[i], name, ft_strlen(name)))
            break ;
        i++;
    }
    if (!envp[i])
        return ;
    free(envp[i]);
    envp[i] = envp[envp_len];
    envp[envp_len] = NULL;
	free(line);
	free(name);
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


void	change_dir(int fd, char **envp)
{
	char	*line;

	line = get_line(fd);
	chdir(line);
	substitute_envp(envp, ft_strdup("PWD"), line);
}
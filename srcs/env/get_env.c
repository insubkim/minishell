/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 03:24:54 by skim2             #+#    #+#             */
/*   Updated: 2023/04/05 05:49:03 by skim2            ###   ########.fr       */
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
	int		i;
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
	int		i;
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

int	get_status(int fd)
{
	char	*line;
	char	*tmp;
	int		size;
	int		byte;

	size = 100;
	tmp = (char *)malloc(sizeof(char) * size);
	line = 0;
	if (!tmp)
		exit(1);
	while (1)
	{
		byte = read(fd, tmp, size - 1);
		tmp[byte] = 0;
		line = heredoc_strjoin(line, tmp);
		if (byte < size - 1)
			break ;
	}
	free(tmp);
	size = ft_atoi(line);
	free(line);
	return (size);
}

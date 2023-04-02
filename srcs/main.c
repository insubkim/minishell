/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:53:16 by inskim            #+#    #+#             */
/*   Updated: 2023/04/03 01:51:36 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(struct termios *term, int *status, char ***envp)
{
	char	*line;

	line = "Black Hole plz...";	
	while (line)
	{
		line = readline("minishell> ");
		heredoc_sigint = 0;
		if (line)
		{
			if (ft_strlen(line) > 0)
			{
				add_history(line);
				if (!ft_is_space(line))
					handle_line(line, envp, status, term);
			}
			free(line);
			reset_input_mode(term);
		}
	}
}

char **create_envp(char **envp)
{
	char **temp;
	int	i;
	int	j;

	i = 0;
	while (envp[i])
		i++;
	temp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!temp)
		exit(1);
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
			j++;
		temp[i] = (char *)malloc(sizeof(char) * (j + 1));
		if (!temp[i])
			exit(1);
		i++;
	}
	return (temp);
}

char **dup_envp(char **envp)
{
	char **temp;
	int	i;
	int	j;
	
	temp = create_envp(envp);
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			temp[i][j] = envp[i][j];
			j++;
		}
		temp[i][j] = '\0';
		i++;
	}
	temp[i] = 0;
	return (temp);
}

int	main(int argc, char **argv, char **envp)
{
	int				status;
	struct termios	term[2];

	set_signal();
	save_input_mode(term);
	envp = dup_envp(envp);
	status = 0;
	prompt(term, &status, &envp);
	argv++;
	return (!argc);
}
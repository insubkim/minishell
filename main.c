/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:53:16 by inskim            #+#    #+#             */
/*   Updated: 2023/03/24 19:34:27 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	//make bulletin commands
	char	*line;
	
	//register signal handler
	envp++;
	envp--;
	argc++;
	argc--;
	argv++;
	argv--;
	while (1)
	{
		line = readline("minishell> ");
		printf("hello minishell\n");
		if (line)
		{
			if (strcmp(line, ""))
				add_history(line);
			handle_line(line, envp);
			free(line);
		}
	}
	return (0);
}

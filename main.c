/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:53:16 by inskim            #+#    #+#             */
/*   Updated: 2023/03/23 20:25:24 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void rl_replace_line (const char *text, int clear_undo);

void	sig_int_handler(int sig)
{
	sig++;
	rl_replace_line("\nminishell> ", 1);
	rl_on_new_line();
	rl_redisplay();
}

int main(int argc, char **argv, char **envp)
{
	//make bulletin commands
	char	*line;
	
	//register signal handler
	signal(SIGINT, sig_int_handler);
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
			//handle_line(line);
			free(line);
		}
	}
	return (0);
}

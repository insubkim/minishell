/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:53:16 by inskim            #+#    #+#             */
/*   Updated: 2023/03/24 21:51:19 by inskim           ###   ########.fr       */
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
		if (line)
		{
			if (strcmp(line, ""))
			//스페이스도 히스토리에 저장해야함.
			{
				add_history(line);
				//1개 이상의 스페이스는 핸들라인 해야하나??
				//> , < 과 같은 리다이렉션만 있는 경우 핸들라인 해야할까?
				//<< 히어독은 해야할듯..
				handle_line(line, envp);
			}
			free(line);
		}
	}
	return (0);
}

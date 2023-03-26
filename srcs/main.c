/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:53:16 by inskim            #+#    #+#             */
/*   Updated: 2023/03/26 17:23:48 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	구현할 기능

	1. 파싱
	2. 시그널
	3. bulletin 명령어
	4. 명령 실행부 
	5. 출력부 (readline 고려했을 때)
*/

int main(int argc, char **argv, char **envp)
{
	char	*line;

	//시느널 핸들러 등록
	//SKIM2 화이팅~!(0)

	while (1)
	{
		line = readline("minishell> ");
		if (line)
		{
			if (ft_strlen(line) > 0)
			{
				add_history(line);
				if (!ft_is_space(line))
					handle_line(line, envp);
			}
			free(line);
		}
	}
	argc++;
	argv++;
	return (0);
}

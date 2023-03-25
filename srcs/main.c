/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:53:16 by inskim            #+#    #+#             */
/*   Updated: 2023/03/25 15:44:14 by inskim           ###   ########.fr       */
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
			if (strcmp(line, ""))
			//line이 '\0'이 아닌 경우에만 history에 추가
			//line이 '   ' 이런식으로 공백만 있는 경우에도 추가
			{
				add_history(line);
				//1개 이상의 ' '가 들어가 있는 경우 handle_line에서 처리해야할까?
				handle_line(line, envp);
			}
			free(line);
		}
	}
	argc++;
	argv++;
	return (0);
}

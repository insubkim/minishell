/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:44:17 by inskim            #+#    #+#             */
/*   Updated: 2023/03/31 18:05:28 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_printable(char c)
{
	if (9 <= c && c <= 13)
		return (1);
	else if (32 <= c && c <= 126)
		return (1);
	return (0);
}

char	*delete_char(char *line)
{
	write(0, "\b \b", 3);
	line[ft_strlen(line) - 1] = 0;
	if (ft_strlen(line) == 0)
	{
		free(line);
		line = 0;
	}
	return (line);
}
char	*heredoc_strjoin(char *s1, char *s2)
{
	int		len;
	char	*p;
	int		i;

	if (!s1)
		len = ft_strlen(s2);
	else 
		len = ft_strlen(s1) + ft_strlen(s2);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		exit(127);
	i = 0;
	while (s1 && s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (*s2)
		p[i++] = *s2++;
	p[i] = 0;
	free(s1);
	return (p);
}

char	*append_line(char *line, t_cmd *cmd)
{
	line = heredoc_strjoin(line, "\n");	
	cmd->heredoc = heredoc_strjoin(cmd->heredoc, line);
	free(line);
	line = 0;
	write(0, "> ", 2);
	return (0);
}

char	*append_char(char *line, char *c)
{
	return (heredoc_strjoin(line, c));
}


void	set_heredoc(t_cmd *cmd, char *delimiter)
{
	char	*line;
	char	c[2];

	line = 0;
	c[1] = 0;
	write(0, "> ", 2);
	while (1)
	{
		read(0, c, 1);
		if(is_printable(*c))
			write(0, c, 1);
		if (*c == 4 && !line)
			break ;
		else if (*c == 127 && line && ft_strlen(line) > 0)
			line = delete_char(line);
		else if (*c == '\n' && line && !ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		else if(*c == '\n')
			line = append_line(line, cmd);
		else if(is_printable(*c))  
			line = append_char(line, c);		
	}
}

void	handle_heredoc(t_list *cmd_list)
{
	char **redirection;
	
	while (cmd_list)
	{
		redirection = cmd_list->data->file_redirection;
		while (redirection && *redirection)
		{
			if ((*redirection)[0] == '<' && (*redirection)[1] == '<')
			{
				set_input_mode(term + 1);
				free(cmd_list->data->heredoc);
				cmd_list->data->heredoc = 0;
				set_heredoc(cmd_list->data, &((*redirection)[2]));
				reset_input_mode(term);
			}
			redirection++;
		}
		cmd_list = cmd_list -> next;
	}	
}


///예외케이스
//cat <f
//>ctrl + d
/*

void	set_heredoc(t_cmd *cmd, char *delimiter)
{
	//cmd -> heredoc 에 line을 append 해야함.
	//ctrl + d 나 delimeter 나오면 종료.
	//backspace 나오면 line에서 하나식 지워햐함.
	char	*line;
	char	c[2];

	line = 0;
	c[1] = 0;
	write(0, ">", 1);
	while (1)
	{
		read(0, c, 1);
		if(is_printable(*c))
			write(0, c, 1);
		//ctrl + d 이고 line 길이 0일 경우 break;
		if (*c == 4 && !line)
			break ;
		//backspace 이고 line 길이 1보다 클경우 한글자 지우기.
		//줄이고 난 뒤 line 길이 0이면 free 후 line = 0;
		else if (*c == 127 && line && ft_strlen(line) > 0)
			line = delete_char(line);
		//출력 가능한 문자일경우 
		//1. 개행이고 line이 delimeter인 경우
		//	1)line 할당 해제하고 line = 0; break;
		else if (*c == '\n' && line && !ft_strcmp(line, delimiter))
		{
			line = 0;
			break ;
		}
		//2. 개형이고 line이 delimeter 아닌 경우
		//	1)cmd->heredoc에 line 과 개행 붙임.
		//	2)line 할당 해제. line = 0;
		//	3)write(0, ">", 1);
		else if(*c == '\n')
			line = append_line(line, cmd);
		//3. 개행  아닌 경우.
		//	1)line에 c 붙이기.
		else if(is_printable(*c))  
			line = append_char(line, c);		
	}
}

*/




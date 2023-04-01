/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:44:17 by inskim            #+#    #+#             */
/*   Updated: 2023/04/01 19:01:32 by inskim           ###   ########.fr       */
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
	while (s2 && *s2)
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


void	read_heredoc(t_cmd *cmd, char *delimiter)
{
	char	*line;
	char	c[2];

	line = 0;
	c[1] = 0;
	write(0, "> ", 2);
    cmd->heredoc = 0;
	while (read(0, c, 1) != -1)
	{
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

void	heredoc_signal_handler(int sig)
{
	if (SIGINT == sig)
	{
		close(0);
		heredoc_sigint = 1;
	}
}

void	heredoc_set_signal(void)
{
	signal(SIGINT, heredoc_signal_handler);
	signal(SIGQUIT, heredoc_signal_handler);
}

void	set_heredoc(t_cmd *cmd, char *delimiter_arg)
{
	char	*delimeter;

	delimeter = get_file_name(delimiter_arg);
	read_heredoc(cmd, delimeter);
	free(delimeter);
}

int handle_heredoc(t_list *cmd_list, struct termios *term)
{
    char **redirection;
    t_cmd   *cmd;
	
    cmd = cmd_list->data;
    while (cmd)
    {
        redirection = cmd->file_redirection;
        while (redirection && *redirection)
        {
            if ((*redirection)[0] == '<' && (*redirection)[1] == '<')
            {
                heredoc_set_signal();
                set_input_mode(term + 1);
                free(cmd->heredoc);
                set_heredoc(cmd, &((*redirection)[2]));
                reset_input_mode(term);
                set_signal();
                if (heredoc_sigint)
                    return (0);
            }
            redirection++;
        }
        cmd = cmd->next;
    }
    return (1);
}
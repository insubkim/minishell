/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:44:17 by inskim            #+#    #+#             */
/*   Updated: 2023/04/05 04:17:08 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (is_printable(*c))
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
		else if (*c == '\n')
			line = append_line(line, cmd);
		else if (is_printable(*c))
			line = append_char(line, c);
	}
}

void	set_heredoc(t_cmd *cmd, char *delimiter_arg, char **envp)
{
	char	*delimeter;

	delimeter = get_file_name(delimiter_arg, -1, envp);
	read_heredoc(cmd, delimeter);
	free(delimeter);
}

int	handle_heredoc(t_list *cmd_list, struct termios *term, char **envp)
{
	char	**redirection;
	t_cmd	*cmd;

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
				set_heredoc(cmd, &((*redirection)[2]), envp);
				reset_input_mode(term);
				set_signal();
				if (g_heredoc_sigint)
					return (0);
			}
			redirection++;
		}
		cmd = cmd->next;
	}
	return (1);
}

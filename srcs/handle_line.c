/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 20:37:44 by insub             #+#    #+#             */
/*   Updated: 2023/04/01 19:27:23 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	check_quote(char *str)
{
	int	single_quote;
	int	double_quote;
	
	single_quote = 0;
	double_quote = 0;
	while (*str)
	{
		while (*str && *str != '\'' && *str != '\"' )
			str++;
		if (*str == '\'')
			single_quote = 1;
		else if (*str == '\"')
			double_quote = 1;
		if (*str)
			str++;
		while (*str && ((single_quote && *str != '\'') || (double_quote && *str != '\"')))
			str++;
		if (single_quote && *str == '\'')
			single_quote = 0;
		if (double_quote && *str == '\"')
			double_quote = 0;
		if (single_quote || double_quote)
			return (0);
		str++;
	}
	return (1);
}

int	check_list_quote(t_separate_list *list, int *status)
{
	t_separate_cmd	*node;

	node = list->data;
    *status = 0;
	while (node)
	{
		if (!check_quote(node->str))
		{
			ft_putstr_fd("minishell: quote error\n", 2);
			*status = 120;
			return (0);
		}
		node = node->next;
	}
	return 1;
}

void    wait_child(t_list *cmd_list, int *status)
{
    t_cmd  *node;
    int     pid;
    int     tmp;
    node = cmd_list->data;
    while (node)
    {
        pid = node->pid;
        if (pid)
            waitpid(-1, &tmp, 0);
        if (FT_WIFEXITED(tmp))
            *status = FT_WEXITSTATUS(tmp);
        else if (FT_WIFSIGNALED(tmp))
            *status = FT_WTERMSIG(tmp);
        else
            *status = 124;
        node = node->next;
    }
}

void    free_str_arr(char **str_arr)
{
    int i;

    i = 0;
    if (!str_arr)
        return ;
    while (str_arr[i])
    {
        free(str_arr[i]);
        i++;
    }
    free(str_arr);
}

void    free_parse(t_parse *parse)
{
    t_parse   *tmp;

    while (parse)
    {
        tmp = parse->next;
        parse->redir_count = 0;
        parse->args_count = 0;
        free(parse);
        parse = tmp;
    }
    free(parse);
}

void    free_separate_list(t_separate_list *separate_list)
{
    t_separate_cmd   *node;
    t_separate_cmd   *cmd;

    node = separate_list->data;
    while (node)
    {
        cmd = node->next;
        node->endline = 0; 
        node->startline = 0;
        free(node->str);
        free(node);
        node = cmd;
    }
    free(separate_list);
}

void    free_cmd_list(t_list *cmd_list)
{
    t_cmd  *tmp;
    t_cmd   *cmd;
    cmd = cmd_list -> data;
    while (cmd)
    {
        tmp = cmd->next;
        free(cmd->cmd);
        free(cmd->heredoc);
        free_str_arr(cmd->args);
        free_str_arr(cmd->file_redirection);
        free(cmd);
        cmd = tmp;
    }
    free(cmd_list);
}

void    separate_dup(t_separate_list *list)
{
    t_separate_cmd *cmd;
    t_separate_cmd *tmp;

    cmd = list->data;
    while (cmd)
    {
        if ((ft_strlen(cmd->str) == 1 && (cmd->str[0] == '<' || cmd->str[0] == '>'))
            || (ft_strlen(cmd->str) == 2 && ((cmd->str[0] == '<' && cmd->str[1] == '<')
            || (cmd->str[0] == '>' && cmd->str[1] == '>'))))
        {
            if (cmd->next->str[0] != '|' && cmd->next->str[0] != '<' && cmd->next->str[0] != '>')
            {
                tmp = cmd->next->next;
                cmd->str = heredoc_strjoin(cmd->str, cmd->next->str);
                cmd->next->endline = 0;
                cmd->next->startline = 0;
                free(cmd->next->str);
                free(cmd->next);
                cmd->next = tmp;
            }
        }
        cmd = cmd->next;
    }
    cmd = list->data;
    while (cmd)
    {
        printf("dup str : %s\n", cmd->str);
        cmd = cmd->next;
    }
}

void    set_cmd(t_list *list)
{
    t_cmd *cur;
    
    cur = list->data;
    while (cur)
    {
        cur->cmd = ft_strdup(cur->args[0]);
        cur = cur->next;
    }
}


void	handle_line(char *line, char **envp, int *status, struct termios *term)
{




    t_list  *cmd_list;
    t_separate_list *separate_list;
    t_parse *parse;
    int std_fd[2];


    separate_list = init_cmd_list();
    cmd_list = init_list();
    parse = init_parse();
    create_cmd_list(separate_list, line);
    set_separate(separate_list, line);
    separate_line(separate_list, line, status);
    separate_dup(separate_list);
    if (check_list_quote(separate_list, status))
    {  
        add_parse(parse, separate_list);
        args_count(separate_list, parse);
        parsing(cmd_list, separate_list, parse);
        env_handle(cmd_list);
        erase_quote(cmd_list);
    }
    set_cmd(cmd_list);
    std_fd[0] = dup(0);
    if (handle_heredoc(cmd_list, term) && !*status)
    {    
        execute_cmd_list(cmd_list, envp, std_fd);
        wait_child(cmd_list, status);
        dup2(std_fd[1], 1);
    }
    dup2(std_fd[0], 0);
    close(std_fd[0]);
    close(std_fd[1]);
    free_parse(parse);
    free_cmd_list(cmd_list);
    free_separate_list(separate_list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:29:35 by inskim            #+#    #+#             */
/*   Updated: 2023/04/01 18:53:12 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirection_error(int errnum, char *file_name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file_name, 2);
	if (errnum == 0)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (errnum == 1)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (errnum == 2)
		ft_putstr_fd(": Is a directory\n", 2);
	else if (errnum == 3)
		ft_putstr_fd(" open error\n", 2); 
	else
		ft_putstr_fd(" error\n", 2); 
	free(file_name);
	exit(1);
}

char	*get_file_name(char *file_arg)
{
	char	*file_name;
	int		i;
    int single_flag;
    int double_flag;
    int del;	

	file_name = ft_strdup(file_arg);
	single_flag = 0;
    double_flag = 0;
    i = 0;
	while (file_name[i])
	{
        del = 0;
        if ((double_flag || !single_flag) && file_name[i] == '$')
            file_name = set_env_symbol(file_name, i, &del);
        if (!double_flag && file_name[i] == '\'' && !del)
            single_flag = flag_switch(single_flag);
        if (!single_flag && file_name[i] == '\"' && !del)
            double_flag = flag_switch(double_flag);
        if (!del)
            i++;
	}
	file_name = delete_quote(file_name);
	return (file_name);
}

void	redirection_input(char *file_arg)
{
	int		fd;
	struct stat stats;
	char	*file_name;

	file_name = get_file_name(file_arg);
	stat(file_name, &stats);
	if (access(file_name, F_OK))
		handle_redirection_error(0, file_name);
	if (S_ISDIR(stats.st_mode) || access(file_name, R_OK))
		handle_redirection_error(1, file_name);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		handle_redirection_error(3, file_name);
	dup2(fd, 0);
	close(fd);
	free(file_name);
}

void	redirection_output(char *file_arg)
{
	int		fd;
	struct stat stats;	
	char	*file_name;

	file_name = get_file_name(file_arg);
	stat(file_name, &stats);
	if (!access(file_name, F_OK) && S_ISDIR(stats.st_mode))
		handle_redirection_error(2, file_name);
	if (!access(file_name, F_OK) && access(file_name, W_OK))
		handle_redirection_error(1, file_name);	
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		handle_redirection_error(3, file_name);
	dup2(fd, 1);
	free(file_name);
}

void	redirection_output_append(char *file_arg)
{
	int		fd;
	struct stat stats;
	char	*file_name;

	file_name = get_file_name(file_arg);	
	stat(file_name, &stats);
	if (!access(file_name, F_OK) && S_ISDIR(stats.st_mode))
		handle_redirection_error(2, file_name);
	if (!access(file_name, F_OK) && access(file_name, W_OK))
		handle_redirection_error(1, file_name);
	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		handle_redirection_error(3, file_name);
	dup2(fd, 1);
	free(file_name);
}

void	redirection_heredoc(char *str)
{
	int		pipe_fd[2];

	if (!str)
		str = ft_strdup("");
	pipe(pipe_fd);
	write(pipe_fd[1], str, ft_strlen(str));
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}


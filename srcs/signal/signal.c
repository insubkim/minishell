/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:32:45 by inskim            #+#    #+#             */
/*   Updated: 2023/04/05 05:57:09 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
}

void	ctrl_c(pid_t pid)
{
	if (pid == -1)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		ft_putstr_fd("\n", 1);
}

void	sig_handler(int sig)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (sig == SIGINT)
	{
		ctrl_c(pid);
	}
	if (sig == SIGQUIT)
	{
		if (pid == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			ft_putstr_fd("  \b\b", 1);
		}
		else
			ft_putstr_fd("\n", 1);
	}
}

void	heredoc_set_signal(void)
{
	signal(SIGINT, heredoc_signal_handler);
	signal(SIGQUIT, heredoc_signal_handler);
}

void	heredoc_signal_handler(int sig)
{
	if (SIGINT == sig)
	{
		close(0);
		g_heredoc_sigint = 1;
	}
}

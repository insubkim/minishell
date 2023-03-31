/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:33:11 by inskim            #+#    #+#             */
/*   Updated: 2023/03/31 16:58:54 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void save_input_mode(struct termios *org_term)
{
        tcgetattr(STDIN_FILENO, org_term);
}
void set_input_mode(struct termios *new_term)
{
    tcgetattr(STDIN_FILENO, new_term);
    new_term->c_lflag &= ~(ICANON | ECHO);
    new_term->c_cc[VMIN] = 1;
    new_term->c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, new_term);
}
void reset_input_mode(struct termios *org_term)
{
    tcsetattr(STDIN_FILENO, TCSANOW, org_term);
}

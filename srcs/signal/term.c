/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:33:11 by inskim            #+#    #+#             */
/*   Updated: 2023/04/01 16:03:04 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


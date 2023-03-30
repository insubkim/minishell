/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:53:16 by inskim            #+#    #+#             */
/*   Updated: 2023/03/30 21:34:19 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct termios *term;

int main(int argc, char **argv, char **envp)
{
    char    *line;

    term = (struct termios *)malloc(sizeof(struct termios) * 2);
    if (!term)
        return (0);
    set_signal();
    save_input_mode(&(term[0]));
    while ((line = readline("minishell> ")))
    {
        set_input_mode(&(term[1]));
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
        reset_input_mode(&(term[0]));
    }
    argc++;
    argv++;
    return (0);
}
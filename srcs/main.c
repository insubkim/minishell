/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:53:16 by inskim            #+#    #+#             */
/*   Updated: 2023/03/31 18:46:53 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    char    *line;
    int     status;

    set_signal();
    save_input_mode(term);
    status = -1;
    while ((line = readline("minishell> ")))
    {
        //set_input_mode(term + 1);
        if (line)
        {
            if (ft_strlen(line) > 0)
            {
                add_history(line);
                 if (!ft_is_space(line))
                     handle_line(line, envp, &status);
            }
            free(line);
        }
        //reset_input_mode(term);
    }
    argc++;
    argv++;
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 20:37:44 by insub             #+#    #+#             */
/*   Updated: 2023/03/21 21:43:02 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_line(char *line)
{
    t_list  *cmd_list;
    t_list  *pid_list;
    //parse line
    //cmd_list = parse_line(line);
    

    //execute command
    pid_list = execute_cmd_list(cmd_list);
    
    //wait child processes
    wait_child(pid_list);

    //free
    //free_cmd_list(cmd_list);
}

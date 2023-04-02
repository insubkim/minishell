/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:53:44 by skim2             #+#    #+#             */
/*   Updated: 2023/04/03 05:02:10 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    echo(t_cmd *cmd)
{
    int i;

    i = 1;
    if (ft_strcmp(cmd->args[1], "-n"))
        i++;
    while (cmd->args[i])
        printf("%s", cmd->args[i++]);
    if (ft_strcmp(cmd->args[1], "-n"))
        printf("\n");
    exit(0);
}
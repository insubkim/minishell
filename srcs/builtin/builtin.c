/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:46:34 by skim2             #+#    #+#             */
/*   Updated: 2023/04/03 03:58:09 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(t_cmd *cmd)
{
    if (!ft_strcmp(cmd->cmd, "echo"))
        return (1);
    else if (!ft_strcmp(cmd->cmd, "cd"))
        return (1);
    else if (!ft_strcmp(cmd->cmd, "pwd"))
        return (1);
    else if (!ft_strcmp(cmd->cmd, "export"))
        return (1);
    else if (!ft_strcmp(cmd->cmd, "unset"))
        return (1);
    else if (!ft_strcmp(cmd->cmd, "env"))
        return (1);
    else if (!ft_strcmp(cmd->cmd, "exit"))
        return (1);
    return (0);
}

void    run_builtin(t_cmd *cmd, int *pipe, char **envp)
{
    if (!ft_strcmp(cmd->cmd, "echo"))
        echo(cmd);
    else if (!ft_strcmp(cmd->cmd, "cd"))
         cd(cmd, pipe, envp);
    else if (!ft_strcmp(cmd->cmd, "pwd"))
        run_pwd(envp);
    else if (!ft_strcmp(cmd->cmd, "export"))
        ft_export(cmd, pipe);
    else if (!ft_strcmp(cmd->cmd, "unset"))
         unset(cmd, pipe);
    else if (!ft_strcmp(cmd->cmd, "env"))
        run_env(envp);
    close(pipe[0]);
    close(pipe[1]);
    exit((unsigned char)ft_atoi(cmd->args[1]));
}
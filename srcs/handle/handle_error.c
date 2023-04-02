/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:52:20 by inskim            #+#    #+#             */
/*   Updated: 2023/04/02 18:41:24 by skim2            ###   ########.fr       */
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

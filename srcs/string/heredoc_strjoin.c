/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_strjoin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:34:19 by inskim            #+#    #+#             */
/*   Updated: 2023/04/02 18:03:45 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_strjoin(char *s1, char *s2)
{
	int		len;
	char	*p;
	int		i;

	if (!s1)
		len = ft_strlen(s2);
	else
		len = ft_strlen(s1) + ft_strlen(s2);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		exit(127);
	i = 0;
	while (s1 && s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2 && *s2)
		p[i++] = *s2++;
	p[i] = 0;
	free(s1);
	return (p);
}

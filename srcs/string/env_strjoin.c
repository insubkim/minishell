/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_strjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 15:34:19 by inskim            #+#    #+#             */
/*   Updated: 2023/04/05 03:11:32 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_strjoin(char *s1, char *s2)
{
	int		len;
	char	*p;
	int		i;
	int		j;

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
	j = 0;
	while (s2 && s2[j])
		p[i++] = s2[j++];
	p[i] = 0;
	free(s1);
	free(s2);
	return (p);
}

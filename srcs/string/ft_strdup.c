/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:27:17 by inskim            #+#    #+#             */
/*   Updated: 2023/03/31 17:31:52 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *s)
{
	size_t	len;
	char	*cp;
	size_t	i;

	len = ft_strlen(s);
	cp = (char *)malloc(sizeof(char) * (len + 1));
	if (!cp)
		exit(123);
	i = 0;
	while (i < len)
		cp[i++] = *s++;
	cp[i] = 0;
	return (cp);
}

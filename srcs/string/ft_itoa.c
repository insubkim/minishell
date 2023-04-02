/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 19:16:36 by inskim            #+#    #+#             */
/*   Updated: 2023/04/02 18:00:06 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	int_len(int n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int				len;
	char			*arr;
	int				i;
	unsigned int	u_n;

	len = int_len(n);
	arr = malloc(sizeof(char) * (len + 1));
	if (!arr)
		exit(1);
	arr[len] = 0;
	u_n = n;
	if (n < 0)
	{
		arr[0] = '-';
		u_n = -n;
	}
	i = len - 1;
	while (i >= 0)
	{
		if (n < 0 && i == 0)
			return (arr);
		arr[i--] = u_n % 10 + 48;
		u_n = u_n / 10;
	}
	return (arr);
}

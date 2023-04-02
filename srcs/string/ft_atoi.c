/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:26:13 by inskim            #+#    #+#             */
/*   Updated: 2022/08/12 18:48:15 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static	int	whitespace(char c)
{
	if (c == ' ' || (9 <= c && c <= 13))
		return (1);
	return (0);
}

static	int	sign(char c, int *min)
{
	if (c == '+' || c == '-')
	{
		if (c == '-')
			(*min)++;
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int			min;
	long long	tmp;

	if (nptr == 0)
		return (0);
	while (whitespace(*nptr))
		nptr++;
	min = 0;
	if (sign(*nptr, &min))
		nptr++;
	tmp = 0;
	while ('0' <= *nptr && *nptr <= '9')
		tmp = tmp * 10 + *nptr++ - '0';
	if (min % 2)
		return (-tmp);
	return (tmp);
}

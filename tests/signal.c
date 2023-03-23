/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:11:16 by inskim            #+#    #+#             */
/*   Updated: 2023/03/23 20:16:26 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>

void	h1(int sig)
{
	if (sig == SIGINT)
	{
		printf("SIGINT\n");
	}
}

int main()
{
	signal(SIGINT, h1);
	int a;
	while(1)
	{
		scanf("%d", &a);
		printf("hello\n");
	}

	return (0);


}
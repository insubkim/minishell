/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 20:11:16 by inskim            #+#    #+#             */
/*   Updated: 2023/03/25 01:13:07 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void	h1(int sig)
{
	if (sig == SIGINT)
	{
		printf("SIGINT\n");
	}
}

void	h2(int sig)
{
	if (sig == SIGINT)
	{
		printf("SIGINT22222\n");
	}
}

int main(int argc, char **argv, char **envp)
{
	signal(SIGINT, h1);
	int a;
	(*argv)[0] = 'c';
	(*argv)[1] = 'a';
	(*argv)[2] = 't';
	(*argv)[3] = 0;
	if (!fork())
		signal(SIGINT, h2);
	else
		signal(SIGINT, SIG_IGN);
	while(1)
		;

	return (0);


}
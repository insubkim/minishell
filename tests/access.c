/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 15:11:39 by inskim            #+#    #+#             */
/*   Updated: 2023/03/25 15:14:36 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	if (access("a.out", F_OK) == 0)
		printf("a exists\n");
	else
		printf("a does not exist\n");
	if (access("a.out", X_OK) == 0)
		printf("a exec OK\n");
	else
		printf("a exec NO\n");
	
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 22:10:14 by halbit            #+#    #+#             */
/*   Updated: 2026/01/18 00:38:03 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L

#include "libft/libft.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

volatile int	ready = 0;

void	sigusr_handler(int signum)
{
	printf("Received signal %d\n", signum);
	(void)signum;
}

int	main(int argc, char **argv)
{
	if (argc != 2 || !((int)ft_strlen(argv[1])))
		return (1);
	struct sigaction	sa;
	sa.sa_handler = &sigusr_handler;
	sigaction(SIGUSR2, &sa, NULL);
	int x;
	int	pid;
	
	x = 5;
	pid = atoi(argv[1]);
	while (x--)
	{
		kill(pid, SIGUSR1);
		printf("sending action for server PID(%d)", pid);
		sleep(2);
	}
	return (0);
}

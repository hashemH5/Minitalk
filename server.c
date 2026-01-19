/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 23:27:10 by halbit            #+#    #+#             */
/*   Updated: 2026/01/18 00:38:07 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

static void sigusr_handler(int sig, siginfo_t *info, void *context)
{
    (void)context;
	printf("signal received SIGUSR1: %d\n", sig);
    printf("from process: %d\n", info->si_pid);
    kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
    struct sigaction	sa;
	sa.sa_sigaction = sigusr_handler;
    sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
    printf("Server is running with PID: %d\n", getpid());
    int x;
    
	x = 5;
	while (x--)
	{
	 	printf("\nwating for client...\n");
		sleep(10);
	}
    return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 22:10:14 by halbit            #+#    #+#             */
/*   Updated: 2026/01/22 21:28:31 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L

#include "libft/libft.h"
#include <signal.h>

volatile int	g_ready = 0;

static void	action(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGUSR1)
		g_ready = 1;
	(void)info;
	(void)context;
}

void	end_mass(int pid)
{
	int	end;

	end = 8;
	while (end--)
	{
		g_ready = 0;
		kill(pid, SIGUSR2);
		while (!g_ready)
			pause();
	}
}

static void	str_kill(int pid, char *str)
{
	unsigned char	c;
	int				bit;

	while (*str)
	{
		bit = 8;
		c = *(str++);
		while (bit--)
		{
			g_ready = 0;
			if (c >> bit & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			while (!g_ready)
				pause();
		}
	}
	end_mass(pid);
}

int	main(int argc, char **argv)
{
	struct sigaction	sc;

	sigemptyset(&sc.sa_mask);
	sc.sa_flags = SA_SIGINFO;
	sc.sa_sigaction = action;
	if (argc != 3 || !((int)ft_strlen(argv[1])))
		return (1);
	if (kill(ft_atoi(argv[1]), 0) == -1)
		return (write(2, "error\n", 6));
	ft_putstr_fd("Sent : ", 1);
	ft_putnbr_fd(ft_strlen(argv[2]), 1);
	ft_putchar_fd('\n', 1);
	sigaction(SIGUSR1, &sc, NULL);
	str_kill(ft_atoi(argv[1]), argv[2]);
	return (0);
}

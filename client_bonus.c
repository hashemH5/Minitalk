/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 22:10:14 by halbit            #+#    #+#             */
/*   Updated: 2026/01/24 20:56:35 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L

#include "libft/libft.h"
#include <signal.h>

volatile int	g_ready = 0;

static void	action(int sig)
{
	if (sig == SIGUSR1)
		g_ready = 1;
}

static void	client_error(int e)
{
	if (e == -1)
		write(2, "Error: Failed to send signal.\n", 28);
	else if (e == 1)
		write(2, "Error: Usage: ./client <PID> <Message>\n", 39);
	else if (e == 2)
		write(2, "Error: Invalid PID.\n", 20);
	else if (e == 0)
		return ;
	exit(1);
}

static void	end_mass(int pid)
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
	int				val;

	val = 0;
	while (*str)
	{
		bit = 8;
		c = *(str++);
		while (bit--)
		{
			g_ready = 0;
			if (c >> bit & 1)
				val = kill(pid, SIGUSR1);
			else
				val = kill(pid, SIGUSR2);
			client_error(val);
			while (!g_ready)
				pause();
		}
		if (kill(pid, 0) == -1)
			client_error(2);
	}
	end_mass(pid);
}

int	main(int argc, char **argv)
{
	struct sigaction	sc;

	sc.sa_handler = &action;
	sigemptyset(&sc.sa_mask);
	sc.sa_flags = 0;
	if (argc != 3 || !(ft_strlen(argv[1])))
		client_error(1);
	if (kill(ft_atoi(argv[1]), 0) == -1)
		client_error(2);
	ft_putstr_fd("Sent : ", 1);
	ft_putnbr_fd(ft_strlen(argv[2]), 1);
	ft_putchar_fd('\n', 1);
	sigaction(SIGUSR1, &sc, NULL);
	str_kill(ft_atoi(argv[1]), argv[2]);
	return (0);
}

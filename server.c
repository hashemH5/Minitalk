/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 23:27:10 by halbit            #+#    #+#             */
/*   Updated: 2026/01/22 20:57:58 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"

unsigned char *saver(unsigned char *rec, char new)
{
	char unsigned	*str;
	int				i;
	
	i = 0;
	if (new == '\0')
	{
		if (rec)
			ft_putstr_fd((char*)rec, 1);
		ft_putstr_fd("\n", 1);
		free(rec);
		return(NULL);
	}
	str = malloc(ft_strlen((char*)rec) + 2);
	while (rec && rec[i])
	{
		str[i] = rec[i];
		i++;
	}
	if (!rec)
		free(rec);
	str[i] = new;
	str[++i] = '\0';
	return (str);
}

static void	sigusr_handler(int sig, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int	bit = 0;
	static unsigned char *str = NULL;

	(void)context;
	c <<= 1;
	if (sig == SIGUSR1)
		c |= 1;
	bit++;
	if (bit == 8)
	{
		str = saver(str, c);
		bit = 0;
		c = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sigusr_handler;
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halbit <halbit@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 23:27:10 by halbit            #+#    #+#             */
/*   Updated: 2026/01/24 20:56:16 by halbit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _POSIX_C_SOURCE 200809L

#include "libft/libft.h"
#include <signal.h>

static int	server_error(unsigned char *s)
{
	free(s);
	write(2, "server_error\n", 13);
	exit(1);
}

static unsigned char	*saver(unsigned char *rec, char new)
{
	char unsigned	*str;
	int				i;

	i = 0;
	if (new == '\0')
	{
		if (rec)
			ft_putstr_fd((char *)rec, 1);
		ft_putstr_fd("\n", 1);
		free(rec);
		return (NULL);
	}
	str = malloc(ft_strlen((char *)rec) + 2);
	if (!str)
		server_error(rec);
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
	static int				bit = 0;
	static unsigned char	*str = NULL;
	int						val;

	val = 0;
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
	val = kill(info->si_pid, SIGUSR1);
	if (val == -1)
		server_error(str);
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

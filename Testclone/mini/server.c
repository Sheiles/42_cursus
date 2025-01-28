/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:46:58 by sheiles           #+#    #+#             */
/*   Updated: 2024/12/20 12:26:27 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Libft/libft.h"

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static int	bit_index = 0;
	static char	current_char = 0;

	(void)context;
	current_char |= (sig == SIGUSR2) << (7 - bit_index);
	bit_index++;
	if (bit_index == 8)
	{
		if (current_char == '\0')
		{
			write(1, "\n", 1);
		}
		else
		{
			write(1, &current_char, 1);
		}
		bit_index = 0;
		current_char = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	printf("Server PID: %d\n", getpid());
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}

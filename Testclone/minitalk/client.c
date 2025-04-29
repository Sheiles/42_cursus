/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:11:05 by sheiles           #+#    #+#             */
/*   Updated: 2025/04/29 21:06:30 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	handle_ack(int sig)
{
	(void)sig;
}

void	send_bit(pid_t server_pid, int bit)
{
	if (bit == 1)
	{
		if (kill(server_pid, SIGUSR2) == -1)
		{
			printf("Error sending signal");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (kill(server_pid, SIGUSR1) == -1)
		{
			printf("Error sending signal");
			exit(EXIT_FAILURE);
		}
	}
	usleep(100);
}

void	send_char(pid_t server_pid, char c)
{
	int	bit;
	int	i;

	i = 7;
	while (i >= 0)
	{
		bit = (c >> i) & 1;
		send_bit(server_pid, bit);
		i--;
	}
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;
	char				*message;
	size_t				i;
	struct sigaction	sa;

	sa.sa_handler = handle_ack;
	sa.sa_flags = SA_RESTART;
	if (argc != 3)
	{
		printf("Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	sigaction(SIGUSR1, &sa, NULL);
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	i = 0;
	while (i < ft_strlen(message))
	{
		send_char(server_pid, message[i]);
		i++;
	}
	send_char(server_pid, '\0');
	return (0);
}

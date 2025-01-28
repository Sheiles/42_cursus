/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:11:05 by sheiles           #+#    #+#             */
/*   Updated: 2025/01/09 09:46:46 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Libft/libft.h"

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
			perror("Error sending signal");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (kill(server_pid, SIGUSR1) == -1)
		{
			perror("Error sending signal");
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
	pid_t	server_pid;
	char	*message;
	size_t	i;

	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}

	struct sigaction sa;
	sa.sa_handler = handle_ack;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);

	server_pid = atoi(argv[1]);
	message = argv[2];

	i = 0;
	while (i < strlen(message))
	{
		send_char(server_pid, message[i]);
		i++;
	}
	send_char(server_pid, '\0');
	return (0);
}

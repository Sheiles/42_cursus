/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 21:13:29 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/08 21:16:11 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

static void	handle_sigint_parent(int signo)
{
	(void)signo;
	g_sig = SIGINT;
	write(1, "\n", 1);
}

static void	handle_sigquit_parent(int signo)
{
	(void)signo;
}

void	setup_signals_interactive(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handle_sigint_parent;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = handle_sigquit_parent;
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_signals_child(void)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void	handle_sigint_heredoc(int signo)
{
	(void)signo;
	g_sig = SIGINT;
	write(1, "\n", 1);
	close(0);
}

void	setup_signals_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handle_sigint_heredoc;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

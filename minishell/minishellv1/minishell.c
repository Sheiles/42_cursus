/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:47:40 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/08 21:15:53 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

static void	sigint_parent(int signo)
{
	(void)signo;
	g_sig = SIGINT;
	write(1, "\n", 1);
}

static void	setup_signals_interactive(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sigint_parent;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

static void	handle_sigint_after_readline(char **line)
{
	if (g_sig == SIGINT)
	{
		g_shell.exit_status = 130;
		g_sig = 0;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		free(*line);
		*line = NULL;
	}
}

static int	process_line(char *line)
{
	t_cmd	*cmd;

	if (!*line)
		return (free(line), 1);
	add_history(line);
	cmd = parse_input(line);
	free(line);
	if (!cmd)
		return (0);
	execute(cmd);
	return (0);
}

static void	shell_loop(void)
{
	char	*line;

	setup_signals_interactive();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		handle_sigint_after_readline(&line);
		if (!line)
			continue ;
		if (process_line(line))
			continue ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	ms_ctx(&shell);
	g_shell.exit_status = 0;
	g_shell.env = init_env(envp);
	shell_loop();
	return (g_shell.exit_status);
}

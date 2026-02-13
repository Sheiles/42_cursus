/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:47:40 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/08 21:22:43 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell		g_shell;

static void	handle_sigint(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_shell.exit_status = 130;
}

static void	handle_sigquit(int signo)
{
	(void)signo;
	write(1, "\b\b  \b\b", 6);
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmds;

	(void)argc;
	(void)argv;
	init_shell(envp);
	while (1)
	{
		setup_signals();
		line = readline("minishell$ ");
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (*line)
			add_history(line);
		cmds = parse_input(line);
		if (cmds)
			execute(cmds);
		free_cmds(cmds);
		free(line);
	}
	free_shell();
	return (0);
}

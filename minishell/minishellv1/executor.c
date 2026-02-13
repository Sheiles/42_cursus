/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:47:27 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/08 15:37:54 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	apply_fds(int stdin_fd, int stdout_fd)
{
	if (stdin_fd != STDIN_FILENO)
	{
		dup2(stdin_fd, STDIN_FILENO);
		close(stdin_fd);
	}
	if (stdout_fd != STDOUT_FILENO)
	{
		dup2(stdout_fd, STDOUT_FILENO);
		close(stdout_fd);
	}
}

static void	run_child(t_cmd *cmd, int in_fd, int out_fd)
{
	int	stdin_fd;
	int	stdout_fd;

	stdin_fd = in_fd;
	stdout_fd = out_fd;
	if (handle_redirections(cmd->redirs, &stdin_fd, &stdout_fd) < 0)
		exit(1);
	apply_fds(stdin_fd, stdout_fd);
	if (is_builtin(cmd->args[0]))
		exit(exec_builtin(cmd));
	execvp(cmd->args[0], cmd->args);
	perror("execvp");
	exit(127);
}

static int	open_pipe_if_needed(int pipe_fd[2], int has_next)
{
	if (has_next)
	{
		if (pipe(pipe_fd) < 0)
		{
			perror("pipe");
			return (-1);
		}
	}
	return (0);
}

static void	parent_after_fork(int *in_fd, int has_next, int pipe_fd[2], int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_shell.exit_status = WEXITSTATUS(status);
	if (*in_fd != 0)
		close(*in_fd);
	if (has_next)
	{
		close(pipe_fd[1]);
		*in_fd = pipe_fd[0];
	}
}

void	execute(t_cmd *cmds)
{
	t_cmd	*cmd;
	int		in_fd;
	int		pipe_fd[2];
	int		has_next;
	int		pid;

	cmd = cmds;
	in_fd = 0;
	while (cmd)
	{
		has_next = (cmd->next != NULL);
		if (open_pipe_if_needed(pipe_fd, has_next) < 0)
			return ;
		pid = fork();
		if (pid == 0)
		{
			if (has_next)
				run_child(cmd, in_fd, pipe_fd[1]);
			else
				run_child(cmd, in_fd, STDOUT_FILENO);
		}
		else
			parent_after_fork(&in_fd, has_next, pipe_fd, pid);
		cmd = cmd->next;
	}
}

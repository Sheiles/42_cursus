#include "minishell.h"

static void	child_process(t_cmd *cmd, int in_fd, int out_fd)
{
	int stdin_fd = in_fd;
	int stdout_fd = out_fd;

	if (handle_redirections(cmd->redirs, &stdin_fd, &stdout_fd) < 0)
		exit(1);
	if (stdin_fd != STDIN_FILENO)
		dup2(stdin_fd, STDIN_FILENO), close(stdin_fd);
	if (stdout_fd != STDOUT_FILENO)
		dup2(stdout_fd, STDOUT_FILENO), close(stdout_fd);
	if (is_builtin(cmd->args[0]))
		exit(exec_builtin(cmd));
	execvp(cmd->args[0], cmd->args);
	perror("execvp");
	exit(127);
}

void	execute(t_cmd *cmds)
{
	t_cmd	*cmd = cmds;
	int		in_fd = 0, pipe_fd[2], has_next, pid;

	while (cmd)
	{
		has_next = cmd->next != NULL;
		if (has_next && pipe(pipe_fd) < 0)
			return (perror("pipe"));
		pid = fork();
		if (pid == 0)
		{
			if (has_next)
				child_process(cmd, in_fd, pipe_fd[1]);
			else
				child_process(cmd, in_fd, STDOUT_FILENO);
		}
		else
		{
			waitpid(pid, &g_shell.exit_status, 0);
			if (in_fd != 0)
				close(in_fd);
			if (has_next)
				close(pipe_fd[1]), in_fd = pipe_fd[0];
		}
		cmd = cmd->next;
	}
}

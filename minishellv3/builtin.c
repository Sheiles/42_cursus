#include "minishell.h"

int	builtin_echo(char **args)
{
	int	i = 1;
	int	newline = 1;

	if (args[i] && strcmp(args[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}

int	builtin_cd(char **args)
{
	char	*path = args[1] ? args[1] : get_env_value("HOME");

	if (!path)
		return (fprintf(stderr, "cd: HOME not set\n"), 1);
	if (chdir(path) != 0)
		return (perror("cd"), 1);
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)))
		set_env_value("PWD", cwd);
	return (0);
}

int	builtin_pwd(void)
{
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("pwd");
	return (0);
}

int	builtin_env(void)
{
	t_env *env = g_shell.env;
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

int	builtin_export(char **args)
{
	int i = 1;

	while (args[i])
	{
		char *sep = strchr(args[i], '=');
		if (sep)
		{
			*sep = 0;
			set_env_value(args[i], sep + 1);
			*sep = '=';
		}
		else
			set_env_value(args[i], "");
		i++;
	}
	return (0);
}

int	builtin_unset(char **args)
{
	int i = 1;

	while (args[i])
	{
		unset_env_key(args[i]);
		i++;
	}
	return (0);
}

int	builtin_exit(char **args)
{
	int i = 0;

	printf("exit\n");
	if (args[1])
	{
		while (args[1][i])
		{
			if (args[1][i] < '0' || args[1][i] > '9')
			{
				fprintf(stderr, "exit: numeric argument required\n");
				exit(255);
			}
			i++;
		}
		exit(atoi(args[1]));
	}
	exit(g_shell.exit_status);
}

int	is_builtin(char *cmd)
{
	return (!strcmp(cmd, "echo") || !strcmp(cmd, "cd") || !strcmp(cmd, "pwd") ||
		!strcmp(cmd, "export") || !strcmp(cmd, "unset") || !strcmp(cmd, "env") ||
		!strcmp(cmd, "exit"));
}

int	exec_builtin(t_cmd *cmd)
{
	char **args = cmd->args;

	if (!strcmp(args[0], "echo"))
		return builtin_echo(args);
	if (!strcmp(args[0], "cd"))
		return builtin_cd(args);
	if (!strcmp(args[0], "pwd"))
		return builtin_pwd();
	if (!strcmp(args[0], "env"))
		return builtin_env();
	if (!strcmp(args[0], "export"))
		return builtin_export(args);
	if (!strcmp(args[0], "unset"))
		return builtin_unset(args);
	if (!strcmp(args[0], "exit"))
		return builtin_exit(args);
	return (1);
}

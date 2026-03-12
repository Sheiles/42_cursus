











#include "minishell.h"

int	builtin_env(void)
{
	t_env	*env;

	env = g_shell.env;
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

static void	export_one(char *arg)
{
	char	*sep;

	sep = strchr(arg, '=');
	if (sep)
	{
		*sep = '\0';
		set_env_value(arg, sep + 1);
		*sep = '=';
	}
	else
		set_env_value(arg, "");
}

int	builtin_export(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		export_one(args[i]);
		i++;
	}
	return (0);
}

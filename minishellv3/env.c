#include "minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*head = NULL;
	t_env	*last = NULL;
	int		i = 0;

	while (envp[i])
	{
		char *sep = strchr(envp[i], '=');
		if (sep)
		{
			t_env *node = malloc(sizeof(t_env));
			node->key = strndup(envp[i], sep - envp[i]);
			node->value = strdup(sep + 1);
			node->next = NULL;
			if (!head)
				head = node;
			else
				last->next = node;
			last = node;
		}
		i++;
	}
	return head;
}

void	free_env(t_env *env)
{
	t_env *tmp;
	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

char	*get_env_value(char *key)
{
	t_env *env = g_shell.env;

	while (env)
	{
		if (!strcmp(env->key, key))
			return env->value;
		env = env->next;
	}
	return NULL;
}

void	set_env_value(char *key, char *value)
{
	t_env *env = g_shell.env;

	while (env)
	{
		if (!strcmp(env->key, key))
		{
			free(env->value);
			env->value = strdup(value);
			return;
		}
		env = env->next;
	}

	t_env *new = malloc(sizeof(t_env));
	new->key = strdup(key);
	new->value = strdup(value);
	new->next = g_shell.env;
	g_shell.env = new;
}

void	unset_env_key(char *key)
{
	t_env *env = g_shell.env;
	t_env *prev = NULL;

	while (env)
	{
		if (!strcmp(env->key, key))
		{
			if (prev)
				prev->next = env->next;
			else
				g_shell.env = env->next;
			free(env->key);
			free(env->value);
			free(env);
			return;
		}
		prev = env;
		env = env->next;
	}
}

char	**env_to_array(void)
{
	t_env	*env = g_shell.env;
	int		count = 0;
	char	**arr;
	int		i = 0;

	while (env)
	{
		count++;
		env = env->next;
	}
	arr = malloc(sizeof(char *) * (count + 1));
	env = g_shell.env;
	while (env)
	{
		arr[i] = malloc(strlen(env->key) + strlen(env->value) + 2);
		sprintf(arr[i], "%s=%s", env->key, env->value);
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return arr;
}

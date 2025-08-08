/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_getset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:50:22 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/08 15:50:23 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *key)
{
	t_env	*env;

	env = g_shell.env;
	while (env)
	{
		if (!strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static void	assign_value(t_env *env, const char *value)
{
	free(env->value);
	env->value = strdup(value);
}

void	set_env_value(char *key, char *value)
{
	t_env	*env;
	t_env	*new;

	env = g_shell.env;
	while (env)
	{
		if (!strcmp(env->key, key))
			return (assign_value(env, value));
		env = env->next;
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = strdup(key);
	new->value = strdup(value);
	new->next = g_shell.env;
	g_shell.env = new;
}

void	unset_env_key(char *key)
{
	t_env	*env;
	t_env	*prev;

	env = g_shell.env;
	prev = NULL;
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
			return ;
		}
		prev = env;
		env = env->next;
	}
}

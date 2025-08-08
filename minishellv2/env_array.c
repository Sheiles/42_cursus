/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:50:12 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/08 15:50:13 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_count(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		n++;
		env = env->next;
	}
	return (n);
}

char	**env_to_array(void)
{
	char	**arr;
	t_env	*env;
	int		i;
	int		len;

	i = 0;
	env = g_shell.env;
	arr = malloc(sizeof(char *) * (env_count(env) + 1));
	if (!arr)
		return (NULL);
	while (env)
	{
		len = strlen(env->key) + strlen(env->value) + 2;
		arr[i] = malloc(len);
		if (!arr[i])
			return (arr);
		sprintf(arr[i], "%s=%s", env->key, env->value);
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return (arr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:50:05 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/08 15:50:08 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		unset_env_key(args[i]);
		i++;
	}
	return (0);
}

static int	is_numeric(const char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(char **args)
{
	printf("exit\n");
	if (args[1])
	{
		if (!is_numeric(args[1]))
		{
			fprintf(stderr, "exit: numeric argument required\n");
			exit(255);
		}
		exit(atoi(args[1]));
	}
	exit(g_shell.exit_status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:50:34 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/09 16:50:36 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_mini *ms, char **cmd, char ***envp)
{
	size_t	i;

	if (cmd[1])
	{
		ft_putstr_fd ("-" PROMPT_MSG ": env: " INVALID_USAGE "\n", 2);
		ms -> error = 42;
	}
	else
	{
		i = 0;
		while (envp && *envp && envp[0][i])
		{
			ft_printf ("%s\n", envp[0][i]);
			i++;
		}
		ms -> error = 0;
	}
}

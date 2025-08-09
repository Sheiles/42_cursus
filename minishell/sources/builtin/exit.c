/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:50:38 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/09 16:50:43 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!(ft_isdigit (str[i]) || str[i] == '+'))
			return (0);
		i++;
	}
	return (1);
}

static int	check_for_zeros(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] != '0')
			return (1);
	}
	return (0);
}

void	ft_exit(t_mini *ms, char **cmd)
{
	int	code;

	if (!cmd[1])
	{
		cmd = free_mat(cmd);
		exit_handler (ms, NULL, 0);
	}
	if (!check_for_zeros(cmd[1]))
	{
		cmd = free_mat(cmd);
		exit_handler (ms, NULL, 0);
	}
	if (!cmd[2] && is_valid_number (cmd[1]))
	{
		code = ft_atoi (cmd[1]);
		cmd = free_mat(cmd);
		exit_handler (ms, "exited with error number", code);
	}
	cmd = free_mat(cmd);
	exit_handler (ms, "-" PROMPT_MSG ": exit: " INVALID_USAGE, 42);
}

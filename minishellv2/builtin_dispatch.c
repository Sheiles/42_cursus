/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:49:41 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/08 15:49:45 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!strcmp(cmd, "echo"))
		return (1);
	if (!strcmp(cmd, "cd"))
		return (1);
	if (!strcmp(cmd, "pwd"))
		return (1);
	if (!strcmp(cmd, "export"))
		return (1);
	if (!strcmp(cmd, "unset"))
		return (1);
	if (!strcmp(cmd, "env"))
		return (1);
	if (!strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd)
{
	char	**a;

	a = cmd->args;
	if (!strcmp(a[0], "echo"))
		return (builtin_echo(a));
	if (!strcmp(a[0], "cd"))
		return (builtin_cd(a));
	if (!strcmp(a[0], "pwd"))
		return (builtin_pwd());
	if (!strcmp(a[0], "env"))
		return (builtin_env());
	if (!strcmp(a[0], "export"))
		return (builtin_export(a));
	if (!strcmp(a[0], "unset"))
		return (builtin_unset(a));
	if (!strcmp(a[0], "exit"))
		return (builtin_exit(a));
	return (1);
}

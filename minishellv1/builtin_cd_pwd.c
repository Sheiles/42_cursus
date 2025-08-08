/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:47:42 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/08 15:49:47 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cd_path(char **args)
{
	if (args[1])
		return (args[1]);
	return (get_env_value("HOME"));
}

int	builtin_cd(char **args)
{
	char	*path;
	char	cwd[1024];
	int		ret;

	path = get_cd_path(args);
	if (!path)
	{
		fprintf(stderr, "cd: HOME not set\n");
		return (1);
	}
	ret = chdir(path);
	if (ret != 0)
		return (perror("cd"), 1);
	if (getcwd(cwd, sizeof(cwd)))
		set_env_value("PWD", cwd);
	return (0);
}

int	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
		perror("pwd");
	return (0);
}

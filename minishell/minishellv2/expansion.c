/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:47:33 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/08 21:33:58 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

static int	is_valid_var_char(char c)
{
	if (isalnum((unsigned char)c) || c == '_')
		return (1);
	return (0);
}

static void	append_str(char *res, int *j, const char *src)
{
	size_t	len;

	if (!src)
		return ;
	len = strlen(src);
	memcpy(res + *j, src, len);
	*j += (int)len;
}

static int	handle_dollar(const char *str, int i, char *res, int *j)
{
	if (str[i] == '$')
	{
		res[(*j)++] = '$';
		return (i + 1);
	}
	if (str[i] == '?')
	{
		*j += sprintf(res + *j, "%d", g_shell.exit_status);
		return (i + 1);
	}
	return (-1);
}

static int	expand_var(const char *str, int i, char *res, int *j)
{
	int		k;
	int		ret;
	char	var[256];
	char	*val;

	ret = handle_dollar(str, i, res, j);
	if (ret != -1)
		return (ret);
	k = 0;
	while (str[i] && is_valid_var_char(str[i]) && k < 255)
		var[k++] = str[i++];
	var[k] = '\0';
	if (k == 0)
	{
		res[(*j)++] = '$';
		return (i);
	}
	val = get_env_value(var);
	if (val)
		append_str(res, j, val);
	return (i);
}

char	*expand_variables(char *str)
{
	char	*res;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	res = (char *)malloc(4096);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
			i = expand_var(str, i + 1, res, &j);
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:48:01 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/08 22:24:54 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>

char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	len;

	if (!s)
		return (NULL);
	len = strlen(s);
	copy = (char *)malloc(len + 1);
	if (!copy)
		return (NULL);
	memcpy(copy, s, len + 1);
	return (copy);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	l1;
	size_t	l2;
	char	*new;

	l1 = 0;
	l2 = 0;
	if (s1)
		l1 = strlen(s1);
	if (s2)
		l2 = strlen(s2);
	new = (char *)malloc(l1 + l2 + 1);
	if (!new)
		return (NULL);
	if (s1)
		memcpy(new, s1, l1);
	if (s2)
		memcpy(new + l1, s2, l2);
	new[l1 + l2] = '\0';
	return (new);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*strip_quotes(char *s)
{
	char	*out;
	int		i;
	int		j;
	char	quote;

	if (!s)
		return (NULL);
	out = (char *)malloc(strlen(s) + 1);
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (s[i])
	{
		if (!quote && (s[i] == '\'' || s[i] == '"'))
			quote = s[i];
		else if (quote && s[i] == quote)
			quote = 0;
		else
			out[j++] = s[i];
		i++;
	}
	out[j] = '\0';
	return (out);
}

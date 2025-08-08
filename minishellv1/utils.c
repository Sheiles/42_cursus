/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:48:01 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/08 17:13:46 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s)
{
	char	*copy;

	copy = malloc(strlen(s) + 1);
	if (!copy)
		return (NULL);
	strcpy(copy, s);
	return (copy);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;

	new = malloc(strlen(s1) + strlen(s2) + 1);
	if (!new)
		return (NULL);
	strcpy(new, s1);
	strcat(new, s2);
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
	char	*new;
	int		i;
	int		j;
	char	quote;

	new = malloc
		if (!s || !(new(strlen(s) + 1)))
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
			new[j++] = s[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

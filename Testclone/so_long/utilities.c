/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:12:28 by sheiles           #+#    #+#             */
/*   Updated: 2025/04/29 19:46:00 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	sl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

void	sl_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, sl_strlen(s));
}

int	word_count(const char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static int	word_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	**sl_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		len;

	i = 0;
	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!tab)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		len = word_len(s, c);
		if (len)
		{
			tab[i] = ft_strndup(s, len);
			if (!tab[i++])
				return (NULL);
			s += len;
		}
	}
	tab[i] = NULL;
	return (tab);
}

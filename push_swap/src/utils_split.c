#include "../includes/push_swap.h"
#include <stdlib.h>

static int	count_words(const char *s, char c)
{
	int	count = 0;

	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	*word_dup(const char *s, char c)
{
	int		len = 0;
	char	*word;
	int		i = 0;

	while (s[len] && s[len] != c)
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i = 0;

	if (!s)
		return (NULL);
	split = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!split)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			split[i] = word_dup(s, c);
			if (!split[i++])
				return (NULL);
			while (*s && *s != c)
				s++;
		}
	}
	split[i] = NULL;
	return (split);
}

void	free_split(char **split)
{
	int	i = 0;

	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

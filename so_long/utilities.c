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

char	**sl_split(char const *s, char c)
{
	char	**tab;

	int start, i = 0;
	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!tab)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		start = 0;
		while (s[start] && s[start] != c)
			start++;
		if (start)
		{
			tab[i] = strndup(s, start);
			if (!tab[i++])
				return (NULL);
			s += start;
		}
	}
	tab[i] = NULL;
	return (tab);
}

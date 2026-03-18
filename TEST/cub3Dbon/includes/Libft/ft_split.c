











#include "libft.h"
#include <stdlib.h>

static size_t	count_words(const char *s, char sep)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == sep)
			s++;
		if (*s && *s != sep)
		{
			count++;
			while (*s && *s != sep)
				s++;
		}
	}
	return (count);
}

static char	*next_word(const char **s, char sep)
{
	const char	*start;
	size_t		len;
	char		*word;
	size_t		i;

	len = 0;
	while (**s && **s == sep)
		(*s)++;
	start = *s;
	while ((*s)[len] && (*s)[len] != sep)
		len++;
	*s += len;
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

char	**ft_split(const char *s, char sep)
{
	size_t	words;
	char	**result;
	size_t	i;

	words = count_words(s, sep);
	result = (char **)malloc((words + 1) * sizeof(char *));
	i = 0;
	if (!result)
		return (NULL);
	while (i < words)
	{
		result[i] = next_word(&s, sep);
		if (!result[i])
		{
			while (i-- > 0)
				free(result[i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}

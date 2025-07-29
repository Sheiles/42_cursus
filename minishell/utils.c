#include "minishell.h"

char	*ft_strdup(const char *s)
{
	char *copy = malloc(strlen(s) + 1);
	if (!copy)
		return NULL;
	strcpy(copy, s);
	return copy;
}

char	*ft_strjoin(char *s1, char *s2)
{
	char *new = malloc(strlen(s1) + strlen(s2) + 1);
	if (!new)
		return NULL;
	strcpy(new, s1);
	strcat(new, s2);
	return new;
}

void	free_array(char **arr)
{
	int i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	*strip_quotes(char *s)
{
	int		len = strlen(s);
	char	*new = malloc(len + 1);
	int		i = 0, j = 0;
	char	quote = 0;

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
	return new;
}

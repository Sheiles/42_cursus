











#include <stdlib.h>

char	*ft_strndup(const char *s, size_t n)
{
	char	*copy;
	size_t	i;

	copy = malloc(sizeof(char) * (n + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

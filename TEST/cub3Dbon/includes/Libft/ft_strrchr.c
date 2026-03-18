











#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_occurrence;
	char	character;

	last_occurrence = NULL;
	character = (char)c;
	while (*s)
	{
		if (*s == character)
		{
			last_occurrence = (char *)s;
		}
		s++;
	}
	if (character == '\0')
	{
		return ((char *)s);
	}
	return (last_occurrence);
}

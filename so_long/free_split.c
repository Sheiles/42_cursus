#include "so_long.h"

void	free_split(char **split)
{
	int	i = 0;

	if (!split)
		return;
	while (split[i])
		free(split[i++]);
	free(split);
}













#include "../includes/cub3d.h"

int	parse_floor_color(char *line, t_game *game)
{
	char	**colors;
	char	*trimmed;
	int		i;

	trimmed = ft_strtrim(line + 1, " ");
	colors = ft_split(trimmed, ',');
	free(trimmed);
	if (!colors || !colors[0] || !colors[1] || !colors[2])
		return (-1);
	game->floor_color.r = ft_atoi(colors[0]);
	game->floor_color.g = ft_atoi(colors[1]);
	game->floor_color.b = ft_atoi(colors[2]);
	i = 0;
	while (colors[i])
		free(colors[i++]);
	free(colors);
	return (0);
}

int	parse_ceiling_color(char *line, t_game *game)
{
	char	**colors;
	char	*trimmed;
	int		i;

	trimmed = ft_strtrim(line + 1, " ");
	colors = ft_split(trimmed, ',');
	free(trimmed);
	if (!colors || !colors[0] || !colors[1] || !colors[2])
		return (-1);
	game->ceiling_color.r = ft_atoi(colors[0]);
	game->ceiling_color.g = ft_atoi(colors[1]);
	game->ceiling_color.b = ft_atoi(colors[2]);
	i = 0;
	while (colors[i])
		free(colors[i++]);
	free(colors);
	return (0);
}

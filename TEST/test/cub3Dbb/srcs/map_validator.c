#include "../includes/cub3d.h"

static int	flood_fill(t_game *game, char **visited, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map.width || y >= game->map.height)
		return (-1);
	if (visited[y][x] || game->map.grid[y][x] == '1')
		return (0);
	if (x >= (int)ft_strlen(game->map.grid[y]) || game->map.grid[y][x] == ' ')
		return (-1);
	visited[y][x] = 1;
	if (flood_fill(game, visited, x + 1, y) == -1
		|| flood_fill(game, visited, x - 1, y) == -1
		|| flood_fill(game, visited, x, y + 1) == -1
		|| flood_fill(game, visited, x, y - 1) == -1)
		return (-1);
	return (0);
}

static char	**alloc_visited(t_game *game)
{
	char	**visited;
	int		i;

	visited = ft_calloc(game->map.height, sizeof(char *));
	if (!visited)
		return (NULL);
	i = 0;
	while (i < game->map.height)
	{
		visited[i] = ft_calloc(game->map.width + 1, sizeof(char));
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			return (NULL);
		}
		i++;
	}
	return (visited);
}

static int	check_map_closed(t_game *game)
{
	char	**visited;
	int		result;
	int		height;

	visited = alloc_visited(game);
	if (!visited)
		return (-1);
	height = game->map.height;
	result = flood_fill(game, visited, (int)game->player.x,
			(int)game->player.y);
	free_visited(visited, height);
	return (result);
}

static int	check_chars_and_colors(t_game *game)
{
	int		x;
	int		y;
	char	c;

	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < (int)ft_strlen(game->map.grid[y]))
		{
			c = game->map.grid[y][x];
			if (c != '0' && c != '1' && c != 'N' && c != 'S'
				&& c != 'E' && c != 'W' && c != ' ')
				return (-1);
		}
	}
	if (game->floor_color.r < 0 || game->floor_color.r > 255
		|| game->floor_color.g < 0 || game->floor_color.g > 255
		|| game->floor_color.b < 0 || game->floor_color.b > 255)
		return (-1);
	if (game->ceiling_color.r < 0 || game->ceiling_color.r > 255
		|| game->ceiling_color.g < 0 || game->ceiling_color.g > 255
		|| game->ceiling_color.b < 0 || game->ceiling_color.b > 255)
		return (-1);
	return (0);
}

int	validate_map(t_game *game)
{
	int	x;
	int	y;
	int	player_found;

	player_found = 0;
	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < (int)ft_strlen(game->map.grid[y]))
			if (check_player_char(game, x, y) && ++player_found > 1)
				return (-1);
	}
	if (!player_found)
		return (-1);
	if (check_chars_and_colors(game) == -1)
		return (-1);
	return (check_map_closed(game));
}
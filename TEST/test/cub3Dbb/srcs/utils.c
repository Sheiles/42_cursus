#include "../includes/cub3d.h"

int	is_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0 || map_x >= game->map.width
		|| map_y >= game->map.height)
		return (1);
	if (!game->map.grid || !game->map.grid[map_y])
		return (1);
	if (map_x >= (int)ft_strlen(game->map.grid[map_y]))
		return (1);
	return (game->map.grid[map_y][map_x] == '1');
}

int	check_player_char(t_game *game, int x, int y)
{
	char	c;

	c = game->map.grid[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		game->player.x = x + 0.5;
		game->player.y = y + 0.5;
		if (c == 'N')
			game->player.angle = 3 * M_PI / 2;
		else if (c == 'S')
			game->player.angle = M_PI / 2;
		else if (c == 'E')
			game->player.angle = 0;
		else
			game->player.angle = M_PI;
		return (1);
	}
	return (0);
}

void free_map_grid(t_game *game)
{
	if (!game->map.grid)
		return;
	for (int i = 0; i < game->map.height; i++)
	{
		free(game->map.grid[i]);
	}
	free(game->map.grid);
	game->map.grid = NULL;
}

void free_textures(t_game *game)
{
	free(game->no_texture.path);
	game->no_texture.path = NULL;
	free(game->so_texture.path);
	game->so_texture.path = NULL;
	free(game->we_texture.path);
	game->we_texture.path = NULL;
	free(game->ea_texture.path);
	game->ea_texture.path = NULL;
}

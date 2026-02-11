#include "../includes/cub3d.h"

void	init_game(t_game *game)
{
	game->width = WINDOW_WIDTH;
	game->height = WINDOW_HEIGHT;
	game->player.fov = FOV;
	game->player.x = 0;
	game->player.y = 0;
	game->player.angle = 0;
	game->floor_color.r = 0;
	game->floor_color.g = 0;
	game->floor_color.b = 0;
	game->ceiling_color.r = 0;
	game->ceiling_color.g = 0;
	game->ceiling_color.b = 0;
}

void	cleanup_game(t_game *game)
{
	int	i;

	if (game->map.grid)
	{
		i = 0;
		while (i < game->map.height)
		{
			free(game->map.grid[i]);
			i++;
		}
		free(game->map.grid);
	}
	if (game->no_texture.path)
		free(game->no_texture.path);
	if (game->so_texture.path)
		free(game->so_texture.path);
	if (game->we_texture.path)
		free(game->we_texture.path);
	if (game->ea_texture.path)
		free(game->ea_texture.path);
	if (game->img && game->mlx)
		mlx_destroy_image(game->mlx, game->img);
	if (game->window && game->mlx)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

void	error_exit(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

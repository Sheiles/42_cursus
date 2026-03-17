











#include "../includes/cub3d.h"

static int	load_texture(t_game *game, t_texture *tex)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, tex->path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (-1);
	tex->data = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_length, &tex->endian);
	if (!tex->data)
		return (-1);
	return (0);
}

int	load_textures(t_game *game)
{
	if (!game->no_texture.path || !game->so_texture.path
		|| !game->we_texture.path || !game->ea_texture.path)
		return (-1);
	if (load_texture(game, &game->no_texture) == -1)
		return (-1);
	if (load_texture(game, &game->so_texture) == -1)
		return (-1);
	if (load_texture(game, &game->we_texture) == -1)
		return (-1);
	if (load_texture(game, &game->ea_texture) == -1)
		return (-1);
	return (0);
}

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

static void	cleanup_textures(t_game *game)
{
	if (game->no_texture.img && game->mlx)
		mlx_destroy_image(game->mlx, game->no_texture.img);
	if (game->so_texture.img && game->mlx)
		mlx_destroy_image(game->mlx, game->so_texture.img);
	if (game->we_texture.img && game->mlx)
		mlx_destroy_image(game->mlx, game->we_texture.img);
	if (game->ea_texture.img && game->mlx)
		mlx_destroy_image(game->mlx, game->ea_texture.img);
	if (game->no_texture.path)
		free(game->no_texture.path);
	if (game->so_texture.path)
		free(game->so_texture.path);
	if (game->we_texture.path)
		free(game->we_texture.path);
	if (game->ea_texture.path)
		free(game->ea_texture.path);
}

static void	cleanup_mlx(t_game *game)
{
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
	cleanup_textures(game);
	cleanup_mlx(game);
}

void	error_exit(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

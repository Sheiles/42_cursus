#include "../includes/cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < game->width && y >= 0 && y < game->height)
	{
		pixel = game->img_data + (y * game->line_length + x * (game->bpp / 8));
		*(unsigned int *)pixel = color;
	}
}

int	get_color_from_texture(t_texture *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->data + (y * tex->line_length + x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

void	draw_wall_slice(t_game *game, int x, double distance, int wall_dir)
{
	int		wall_height;
	int		y;
	int		color;
	double	start_y;

	if (distance < 0.1)
		distance = 0.1;
	wall_height = (int)((game->height / distance) * 0.5);
	if (wall_height > game->height)
		wall_height = game->height;
	start_y = (game->height - wall_height) / 2.0;
	y = 0;
	while (y < game->height)
	{
		if (y < (int)start_y)
			color = (game->ceiling_color.r << 16) 
				| (game->ceiling_color.g << 8) | game->ceiling_color.b;
		else if (y >= (int)start_y + wall_height)
			color = (game->floor_color.r << 16) 
				| (game->floor_color.g << 8) | game->floor_color.b;
		else
			color = 0xFF0000;
		put_pixel(game, x, y, color);
		y++;
	}
}

void	render_frame(t_game *game)
{
	raycaster(game);
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
}

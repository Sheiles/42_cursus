#include "../includes/cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	int	pixel;

	if (x < 0 || x >= game->width || y < 0 || y >= game->height)
		return ;
	pixel = (y * game->line_length) + (x * (game->bpp / 8));
	if (game->endian == 0)
	{
		game->img_data[pixel + 0] = (color) & 0xFF;
		game->img_data[pixel + 1] = (color >> 8) & 0xFF;
		game->img_data[pixel + 2] = (color >> 16) & 0xFF;
	}
	else
	{
		game->img_data[pixel + 0] = (color >> 16) & 0xFF;
		game->img_data[pixel + 1] = (color >> 8) & 0xFF;
		game->img_data[pixel + 2] = (color) & 0xFF;
	}
}

int	get_color_from_texture(t_texture *tex, int x, int y)
{
	int	pixel;
	int	color;

	if (!tex || !tex->data || x < 0 || x >= tex->width
		|| y < 0 || y >= tex->height)
		return (0);
	pixel = (y * tex->line_length) + (x * (tex->bpp / 8));
	color = *(int *)(tex->data + pixel);
	return (color);
}

static int	get_slice_color(t_game *game, int y, int start, int end)
{
	int	color;

	if (y < start)
		color = (game->ceiling_color.r << 16)
			| (game->ceiling_color.g << 8) | game->ceiling_color.b;
	else if (y >= start && y < end)
		color = 0x808080;
	else
		color = (game->floor_color.r << 16)
			| (game->floor_color.g << 8) | game->floor_color.b;
	return (color);
}

static void	draw_textured_slice(t_game *game, int x, t_ray *ray,
		int wall_start, int wall_end)
{
	t_texture	*tex;
	int			clipped_start;
	int			clipped_end;
	double		step;
	double		tex_pos;
	int			tex_y;
	int			y;

	tex = get_wall_texture(game, ray->wall_direction);
	step = (double)tex->height / (wall_end - wall_start);
	tex_pos = (wall_start - (game->height / 2)
			+ ((wall_end - wall_start) / 2)) * step;
	clipped_start = wall_start < 0 ? 0 : wall_start;
	clipped_end = wall_end > game->height ? game->height : wall_end;
	tex_pos += (clipped_start - wall_start) * step;
	y = 0;
	while (y < game->height)
	{
		if (y < clipped_start || y >= clipped_end)
			put_pixel(game, x, y,
				get_slice_color(game, y, wall_start, wall_end));
		else
		{
			tex_y = (int)tex_pos;
			if (tex_y < 0)
				tex_y = 0;
			if (tex_y >= tex->height)
				tex_y = tex->height - 1;
			put_pixel(game, x, y, get_color_from_texture(tex,
					get_tex_x(tex, ray), tex_y));
			tex_pos += step;
		}
		y++;
	}
}

void	draw_wall_slice(t_game *game, int x, t_ray *ray)
{
	t_texture	*tex;
	int			wall_height;
	int			wall_start;
	int			wall_end;
	int			y;

	if (ray->distance < 0.1)
		ray->distance = 0.1;
	wall_height = (int)(game->height / ray->distance);
	wall_start = (game->height - wall_height) / 2;
	wall_end = wall_start + wall_height;
	tex = get_wall_texture(game, ray->wall_direction);
	if (!tex || !tex->data || tex->width <= 0 || tex->height <= 0)
	{
		y = 0;
		while (y < game->height)
		{
			put_pixel(game, x, y,
				get_slice_color(game, y, wall_start, wall_end));
			y++;
		}
		return ;
	}
	draw_textured_slice(game, x, ray, wall_start, wall_end);
}

int	render_frame(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	raycaster(game);
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	return (0);
}
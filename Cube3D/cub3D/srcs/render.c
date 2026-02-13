/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 00:00:00 by sheiles           #+#    #+#             */
/*   Updated: 2026/02/12 00:00:00 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	draw_wall_slice(t_game *game, int x, double distance, int wall_dir)
{
	int	y;
	int	wall_height;
	int	wall_start;
	int	wall_end;

	if (distance < 0.1)
		distance = 0.1;
	wall_height = (int)(game->height / distance);
	wall_start = (game->height - wall_height) / 2;
	wall_end = wall_start + wall_height;
	y = 0;
	while (y < game->height)
	{
		put_pixel(game, x, y, get_slice_color(game, y, wall_start, wall_end));
		y++;
	}
	(void)wall_dir;
}

int	render_frame(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	raycaster(game);
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	return (0);
}

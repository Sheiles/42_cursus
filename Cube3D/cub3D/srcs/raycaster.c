/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 18:20:35 by sheiles           #+#    #+#             */
/*   Updated: 2026/02/11 19:57:05 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	cast_ray(t_game *game, double angle)
{
	double	ray_x;
	double	ray_y;
	double	distance;
	double	step_x;
	double	step_y;

	ray_x = game->player.x;
	ray_y = game->player.y;
	step_x = cos(angle) * 0.1;
	step_y = sin(angle) * 0.1;
	distance = 0;
	while (!is_wall(game, ray_x, ray_y))
	{
		ray_x += step_x;
		ray_y += step_y;
		distance += 0.1;
	}
	return (distance);
}

int	get_wall_direction(t_game *game, double hit_x, double hit_y)
{
	double	dx;
	double	dy;

	dx = hit_x - game->player.x;
	dy = hit_y - game->player.y;
	if (fabs(dx) > fabs(dy))
	{
		if (dx > 0)
			return (3);
		return (2);
	}
	if (dy > 0)
		return (1);
	return (0);
}

void	raycaster(t_game *game)
{
	int		x;
	double	ray_angle;
	double	distance;
	double	fov_rad;

	fov_rad = (game->player.fov * M_PI) / 180.0;
	x = 0;
	while (x < game->width)
	{
		ray_angle = game->player.angle - (fov_rad / 2.0)
			+ ((double)x / game->width) * fov_rad;
		distance = cast_ray(game, ray_angle);
		distance *= cos(ray_angle - game->player.angle);
		draw_wall_slice(game, x, distance, 0);
		x++;
	}
}

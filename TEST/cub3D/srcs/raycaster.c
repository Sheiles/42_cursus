











#include "../includes/cub3d.h"

static int	get_wall_direction_from_hit(double hit_x, double hit_y)

{
	double	frac_x;
	double	frac_y;
	double	to_west;
	double	to_east;
	double	to_north;
	double	to_south;

	frac_x = hit_x - floor(hit_x);
	frac_y = hit_y - floor(hit_y);
	to_west = frac_x;
	to_east = 1.0 - frac_x;
	to_north = frac_y;
	to_south = 1.0 - frac_y;
	if (to_west <= to_east && to_west <= to_north && to_west <= to_south)
		return (WALL_WEST);
	if (to_east <= to_west && to_east <= to_north && to_east <= to_south)
		return (WALL_EAST);
	if (to_north <= to_west && to_north <= to_east && to_north <= to_south)
		return (WALL_NORTH);
	return (WALL_SOUTH);
}

double	cast_ray(t_game *game, double angle, t_ray *ray)
{
	double	ray_x;
	double	ray_y;
	double	prev_x;
	double	prev_y;
	double	distance;
	double	step_x;
	double	step_y;

	ray_x = game->player.x;
	ray_y = game->player.y;
	prev_x = ray_x;
	prev_y = ray_y;
	step_x = cos(angle) * 0.01;
	step_y = sin(angle) * 0.01;
	distance = 0;
	while (!is_wall(game, ray_x, ray_y) && distance < 100.0)
	{
		prev_x = ray_x;
		prev_y = ray_y;
		ray_x += step_x;
		ray_y += step_y;
		distance += 0.01;
	}
	ray->x = prev_x;
	ray->y = prev_y;
	ray->angle = angle;
	ray->wall_direction = get_wall_direction(game, ray->x, ray->y);
	return (distance);
}

int	get_wall_direction(t_game *game, double hit_x, double hit_y)
{
	(void)game;
	return (get_wall_direction_from_hit(hit_x, hit_y));
}

void	raycaster(t_game *game)
{
	int		x;
	double	ray_angle;
	t_ray	ray;
	double	raw_distance;
	double	fov_rad;

	fov_rad = (game->player.fov * M_PI) / 180.0;
	x = 0;
	while (x < game->width)
	{
		ray_angle = game->player.angle - (fov_rad / 2.0)
			+ ((double)x / game->width) * fov_rad;
		raw_distance = cast_ray(game, ray_angle, &ray);
		ray.distance = raw_distance * cos(ray_angle - game->player.angle);
		draw_wall_slice(game, x, &ray);
		x++;
	}
}

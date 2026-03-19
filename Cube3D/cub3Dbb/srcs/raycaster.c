











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
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		hit_side;
	double	distance;

	ray_dir_x = cos(angle);
	ray_dir_y = sin(angle);
	map_x = (int)game->player.x;
	map_y = (int)game->player.y;
	delta_dist_x = 1e30;
	delta_dist_y = 1e30;
	if (ray_dir_x != 0.0)
		delta_dist_x = fabs(1.0 / ray_dir_x);
	if (ray_dir_y != 0.0)
		delta_dist_y = fabs(1.0 / ray_dir_y);
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (game->player.x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - game->player.x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (game->player.y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - game->player.y) * delta_dist_y;
	}
	hit_side = 0;
	while (1)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			hit_side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			hit_side = 1;
		}
		if (is_wall(game, map_x + 0.5, map_y + 0.5))
			break ;
	}
	if (hit_side == 0)
		distance = (map_x - game->player.x + (1 - step_x) / 2.0) / ray_dir_x;
	else
		distance = (map_y - game->player.y + (1 - step_y) / 2.0) / ray_dir_y;
	if (distance < 0)
		distance = -distance;
	ray->x = game->player.x + distance * ray_dir_x;
	ray->y = game->player.y + distance * ray_dir_y;
	ray->angle = angle;
	if (hit_side == 0)
	{
		if (step_x > 0)
			ray->wall_direction = WALL_WEST;
		else
			ray->wall_direction = WALL_EAST;
	}
	else
	{
		if (step_y > 0)
			ray->wall_direction = WALL_NORTH;
		else
			ray->wall_direction = WALL_SOUTH;
	}
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
	double	tan_half_fov;
	double	camera_x;
	double	ray_offset;

	fov_rad = (game->player.fov * M_PI) / 180.0;
	tan_half_fov = tan(fov_rad / 2.0);
	x = 0;
	while (x < game->width)
	{
		camera_x = (2.0 * (x + 0.5) / game->width) - 1.0;
		ray_offset = atan(camera_x * tan_half_fov);
		ray_angle = game->player.angle + ray_offset;
		raw_distance = cast_ray(game, ray_angle, &ray);
		ray.distance = raw_distance * cos(ray_offset);
		draw_wall_slice(game, x, &ray);
		x++;
	}
}

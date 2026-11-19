#include "../includes/cub3d.h"

t_texture	*get_wall_texture(t_game *game, int wall_dir)
{
	if (wall_dir == WALL_NORTH)
		return (&game->no_texture);
	if (wall_dir == WALL_SOUTH)
		return (&game->so_texture);
	if (wall_dir == WALL_WEST)
		return (&game->we_texture);
	return (&game->ea_texture);
}

int	get_tex_x(t_texture *tex, t_ray *ray)
{
	double	wall_pos;
	int		tex_x;

	if (ray->wall_direction == WALL_NORTH || ray->wall_direction == WALL_SOUTH)
		wall_pos = ray->x - floor(ray->x);
	else
		wall_pos = ray->y - floor(ray->y);
	tex_x = (int)(wall_pos * tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	if (ray->wall_direction == WALL_EAST || ray->wall_direction == WALL_NORTH)
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}
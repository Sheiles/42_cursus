











#include "so_long.h"

static void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			mlx_put_image_to_window(game->mlx, game->win,
				game->img.floor, x * TILE_SIZE, y * TILE_SIZE);
			draw_tile(game, x, y);
			x++;
		}
		y++;
	}
}

void	render_map(t_game *game)
{
	game->frame++;
	draw_background(game);
	draw_player(game, game->player_x, game->player_y);
}

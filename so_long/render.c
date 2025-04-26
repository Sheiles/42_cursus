#include "so_long.h"
static void	draw_key(t_game *game, int x, int y)
{
	int offset = (game->frame / 15) % 2 == 0 ? 0 : 5;
	if ((game->frame / 30) % 2 == 0)
		mlx_put_image_to_window(game->mlx, game->win, game->img.key[0], x * TILE_SIZE, y * TILE_SIZE + offset);
	else
		mlx_put_image_to_window(game->mlx, game->win, game->img.key[1], x * TILE_SIZE, y * TILE_SIZE + offset);
}

static void	draw_exit(t_game *game, int x, int y)
{
	if ((game->frame / 30) % 2 == 0)
		mlx_put_image_to_window(game->mlx, game->win, game->img.exit[0], x * TILE_SIZE, y * TILE_SIZE);
	else
		mlx_put_image_to_window(game->mlx, game->win, game->img.exit[1], x * TILE_SIZE, y * TILE_SIZE);
}

static void	draw_player(t_game *game, int x, int y)
{
	if (game->last_dir == 'L')
		mlx_put_image_to_window(game->mlx, game->win, game->img.player_left, x * TILE_SIZE, y * TILE_SIZE);
	else
		mlx_put_image_to_window(game->mlx, game->win, game->img.player_right, x * TILE_SIZE, y * TILE_SIZE);
}

static void	draw_tile(t_game *game, int x, int y)
{
	if (game->map[y][x] == WALL)
		mlx_put_image_to_window(game->mlx, game->win, game->img.wall, x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map[y][x] == FLOOR)
		mlx_put_image_to_window(game->mlx, game->win, game->img.floor, x * TILE_SIZE, y * TILE_SIZE);
	else if (game->map[y][x] == KEY)
		draw_key(game, x, y);
	else if (game->map[y][x] == EXIT)
		draw_exit(game, x, y);
	else if (game->map[y][x] == PLAYER)
		draw_player(game, x, y);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	game->frame++;
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			draw_tile(game, x, y);
			x++;
		}
		y++;
	}
}

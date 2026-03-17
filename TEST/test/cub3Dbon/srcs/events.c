











#include "../includes/cub3d.h"

int	close_window(t_game *game)
{
	cleanup_game(game);
	exit(EXIT_SUCCESS);
	return (0);
}

static void	handle_movement(int key, t_game *game)
{
	if (key == KEY_W)
	{
		game->player.x += cos(game->player.angle) * MOVE_SPEED;
		game->player.y += sin(game->player.angle) * MOVE_SPEED;
	}
	if (key == KEY_S)
	{
		game->player.x -= cos(game->player.angle) * MOVE_SPEED;
		game->player.y -= sin(game->player.angle) * MOVE_SPEED;
	}
	if (key == KEY_A)
	{
		game->player.x += cos(game->player.angle - M_PI / 2) * MOVE_SPEED;
		game->player.y += sin(game->player.angle - M_PI / 2) * MOVE_SPEED;
	}
	if (key == KEY_D)
	{
		game->player.x += cos(game->player.angle + M_PI / 2) * MOVE_SPEED;
		game->player.y += sin(game->player.angle + M_PI / 2) * MOVE_SPEED;
	}
}

static void	handle_rotation(int key, t_game *game)
{
	if (key == KEY_LEFT)
		game->player.angle -= ROTATION_SPEED;
	if (key == KEY_RIGHT)
		game->player.angle += ROTATION_SPEED;
}

int	key_press(int key, t_game *game)
{
	if (key == KEY_ESC)
		close_window(game);
	handle_movement(key, game);
	handle_rotation(key, game);
	return (0);
}

int	key_release(int key, t_game *game)
{
	(void)key;
	(void)game;
	return (0);
}

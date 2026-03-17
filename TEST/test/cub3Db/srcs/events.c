











#include "../includes/cub3d.h"

static int	can_move_to(t_game *game, double x, double y)
{
	if (is_wall(game, x, y))
		return (0);
	if (is_wall(game, x + COLLISION_RADIUS, y + COLLISION_RADIUS))
		return (0);
	if (is_wall(game, x + COLLISION_RADIUS, y - COLLISION_RADIUS))
		return (0);
	if (is_wall(game, x - COLLISION_RADIUS, y + COLLISION_RADIUS))
		return (0);
	if (is_wall(game, x - COLLISION_RADIUS, y - COLLISION_RADIUS))
		return (0);
	return (1);
}

static void	move_player(t_game *game, double dx, double dy)
{
	int		steps;
	int		i;
	double	step_x;
	double	step_y;
	double	next_x;
	double	next_y;
	double	max_delta;

	max_delta = fabs(dx);
	if (fabs(dy) > max_delta)
		max_delta = fabs(dy);
	steps = (int)ceil(max_delta / COLLISION_STEP);
	if (steps < 1)
		steps = 1;
	step_x = dx / steps;
	step_y = dy / steps;
	i = 0;
	while (i < steps)
	{
		next_x = game->player.x + step_x;
		next_y = game->player.y + step_y;
		if (can_move_to(game, next_x, game->player.y))
			game->player.x = next_x;
		if (can_move_to(game, game->player.x, next_y))
			game->player.y = next_y;
		i++;
	}
}

int	close_window(t_game *game)
{
	cleanup_game(game);
	exit(EXIT_SUCCESS);
	return (0);
}

static void	handle_movement(int key, t_game *game)
{
	if (key == KEY_W)
		move_player(game, cos(game->player.angle) * MOVE_SPEED,
			sin(game->player.angle) * MOVE_SPEED);
	if (key == KEY_S)
		move_player(game, -cos(game->player.angle) * MOVE_SPEED,
			-sin(game->player.angle) * MOVE_SPEED);
	if (key == KEY_A)
		move_player(game, cos(game->player.angle - M_PI / 2) * MOVE_SPEED,
			sin(game->player.angle - M_PI / 2) * MOVE_SPEED);
	if (key == KEY_D)
		move_player(game, cos(game->player.angle + M_PI / 2) * MOVE_SPEED,
			sin(game->player.angle + M_PI / 2) * MOVE_SPEED);
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

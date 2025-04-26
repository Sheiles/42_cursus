
#include "so_long.h"

static void move_player(t_game *game, int new_x, int new_y)
{
	if (game->map[new_y][new_x] == WALL)
		return;
	if (game->map[new_y][new_x] == KEY)
		game->keys--;
if (game->map[new_y][new_x] == EXIT)
{
	if (game->keys == 0)
	{
		printf("GG, tu as gagné !\n");
		handle_exit(game);
	}
	else
		return;
}

	game->map[game->player_y][game->player_x] = FLOOR;
	game->player_x = new_x;
	game->player_y = new_y;
	game->map[game->player_y][game->player_x] = PLAYER;
	game->moves++;
	printf("Moves: %d\n", game->moves);
	render_map(game);
}

int handle_key(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		handle_exit(game);
	else if (keycode == KEY_W)
		move_player(game, game->player_x, game->player_y - 1);
	else if (keycode == KEY_S)
		move_player(game, game->player_x, game->player_y + 1);
	else if (keycode == KEY_A)
	{
		game->last_dir = 'L'; // ➔ gauche
		move_player(game, game->player_x - 1, game->player_y);
	}
	else if (keycode == KEY_D)
	{
		game->last_dir = 'R'; // ➔ droite
		move_player(game, game->player_x + 1, game->player_y);
	}
	return (0);
}




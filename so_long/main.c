
#include "so_long.h"

int	error(char *msg)
{
	sl_putstr_fd("Error\n", 2);
	sl_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

void	game_init(t_game *game, char *mapfile)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error("MLX init failed");
	load_map(game, mapfile);
	game->win = mlx_new_window(game->mlx, game->width * TILE_SIZE, game->height * TILE_SIZE, "Knight Quest");
	if (!game->win)
		error("Window creation failed");
	load_images(game);
	render_map(game);
	mlx_key_hook(game->win, handle_key, game);
	mlx_hook(game->win, 17, 0, handle_exit, game);
	gettimeofday(&game->start_time, NULL);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		error("Usage: ./so_long <map.ber>");
	game_init(&game, argv[1]);
	return (0);
}

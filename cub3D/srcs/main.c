#include "../includes/cub3d.h"

int	close_window(t_game *game)
{
	cleanup_game(game);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_press(int key, t_game *game)
{
	if (key == KEY_ESC)
		close_window(game);
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
	if (key == KEY_LEFT)
		game->player.angle -= ROTATION_SPEED;
	if (key == KEY_RIGHT)
		game->player.angle += ROTATION_SPEED;
	return (0);
}

int	key_release(int key, t_game *game)
{
	(void)key;
	(void)game;
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Error\nUsage: ./cub3D <map.cub>\n");
		exit(EXIT_FAILURE);
	}
	ft_memset(&game, 0, sizeof(t_game));
	init_game(&game);
	if (parse_cub_file(argv[1], &game) == -1)
	{
		printf("Error\nFailed to parse map file\n");
		exit(EXIT_FAILURE);
	}
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		printf("Error\nFailed to initialize MLX\n");
		exit(EXIT_FAILURE);
	}
	game.window = mlx_new_window(game.mlx, game.width, game.height, "cub3D");
	if (!game.window)
	{
		printf("Error\nFailed to create window\n");
		exit(EXIT_FAILURE);
	}
	game.img = mlx_new_image(game.mlx, game.width, game.height);
	game.img_data = mlx_get_data_addr(game.img, &game.bpp, 
		&game.line_length, &game.endian);
	mlx_hook(game.window, 2, 1L << 0, key_press, &game);
	mlx_hook(game.window, 3, 1L << 1, key_release, &game);
	mlx_hook(game.window, 17, 0, close_window, &game);
	mlx_loop_hook(game.mlx, (int (*)())render_frame, &game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}

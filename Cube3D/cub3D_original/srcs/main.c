/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 18:20:13 by sheiles           #+#    #+#             */
/*   Updated: 2026/02/11 19:57:05 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("Error\nFailed to initialize MLX\n");
		exit(EXIT_FAILURE);
	}
	game->window = mlx_new_window(game->mlx, game->width,
			game->height, "cub3D");
	if (!game->window)
	{
		printf("Error\nFailed to create window\n");
		exit(EXIT_FAILURE);
	}
	game->img = mlx_new_image(game->mlx, game->width, game->height);
	game->img_data = mlx_get_data_addr(game->img, &game->bpp,
			&game->line_length, &game->endian);
	return (0);
}

static void	setup_hooks(t_game *game)
{
	mlx_hook(game->window, 2, 1L << 0, key_press, game);
	mlx_hook(game->window, 3, 1L << 1, key_release, game);
	mlx_hook(game->window, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx, (int (*)())render_frame, game);
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
	init_mlx(&game);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:19:53 by sheiles           #+#    #+#             */
/*   Updated: 2025/02/11 11:42:36 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"
#include "../minilibx-linux/mlx.h"

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	free_map(game->map);
	exit(0);
	return (0);
}

int	main(void)
{
	t_game game;
	/*int tile_width = TILE_SIZE;
	int tile_height = TILE_SIZE;*/

	game.mlx = mlx_init();
	load_textures(&game);
	game.win = mlx_new_window(game.mlx, 800, 600, "So Long");
	mlx_key_hook(game.win, handle_key, &game);
	mlx_loop(game.mlx);
	
	
	
	
	
	/*if (!game.mlx)
	{
		ft_putstr_fd("Error initializing MLX\n", 2);
		return (1);
	}
	if (!game.win)
	{
		ft_putstr_fd("Error creating window\n", 2);
		return (1);
	}
	game.wall_img = mlx_xpm_file_to_image(game.mlx, XPM_WALL,
			&tile_width, &tile_height);
	if (!game.wall_img)
	{
		ft_putstr_fd("Error loading wall.xpm\n", 2);
		return (1);
	}
	game.player_img = mlx_xpm_file_to_image(game.mlx, "./textures/player.xpm",
			&tile_width, &tile_height);
	if (!game.player_img)
	{
		ft_putstr_fd("Error loading player.xpm\n", 2);
		return (1);
	}
	game.collectible_img = mlx_xpm_file_to_image(game.mlx,
			"./textures/collectible.xpm", &tile_width, &tile_height);
	if (!game.collectible_img)
	{
		ft_putstr_fd("Error loading collectible.xpm\n", 2);
		return (1);
	}
	game.exit_img = mlx_xpm_file_to_image(game.mlx, "./textures/exit.xpm",
			&tile_width, &tile_height);
	if (!game.exit_img)
	{
		ft_putstr_fd("Error loading exit.xpm\n", 2);
		return (1);
	}
	game.empty_img = mlx_xpm_file_to_image(game.mlx, "./textures/empty.xpm",
			&tile_width, &tile_height);
	if (!game.empty_img)
	{
		ft_putstr_fd("Error loading empty.xpm\n", 2);
		return (1);
	}
	return (0);*/
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:19:53 by sheiles           #+#    #+#             */
/*   Updated: 2025/01/28 11:51:37 by sheiles          ###   ########.fr       */
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
	int tile_width = TILE_SIZE;
	int tile_height = TILE_SIZE;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 800, 600, "So Long");

	game.wall_img = mlx_xpm_file_to_image(game.mlx, "textures/wall.xpm",
			&tile_width, &tile_height);
	game.player_img = mlx_xpm_file_to_image(game.mlx, "textures/player.xpm",
			&tile_width, &tile_height);
	game.collectible_img = mlx_xpm_file_to_image(game.mlx,
			"textures/collectible.xpm", &tile_width, &tile_height);
	game.exit_img = mlx_xpm_file_to_image(game.mlx, "textures/exit.xpm",
			&tile_width, &tile_height);
	game.empty_img = mlx_xpm_file_to_image(game.mlx, "textures/empty.xpm",
			&tile_width, &tile_height);

	// Check for errors loading images
/*	if (!game.wall_img || !game.player_img || !game.collectible_img
		|| !game.exit_img || !game.empty_img)
	{
		ft_putstr_fd("Error loading textures\n", 2);
		return (1);
	}
*/
	// Other game initialization...

	return (0);
}
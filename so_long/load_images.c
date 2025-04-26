/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:32:47 by sheiles           #+#    #+#             */
/*   Updated: 2025/04/26 18:32:49 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void load_images(t_game *game)
{
	int size = TILE_SIZE;

	game->img.wall = mlx_xpm_file_to_image(game->mlx, "assets/wall.xpm", &size, &size);
	game->img.floor = mlx_xpm_file_to_image(game->mlx, "assets/floor.xpm", &size, &size);
	game->img.key[0] = mlx_xpm_file_to_image(game->mlx, "assets/key1.xpm", &size, &size);
	game->img.key[1] = mlx_xpm_file_to_image(game->mlx, "assets/key2.xpm", &size, &size);
	game->img.exit[0] = mlx_xpm_file_to_image(game->mlx, "assets/exit1.xpm", &size, &size);
	game->img.exit[1] = mlx_xpm_file_to_image(game->mlx, "assets/exit2.xpm", &size, &size);
	game->img.player_right = mlx_xpm_file_to_image(game->mlx, "assets/player_right.xpm", &size, &size);
	game->img.player_left = mlx_xpm_file_to_image(game->mlx, "assets/player_left.xpm", &size, &size);
	if (!game->img.wall || !game->img.floor || !game->img.key[0] || !game->img.key[1]
		|| !game->img.exit[0] || !game->img.exit[1] || !game->img.player_right || !game->img.player_left)
		error("Failed to load one or more textures");
}


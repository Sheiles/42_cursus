/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:19:18 by sheiles           #+#    #+#             */
/*   Updated: 2025/01/24 11:03:19 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	load_textures(t_game *game)
{
	int	size;

	size = TILE_SIZE;
	game->wall_img = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm",
			&size, &size);
	game->player_img = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm",
			&size, &size);
	game->collectible_img = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible.xpm", &size, &size);
	game->exit_img = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm",
			&size, &size);
	game->empty_img = mlx_xpm_file_to_image(game->mlx, "textures/empty.xpm",
			&size, &size);
	if (!game->wall_img || !game->player_img || !game->collectible_img
		|| !game->exit_img || !game->empty_img)
		error_exit("Failed to load textures");
}

void	render_map(t_game *game)
{
	void	*img;

	int x, y;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			img = NULL;
			if (game->map[y][x] == '1')
				img = game->wall_img;
			else if (game->map[y][x] == '0')
				img = game->empty_img;
			else if (game->map[y][x] == 'C')
				img = game->collectible_img;
			else if (game->map[y][x] == 'E')
				img = game->exit_img;
			else if (game->map[y][x] == 'P')
				img = game->player_img;
			if (img)
				mlx_put_image_to_window(game->mlx, game->win, img, x
					* TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

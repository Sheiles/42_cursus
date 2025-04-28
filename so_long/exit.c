/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:32:34 by sheiles           #+#    #+#             */
/*   Updated: 2025/04/27 21:14:22 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <sys/time.h>

void	destroy_images(t_game *game)
{
	if (game->img.wall)
		mlx_destroy_image(game->mlx, game->img.wall);
	if (game->img.floor)
		mlx_destroy_image(game->mlx, game->img.floor);
	if (game->img.key[0])
		mlx_destroy_image(game->mlx, game->img.key[0]);
	if (game->img.key[1])
		mlx_destroy_image(game->mlx, game->img.key[1]);
	if (game->img.exit[0])
		mlx_destroy_image(game->mlx, game->img.exit[0]);
	if (game->img.exit[1])
		mlx_destroy_image(game->mlx, game->img.exit[1]);
	if (game->img.player_left)
		mlx_destroy_image(game->mlx, game->img.player_left);
	if (game->img.player_right)
		mlx_destroy_image(game->mlx, game->img.player_right);
}

int	handle_exit(t_game *game)
{
	ft_printf("Total moves: %d\n", game->moves);
	destroy_images(game);
	free_map(game);
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}

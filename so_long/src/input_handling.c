/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:19:22 by sheiles           #+#    #+#             */
/*   Updated: 2025/01/22 16:14:59 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"
#include "../minilibx-linux/mlx.h"

int	handle_key(int key, t_game *game)
{
	if (key == KEY_ESC)
		close_window(game);
	else if (key == KEY_W)
		move_player(game, 0, -1);
	else if (key == KEY_A)
		move_player(game, -1, 0);
	else if (key == KEY_S)
		move_player(game, 0, 1);
	else if (key == KEY_D)
		move_player(game, 1, 0);
	return (0);
}

void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	if (game->map[new_y][new_x] == '1') // Wall
		return ;
	if (game->map[new_y][new_x] == 'C') // Collectible
		game->collectible_count--;
	if (game->map[new_y][new_x] == 'E' && game->collectible_count == 0) // Exit
		close_window(game);
	// Update player position
	game->map[game->player_y][game->player_x] = '0';
		// Replace old position with empty space
	game->map[new_y][new_x] = 'P';                  
		// Place player in the new position
	game->player_x = new_x;                         
		// Update player's x-coordinate
	game->player_y = new_y;                         
		// Update player's y-coordinate
}

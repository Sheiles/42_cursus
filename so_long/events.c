/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:32:30 by sheiles           #+#    #+#             */
/*   Updated: 2025/04/27 21:14:14 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_key(t_game *game)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == KEY)
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	move_player(t_game *game, int new_x, int new_y)
{
	char	next_tile;

	next_tile = game->map[new_y][new_x];
	if (next_tile == WALL)
		return ;
	if (next_tile == KEY)
		game->keys--;
	if (next_tile == EXIT)
	{
		if (count_key(game) == 0)
		{
			ft_printf("GG, tu as gagné !\n");
			handle_exit(game);
		}
		else
			return ;
	}
	game->map[game->player_y][game->player_x] = FLOOR;
	game->player_x = new_x;
	game->player_y = new_y;
	game->map[game->player_y][game->player_x] = PLAYER;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
	render_map(game);
}

int	handle_key(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		handle_exit(game);
	else if (keycode == KEY_W)
		move_player(game, game->player_x, game->player_y - 1);
	else if (keycode == KEY_S)
		move_player(game, game->player_x, game->player_y + 1);
	else if (keycode == KEY_A)
	{
		game->last_dir = 'L';
		move_player(game, game->player_x - 1, game->player_y);
	}
	else if (keycode == KEY_D)
	{
		game->last_dir = 'R';
		move_player(game, game->player_x + 1, game->player_y);
	}
	return (0);
}

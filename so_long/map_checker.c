/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:32:21 by sheiles           #+#    #+#             */
/*   Updated: 2025/04/26 20:19:04 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_valid_tile(char c)
{
	return (c == WALL || c == FLOOR || c == PLAYER || c == KEY || c == EXIT);
}

static int	check_walls(t_game *game, int i, int j)
{
	if (i == 0 || j == 0 || i == game->height - 1 || j == game->width - 1)
	{
		if (game->map[i][j] != WALL)
			return (0);
	}
	return (1);
}

static int	check_line(t_game *game, int i, int *players, int *exits, int *keys)
{
	int	j;

	j = 0;
	while (j < game->width)
	{
		if (!check_walls(game, i, j))
			return (0);
		if (game->map[i][j] == PLAYER && ++(*players))
		{
			game->player_x = j;
			game->player_y = i;
			game->map[i][j] = FLOOR; // Remplacer P par 0
		}
		else if (game->map[i][j] == EXIT)
			(*exits)++;
		else if (game->map[i][j] == KEY)
			(*keys)++;
		else if (!is_valid_tile(game->map[i][j]))
			return (0);
		j++;
	}
	return (1);
}


int	is_valid_map(t_game *game)
{
	int	i;
	int	exits;
	int	players;
	int	keys;

	i = 0;
	exits = 0;
	players = 0;
	keys = 0;
	while (i < game->height)
	{
		if ((int)sl_strlen(game->map[i]) != game->width)
			return (0);
		if (!check_line(game, i, &players, &exits, &keys))
			return (0);
		i++;
	}
	return (players == 1 && exits == 1 && keys >= 1);
}

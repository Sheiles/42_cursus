/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:32:21 by sheiles           #+#    #+#             */
/*   Updated: 2025/04/27 16:11:54 by sheiles          ###   ########.fr       */
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

static int	check_line(t_game *game, int i, t_count *count)
{
	int	j;

	j = 0;
	while (j < game->width)
	{
		if (!check_walls(game, i, j))
			return (0);
		if (game->map[i][j] == PLAYER)
		{
			count->players++;
			game->player_x = j;
			game->player_y = i;
			game->map[i][j] = FLOOR;
		}
		else if (game->map[i][j] == EXIT)
			count->exits++;
		else if (game->map[i][j] == KEY)
			count->keys++;
		else if (!is_valid_tile(game->map[i][j]))
			return (0);
		j++;
	}
	return (1);
}

int	is_valid_map(t_game *game)
{
	int		i;
	t_count	count;

	i = 0;
	count.players = 0;
	count.exits = 0;
	count.keys = 0;
	while (i < game->height)
	{
		if ((int)sl_strlen(game->map[i]) != game->width)
			return (0);
		if (!check_line(game, i, &count))
			return (0);
		i++;
	}
	return (count.players == 1 && count.exits == 1 && count.keys >= 1);
}

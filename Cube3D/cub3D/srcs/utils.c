/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 00:00:00 by sheiles           #+#    #+#             */
/*   Updated: 2026/02/12 00:00:00 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0 || map_x >= game->map.width
		|| map_y >= game->map.height)
		return (1);
	if (!game->map.grid || !game->map.grid[map_y])
		return (1);
	if (map_x >= (int)ft_strlen(game->map.grid[map_y]))
		return (1);
	return (game->map.grid[map_y][map_x] == '1');
}

int	check_player_char(t_game *game, int x, int y)
{
	char	c;

	c = game->map.grid[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		game->player.x = x + 0.5;
		game->player.y = y + 0.5;
		if (c == 'N')
			game->player.angle = 3 * M_PI / 2;
		else if (c == 'S')
			game->player.angle = M_PI / 2;
		else if (c == 'E')
			game->player.angle = 0;
		else
			game->player.angle = M_PI;
		return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:32:58 by sheiles           #+#    #+#             */
/*   Updated: 2025/04/27 14:06:37 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(char **map, int x, int y)
{
	if (map[y][x] == WALL || map[y][x] == 'X')
		return ;
	map[y][x] = 'X';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

char	**copy_map(char **map, int height)
{
	int		i;
	char	**copy;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = strdup(map[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	check_valid_path(t_game *game)
{
	char	**tmp;
	int		i;
	int		j;
	int		valid;

	valid = 1;
	tmp = copy_map(game->map, game->height);
	if (!tmp)
		return (0);
	flood_fill(tmp, game->player_x, game->player_y);
	i = 0;
	while (tmp[i])
	{
		j = 0;
		while (tmp[i][j])
		{
			if (tmp[i][j] == KEY || tmp[i][j] == EXIT)
				valid = 0;
			j++;
		}
		free(tmp[i++]);
	}
	free(tmp);
	return (valid);
}

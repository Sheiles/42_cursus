/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:19:11 by sheiles           #+#    #+#             */
/*   Updated: 2025/01/24 11:03:15 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	error_exit(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
	exit(EXIT_FAILURE);
}

void	validate_map(t_game *game)
{
	int	player_count;
	int	exit_count;
	int	collectible_count;
	int	y;
	int	x;

	player_count = 0;
	exit_count = 0;
	collectible_count = 0;
	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'P')
				player_count++;
			else if (game->map[y][x] == 'E')
				exit_count++;
			else if (game->map[y][x] == 'C')
				collectible_count++;
			else if (game->map[y][x] != '1' && game->map[y][x] != '0')
				error_exit("Invalid character in map");
			x++;
		}
		y++;
	}
	if (player_count != 1)
		error_exit("Map must contain exactly one player");
	if (exit_count < 1)
		error_exit("Map must contain at least one exit");
	if (collectible_count < 1)
		error_exit("Map must contain at least one collectible");
}

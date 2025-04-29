/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:32:54 by sheiles           #+#    #+#             */
/*   Updated: 2025/04/27 21:12:37 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_game *game)
{
	int		i;

	i = 0;
	while (game->map && game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
}

char	*read_file(char *filename)
{
	int		fd;
	int		ret;
	char	buff[4096];
	char	*content;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error("Cannot open file");
	ret = read(fd, buff, 4095);
	if (ret <= 0)
		error("Cannot read file");
	buff[ret] = '\0';
	content = strdup(buff);
	close(fd);
	return (content);
}

int	load_map(t_game *game, char *filename)
{
	char	*file_content;

	file_content = read_file(filename);
	game->map = sl_split(file_content, '\n');
	free(file_content);
	if (!game->map)
		error("Map loading failed");
	game->height = 0;
	while (game->map[game->height])
		game->height++;
	game->width = sl_strlen(game->map[0]);
	if (!is_valid_map(game))
	{
		free_map(game);
		error("Invalid map");
	}
	if (!check_valid_path(game))
	{
		free_map(game);
		error("No valid path to all keys and exit");
	}
	return (1);
}

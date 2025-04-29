/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:19:57 by sheiles           #+#    #+#             */
/*   Updated: 2025/01/24 11:03:27 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// Check if the map is rectangular
static int	is_rectangular(char **map)
{
	int	width;
	int	i;

	width = ft_strlen(map[0]);
	i = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) != width)
			return (0);
		i++;
	}
	return (1);
}

// Check if the map is surrounded by walls
static int	is_surrounded_by_walls(char **map)
{
	int	width;
	int	height;
	int	x;
	int	y;

	width = ft_strlen(map[0]); // Assume all rows have the same length
	height = 0;
	while (map[height])
		height++;

	// Check top border
	x = 0;
	while (x < width)
	{
		if (map[0][x] != '1')
			return (0);
		x++;
	}

	// Check bottom border
	x = 0;
	while (x < width)
	{
		if (map[height - 1][x] != '1')
			return (0);
		x++;
	}

	// Check left and right borders
	y = 0;
	while (y < height)
	{
		if (map[y][0] != '1' || map[y][width - 1] != '1')
			return (0);
		y++;
	}

	return (1);
}


// Read the map file and split into 2D array
static char	**read_map(const char *file)
{
	int		fd;
	char	*line;
	char	*temp;
	char	*map_str;
	char	**map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open map file");
	map_str = ft_strdup("");
	while ((line = get_next_line(fd)) != NULL)
	{
		temp = map_str;
		map_str = ft_strjoin(map_str, line);
		free(temp);
		free(line);
	}
	close(fd);
	if (!map_str || *map_str == '\0')
		error_exit("Map file is empty or invalid");
	map = ft_split(map_str, '\n');
	free(map_str);
	return (map);
}

// Validate the map for characters and required elements
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
	game->collectible_count = collectible_count;
}

// Parse the map file and validate it
int	parse_map(const char *file, t_game *game)
{
	int	y;

	y = 0;
	// Validate file extension
	if (!ft_strnstr(file + ft_strlen(file) - 4, ".ber", 4))
		error_exit("Invalid map file extension (must be .ber)");
	// Read and validate map
	game->map = read_map(file);
	if (!is_rectangular(game->map))
		error_exit("Map must be rectangular");
	if (!is_surrounded_by_walls(game->map))
		error_exit("Map must be surrounded by walls");
	// Validate characters and count important elements
	validate_map(game);
	// Find the player position
	while (game->map[y])
	{
		for (int x = 0; game->map[y][x]; x++)
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				return (1);
			}
		}
		y++;
	}
	error_exit("Player start position not found");
	return (0);
}

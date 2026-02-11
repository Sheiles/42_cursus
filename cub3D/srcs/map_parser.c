#include "../includes/cub3d.h"

int	validate_map(t_game *game)
{
	int	i;
	int	j;

	if (!game->map.grid)
		return (-1);
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < (int)ft_strlen(game->map.grid[i]))
		{
			if (game->map.grid[i][j] != '0' && game->map.grid[i][j] != '1'
				&& game->map.grid[i][j] != 'N' && game->map.grid[i][j] != 'S'
				&& game->map.grid[i][j] != 'E' && game->map.grid[i][j] != 'W'
				&& game->map.grid[i][j] != ' ')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	parse_map(char *filename, t_game *game, int start_line)
{
	int		fd;
	char	*line;
	int		line_count;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	line_count = 0;
	i = 0;
	while (i < start_line + 10)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (i >= start_line && line[0] != '\n')
			line_count++;
		free(line);
		i++;
	}
	close(fd);
	game->map.height = line_count;
	game->map.grid = (char **)malloc(sizeof(char *) * (line_count + 1));
	if (!game->map.grid)
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	i = 0;
	line_count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (i >= start_line && line[0] != '\n')
		{
			game->map.grid[line_count] = ft_strtrim(line, "\n");
			if (game->map.width < (int)ft_strlen(game->map.grid[line_count]))
				game->map.width = ft_strlen(game->map.grid[line_count]);
			line_count++;
		}
		free(line);
		i++;
	}
	game->map.grid[line_count] = NULL;
	close(fd);
	return (0);
}

int	is_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0 || map_y >= game->map.height
		|| map_x >= game->map.width)
		return (1);
	if (map_x >= (int)ft_strlen(game->map.grid[map_y]))
		return (1);
	if (game->map.grid[map_y][map_x] == '1')
		return (1);
	return (0);
}

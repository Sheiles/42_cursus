#include "../includes/cub3d.h"

static int	count_map_lines(int fd)
{
	char	*line;
	int		count;
	int		found_map;

	count = 0;
	found_map = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '1' || line[0] == '0')
			found_map = 1;
		if (found_map)
			count++;
		free(line);
	}
	return (count);
}

static int	get_map_width(int fd)
{
	char	*line;
	int		max_width;
	int		len;

	max_width = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '1' || line[0] == '0')
		{
			len = ft_strlen(line);
			if (line[len - 1] == '\n')
				len--;
			if (len > max_width)
				max_width = len;
		}
		free(line);
	}
	return (max_width);
}

static int	fill_map(int fd, t_game *game)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '1' || line[0] == '0')
		{
			if (line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = '\0';
			game->map.grid[i] = ft_strdup(line);
			if (!game->map.grid[i])
			{
				free(line);
				// Free all previously allocated grid lines
				for (int j = 0; j < i; j++)
					free(game->map.grid[j]);
				free(game->map.grid);
				game->map.grid = NULL;
				return (-1);
			}
			i++;
		}
		free(line);
	}
	game->map.grid[i] = NULL;
	return (0);
}

static void drain_and_free_lines(int fd)
{
	char *line;
	while ((line = get_next_line(fd)))
		free(line);
	get_next_line_free();
}

int	validate_map(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < (int)ft_strlen(game->map.grid[y]))
			if (check_player_char(game, x, y))
				return (-1); // Return -1 on invalid
	}
	return (0); // Return 0 on valid
}

int	parse_map(char *filename, t_game *game, int start_line)
{
	int	fd;

	(void)start_line;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	game->map.height = count_map_lines(fd);
	if (game->map.height <= 0)
	{
		drain_and_free_lines(fd);
		close(fd);
		get_next_line_free();
		return (-1);
	}
	close(fd);
	get_next_line_free();

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	game->map.width = get_map_width(fd);
	if (game->map.width <= 0)
	{
		drain_and_free_lines(fd);
		close(fd);
		get_next_line_free();
		return (-1);
	}
	close(fd);
	get_next_line_free();

	game->map.grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(game->map.grid);
		game->map.grid = NULL;
		return (-1);
	}
	if (fill_map(fd, game) == -1)
	{
		drain_and_free_lines(fd);
		close(fd);
		get_next_line_free();
		return (-1);
	}
	close(fd);
	get_next_line_free();
	if (validate_map(game) == -1)
	{
		free_map_grid(game);
		return (-1);
	}
	return (0);
}

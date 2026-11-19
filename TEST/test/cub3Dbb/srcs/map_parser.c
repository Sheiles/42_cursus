#include "../includes/cub3d.h"

static int	is_map_line(char *line)
{
	return (line[0] == '1' || line[0] == '0' || line[0] == ' ');
}

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
		if (found_map && is_map_line(line))
			count++;
		free(line);
	}
	get_next_line(-1);
	return (count);
}

static int	get_map_width(int fd)
{
	char	*line;
	int		max_width;
	int		len;
	int		found_map;

	max_width = 0;
	found_map = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '1' || line[0] == '0')
			found_map = 1;
		if (found_map && is_map_line(line))
		{
			len = (int)ft_strlen(line);
			if (len > 0 && line[len - 1] == '\n')
				len--;
			if (len > max_width)
				max_width = len;
		}
		free(line);
	}
	get_next_line(-1);
	return (max_width);
}

static int	fill_map(int fd, t_game *game)
{
	char	*line;
	int		i;
	int		len;
	int		found_map;

	i = 0;
	found_map = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '1' || line[0] == '0')
			found_map = 1;
		if (found_map && is_map_line(line))
		{
			len = (int)ft_strlen(line);
			if (len > 0 && line[len - 1] == '\n')
				line[len - 1] = '\0';
			game->map.grid[i] = ft_strdup(line);
			i++;
		}
		free(line);
	}
	get_next_line(-1);
	game->map.grid[i] = NULL;
	return (0);
}

int	parse_map(char *filename, t_game *game, int start_line)
{
	int	fd;

	(void)start_line;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	game->map.height = count_map_lines(fd);
	close(fd);
	if (game->map.height == 0)
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	game->map.width = get_map_width(fd);
	close(fd);
	game->map.grid = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!game->map.grid)
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	fill_map(fd, game);
	close(fd);
	return (validate_map(game));
}
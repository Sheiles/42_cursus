
#include "so_long.h"

void	free_map(t_game *game)
{
	int i = 0;
	while (game->map && game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
}

static int	count_lines(char *filename)
{
	int	fd;
	int	count;
	char	c;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error("Cannot open file");
	count = 0;
	while (read(fd, &c, 1) > 0)
		if (c == '\n')
			count++;
	close(fd);
	return (count + 1);
}

static char	*read_file(char *filename)
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
		error("Invalid map");
        if (!check_valid_path(game))
	error("No valid path to all keys and exit");
	return (1);
}

int	is_valid_map(t_game *game)
{
	int i, j;
	int exits = 0, players = 0, keys = 0;

	i = 0;
	while (i < game->height)
	{
		if ((int)sl_strlen(game->map[i]) != game->width)
			return (0);
		j = 0;
		while (j < game->width)
		{
			if (i == 0 || j == 0 || i == game->height - 1 || j == game->width - 1)
				if (game->map[i][j] != WALL)
					return (0);
			if (game->map[i][j] == PLAYER)
			{
				players++;
				game->player_x = j;
				game->player_y = i;
			}
			if (game->map[i][j] == EXIT)
				exits++;
			if (game->map[i][j] == KEY)
				keys++;
			j++;
		}
		i++;
	}
	return (players == 1 && exits == 1 && keys >= 1);
}

#include "../includes/cub3d.h"

int	parse_no_texture(char *line, t_game *game)
{
	char	*path;

	path = ft_strtrim(line + 2, " ");
	if (!path || path[0] == '\0')
	{
		free(path);
		return (-1);
	}
	game->no_texture.path = ft_strdup(path);
	free(path);
	return (0);
}

int	parse_so_texture(char *line, t_game *game)
{
	char	*path;

	path = ft_strtrim(line + 2, " ");
	if (!path || path[0] == '\0')
	{
		free(path);
		return (-1);
	}
	game->so_texture.path = ft_strdup(path);
	free(path);
	return (0);
}

int	parse_we_texture(char *line, t_game *game)
{
	char	*path;

	path = ft_strtrim(line + 2, " ");
	if (!path || path[0] == '\0')
	{
		free(path);
		return (-1);
	}
	game->we_texture.path = ft_strdup(path);
	free(path);
	return (0);
}

int	parse_ea_texture(char *line, t_game *game)
{
	char	*path;

	path = ft_strtrim(line + 2, " ");
	if (!path || path[0] == '\0')
	{
		free(path);
		return (-1);
	}
	game->ea_texture.path = ft_strdup(path);
	free(path);
	return (0);
}

int	parse_floor_color(char *line, t_game *game)
{
	char	**colors;
	char	*trimmed;
	int		i;

	trimmed = ft_strtrim(line + 1, " ");
	colors = ft_split(trimmed, ',');
	free(trimmed);
	if (!colors || !colors[0] || !colors[1] || !colors[2])
		return (-1);
	game->floor_color.r = ft_atoi(colors[0]);
	game->floor_color.g = ft_atoi(colors[1]);
	game->floor_color.b = ft_atoi(colors[2]);
	i = 0;
	while (colors[i])
		free(colors[i++]);
	free(colors);
	return (0);
}

int	parse_ceiling_color(char *line, t_game *game)
{
	char	**colors;
	char	*trimmed;
	int		i;

	trimmed = ft_strtrim(line + 1, " ");
	colors = ft_split(trimmed, ',');
	free(trimmed);
	if (!colors || !colors[0] || !colors[1] || !colors[2])
		return (-1);
	game->ceiling_color.r = ft_atoi(colors[0]);
	game->ceiling_color.g = ft_atoi(colors[1]);
	game->ceiling_color.b = ft_atoi(colors[2]);
	i = 0;
	while (colors[i])
		free(colors[i++]);
	free(colors);
	return (0);
}

int	parse_cub_file(char *filename, t_game *game)
{
	int		fd;
	char	*line;
	int		start_map;
	int		found_no;
	int		found_so;
	int		found_we;
	int		found_ea;
	int		found_f;
	int		found_c;

	found_no = 0;
	found_so = 0;
	found_we = 0;
	found_ea = 0;
	found_f = 0;
	found_c = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	start_map = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (line[0] != '\n' && line[0] != '\0')
		{
			if (ft_strncmp(line, "NO", 2) == 0)
				found_no = parse_no_texture(line, game);
			else if (ft_strncmp(line, "SO", 2) == 0)
				found_so = parse_so_texture(line, game);
			else if (ft_strncmp(line, "WE", 2) == 0)
				found_we = parse_we_texture(line, game);
			else if (ft_strncmp(line, "EA", 2) == 0)
				found_ea = parse_ea_texture(line, game);
			else if (ft_strncmp(line, "F", 1) == 0 && line[1] == ' ')
				found_f = parse_floor_color(line, game);
			else if (ft_strncmp(line, "C", 1) == 0 && line[1] == ' ')
				found_c = parse_ceiling_color(line, game);
			else if (line[0] == '0' || line[0] == '1' || line[0] == 'N' 
				|| line[0] == 'S' || line[0] == 'E' || line[0] == 'W')
				break;
		}
		free(line);
		start_map++;
	}
	close(fd);
	if (found_no || found_so || found_we || found_ea || found_f || found_c)
	{
		if (parse_map(filename, game, start_map) == -1)
			return (-1);
	}
	if (validate_map(game) == -1)
		return (-1);
	return (0);
}

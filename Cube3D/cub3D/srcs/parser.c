/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 00:00:00 by sheiles           #+#    #+#             */
/*   Updated: 2026/02/12 00:00:00 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	parse_line(char *line, t_game *game, t_parser_flags *flags)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && !flags->found_no)
	{
		flags->found_no = 1;
		return (parse_no_texture(line, game));
	}
	else if (ft_strncmp(line, "SO ", 3) == 0 && !flags->found_so)
	{
		flags->found_so = 1;
		return (parse_so_texture(line, game));
	}
	else if (ft_strncmp(line, "WE ", 3) == 0 && !flags->found_we)
	{
		flags->found_we = 1;
		return (parse_we_texture(line, game));
	}
	else if (ft_strncmp(line, "EA ", 3) == 0 && !flags->found_ea)
	{
		flags->found_ea = 1;
		return (parse_ea_texture(line, game));
	}
	return (0);
}

static int	parse_color_line(char *line, t_game *game, t_parser_flags *flags)
{
	if (ft_strncmp(line, "F ", 2) == 0 && !flags->found_f)
	{
		flags->found_f = 1;
		return (parse_floor_color(line, game));
	}
	else if (ft_strncmp(line, "C ", 2) == 0 && !flags->found_c)
	{
		flags->found_c = 1;
		return (parse_ceiling_color(line, game));
	}
	return (0);
}

static int	parse_config(int fd, t_game *game, t_parser_flags *flags)
{
	char	*line;
	int		config_done;

	config_done = 0;
	while (!config_done)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '\n' && line[0] != '\0')
		{
			if (parse_line(line, game, flags) == -1
				|| parse_color_line(line, game, flags) == -1)
			{
				free(line);
				return (-1);
			}
			if (flags->found_no && flags->found_so && flags->found_we
				&& flags->found_ea && flags->found_f && flags->found_c)
				config_done = 1;
		}
		free(line);
	}
	return (0);
}

int	parse_cub_file(char *filename, t_game *game)
{
	int				fd;
	t_parser_flags	flags;

	ft_memset(&flags, 0, sizeof(t_parser_flags));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (parse_config(fd, game, &flags) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	if (parse_map(filename, game, 0) == -1)
		return (-1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 18:30:00 by sheiles           #+#    #+#             */
/*   Updated: 2026/02/11 19:57:05 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

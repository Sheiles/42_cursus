/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 12:15:12 by sheiles           #+#    #+#             */
/*   Updated: 2024/12/12 15:59:30 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h> // Ajouté pour size_t et NULL
#include <stdlib.h> // Ajouté pour malloc et free
#include <unistd.h> // Ajouté pour read

static char	*read_to_buffer(int fd, char *buffer)
{
	char	*temp;
	ssize_t	bytes_read;
	char	*new_buffer;

	temp = (char *)malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	while (!ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		temp[bytes_read] = '\0';
		new_buffer = ft_strjoin(buffer, temp);
		if (!new_buffer)
		{
			free(temp);
			free(buffer);
			return (NULL);
		}
		free(buffer);
		buffer = new_buffer;
	}
	free(temp);
	return (buffer);
}

static char	*extract_line(char *buffer)
{
	size_t	i;
	size_t	j;
	size_t	line_length;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		line_length = i + 2;
	else
		line_length = i + 1;
	line = (char *)ft_calloc(line_length, sizeof(char));
	if (!line)
		return (NULL);
	j = 0;
	while (j < line_length - 1)
	{
		line[j] = buffer[j];
		j++;
	}
	return (line);
}

static char	*trim_buffer(char *buffer)
{
	char	*newline;
	char	*new_buffer;

	newline = ft_strchr(buffer, '\n');
	if (!newline)
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = ft_strdup(newline + 1);
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = (char *)ft_calloc(1, sizeof(char));
	if (!buffer)
		return (NULL);
	buffer = read_to_buffer(fd, buffer);
	if (!buffer || *buffer == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = extract_line(buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = trim_buffer(buffer);
	return (line);
}

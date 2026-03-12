











#include "libft.h"


static size_t	set_nl(char **buffer)
{
	size_t	nl_pos;

	nl_pos = 0;
	while (buffer[0][nl_pos] && buffer[0][nl_pos] != '\n')
		nl_pos++;
	if (buffer[0][nl_pos] == '\n')
		nl_pos++;
	return (nl_pos);
}


static char	*split_line(char *line, char *buffer)
{
	char	*temp_line;
	char	*sub_buffer;
	size_t	nl_pos;
	size_t	aux;

	nl_pos = set_nl(&buffer);
	temp_line = line;
	aux = ft_strlen (line);
	sub_buffer = ft_substr (buffer, 0, nl_pos);
	line = ft_strjoin (temp_line, sub_buffer);
	free (temp_line);
	free (sub_buffer);
	if (!line)
		return (NULL);
	line[aux + nl_pos] = 0;
	aux = 0;
	while (buffer[nl_pos + aux])
	{
		buffer[aux] = buffer[nl_pos + aux];
		aux++;
	}
	buffer[aux] = 0;
	return (line);
}


static ssize_t	read_file(char **line, char *buffer, int fd)
{
	ssize_t	read_bytes;
	size_t	j;

	read_bytes = 42;
	j = 0;
	while (line[0][j] != '\n' && line[0][j])
		j++;
	while (line[0][j] != '\n' && read_bytes > 0)
	{
		read_bytes = read (fd, buffer, BUFFER_SIZE);
		if (read_bytes > 0)
		{
			buffer[read_bytes] = 0;
			*line = split_line (*line, buffer);
			if (!line[0])
				return (-1);
		}
		j = 0;
		while (line[0][j] != '\n' && line[0][j])
			j++;
	}
	return (read_bytes);
}


static char	check(int fd, char **line, char **buffer)
{
	if (fd < 0 || fd >= 1024)
		return (0);
	if (BUFFER_SIZE <= 0)
		return (0);
	line[0] = ft_strdup ("");
	if (!line[0])
		return (0);
	if (!*buffer)
	{
		*buffer = malloc ((BUFFER_SIZE + 1) * sizeof(char));
		if (!*buffer)
		{
			free (line[0]);
			return (0);
		}
		*buffer[0] = 0;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;
	ssize_t		read_bytes;

	if (!check (fd, &line, &buffer[fd]))
		return (NULL);
	if (buffer[fd])
	{
		line = split_line (line, buffer[fd]);
		if (!line)
			return (NULL);
	}
	read_bytes = read_file (&line, buffer[fd], fd);
	if ((!read_bytes && !line[0]) || read_bytes < 0)
	{
		free (buffer[fd]);
		free (line);
		buffer[fd] = NULL;
		return (NULL);
	}
	return (line);
}

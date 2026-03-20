#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

static char	*ft_free(char *s1, char *s2)
{
	free(s1);
	return (s2);
}

static char	*ft_read_line(int fd, char *buffer, char *line)
{
	int		bytes;
	char	*temp;

	while (1)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (ft_free(line, NULL));
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		if (line == NULL)
			line = ft_strdup("");
		if (line == NULL)
			return (NULL);
		temp = line;
		line = ft_strjoin(line, buffer);
		free(temp);
		if (line == NULL)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (line);
}

static char	*process_line(char **line)
{
	char	*newline;
	char	*result;

	newline = ft_strchr(*line, '\n');
	if (newline)
	{
		*newline = '\0';
		if (*line && (*line)[0] != '\0')
			result = ft_strdup(*line);
		else
			result = NULL;
		// Move remaining part BEFORE freeing
		ft_memmove(*line, newline + 1, ft_strlen(newline + 1) + 1);
		if ((*line)[0] == '\0')
		{
			free(*line);
			*line = NULL;
		}
	}
	else
	{
		if (*line && (*line)[0] != '\0')
			result = *line;
		else {
			free(*line);
			result = NULL;
		}
		*line = NULL;
	}
	return result;
}

static char *gnl_static_line = NULL;

char	*get_next_line(int fd)
{
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (gnl_static_line == NULL)
	{
		gnl_static_line = ft_read_line(fd, buffer, NULL);
		free(buffer);
		if (gnl_static_line == NULL || gnl_static_line[0] == '\0')
		{
			free(gnl_static_line);
			gnl_static_line = NULL;
			return (NULL);
		}
	}
	return (process_line(&gnl_static_line));
}

void get_next_line_free(void)
{
	if (gnl_static_line)
	{
		free(gnl_static_line);
		gnl_static_line = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcamacho <tcamacho@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:47:53 by tcamacho          #+#    #+#             */
/*   Updated: 2025/08/08 16:30:44 by tcamacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_input(char *file, int *fd)
{
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
		return (perror(file), -1);
	return (0);
}

static int	open_output(char *file, int *fd, int append)
{
	if (append)
		*fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		*fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*fd == -1)
		return (perror(file), -1);
	return (0);
}

static int	handle_redir_type(t_redir *r, int *in_fd, int *out_fd)
{
	int	fd;

	if (r->type == 0)
		return (open_input(r->file, in_fd));
	else if (r->type == 1)
		return (open_output(r->file, out_fd, 0));
	else if (r->type == 2)
		return (open_output(r->file, out_fd, 1));
	else if (r->type == 3)
	{
		fd = handle_heredoc(r->file);
		if (fd == -1)
			return (-1);
		*in_fd = fd;
	}
	return (0);
}

int	handle_redirections(t_redir *redir, int *stdin_fd, int *stdout_fd)
{
	while (redir)
	{
		if (handle_redir_type(redir, stdin_fd, stdout_fd) < 0)
			return (-1);
		redir = redir->next;
	}
	return (0);
}

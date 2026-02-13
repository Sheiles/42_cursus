/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:47:47 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/08 22:24:21 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

static int	redir_type(const char *t)
{
	if (!t)
		return (0);
	if (!strcmp(t, "<"))
		return (1);
	if (!strcmp(t, ">"))
		return (2);
	if (!strcmp(t, ">>"))
		return (3);
	if (!strcmp(t, "<<"))
		return (4);
	return (0);
}

static void	take_word(t_cmd *cmd, char **tokens, int *j, int *k)
{
	char	*clean;

	clean = clean_token(tokens[*j]);
	if (clean)
	{
		cmd->args[*k] = clean;
		(*k)++;
	}
	(*j)++;
}

static void	take_redir(t_cmd *cmd, char **tokens, int *j, int type)
{
	char	*file;
	char	*clean;

	(*j)++;
	if (!tokens[*j])
		return ;
	clean = clean_token(tokens[*j]);
	if (clean)
		file = clean;
	else
		file = tokens[*j];
	cmd->redirs = add_redir(cmd->redirs, file, type);
	if (clean)
		free(clean);
	(*j)++;
}

static void	parse_one_cmd(t_cmd *cmd, char **tokens, int *j)
{
	int	k;
	int	rt;

	k = 0;
	while (tokens[*j] && strcmp(tokens[*j], "|"))
	{
		rt = redir_type(tokens[*j]);
		if (rt)
			take_redir(cmd, tokens, j, rt);
		else
			take_word(cmd, tokens, j, &k);
	}
	cmd->args[k] = NULL;
	if (tokens[*j] && !strcmp(tokens[*j], "|"))
		(*j)++;
}

void	process_command(t_cmd **head, t_cmd **curr, char **tokens, int *j)
{
	t_cmd	*new;

	new = init_cmd();
	if (!new)
		return ;
	if (!*head)
		*head = new;
	else
		(*curr)->next = new;
	*curr = new;
	parse_one_cmd(new, tokens, j);
}

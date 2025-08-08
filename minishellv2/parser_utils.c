/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:50:54 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/08 22:20:21 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = malloc(sizeof(char *) * 128);
	if (!cmd->args)
		return (free(cmd), NULL);
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_redir	*add_redir(t_redir *list, char *file, int type)
{
	t_redir	*new;
	t_redir	*tmp;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (list);
	new->file = clean_token(file);
	new->type = type;
	new->next = NULL;
	if (!list)
		return (new);
	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (list);
}

char	*clean_token(char *token)
{
	char	*expanded;
	char	*stripped;

	expanded = expand_variables(token);
	stripped = strip_quotes(expanded);
	free(expanded);
	return (stripped);
}

static void	free_redirs(t_redir *r)
{
	t_redir	*n;

	while (r)
	{
		n = r->next;
		free(r->file);
		free(r);
		r = n;
	}
}

void	free_cmds(t_cmd *c)
{
	t_cmd	*n;
	int		i;

	while (c)
	{
		n = c->next;
		if (c->args)
		{
			i = 0;
			while (c->args[i])
				free(c->args[i++]);
			free(c->args);
		}
		free_redirs(c->redirs);
		free(c);
		c = n;
	}
}

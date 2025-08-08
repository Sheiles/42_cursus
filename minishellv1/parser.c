/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:47:47 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/08 21:46:17 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	consume_simple_token(t_cmd *cmd, char **tokens, int *j, int *k)
{
	char	*clean;

	clean = clean_token(tokens[*j]);
	cmd->args[*k] = clean;
	*k = *k + 1;
	*j = *j + 1;
}

static void	consume_redir(t_cmd *cmd, char **tokens, int *j, int type)
{
	*j = *j + 1;
	if (tokens[*j])
	{
		cmd->redirs = add_redir(cmd->redirs, tokens[*j], type);
		*j = *j + 1;
	}
}

static void	fill_cmd_from_tokens(t_cmd *cmd, char **tokens, int *j)
{
	int	k;

	k = 0;
	while (tokens[*j] && strcmp(tokens[*j], "|"))
	{
		if (!strcmp(tokens[*j], "<"))
			consume_redir(cmd, tokens, j, 0);
		else if (!strcmp(tokens[*j], ">"))
			consume_redir(cmd, tokens, j, 1);
		else if (!strcmp(tokens[*j], ">>"))
			consume_redir(cmd, tokens, j, 2);
		else if (!strcmp(tokens[*j], "<<"))
			consume_redir(cmd, tokens, j, 3);
		else
			consume_simple_token(cmd, tokens, j, &k);
	}
	cmd->args[k] = NULL;
}

static char	**tokenize_line(char *line)
{
	char	**tokens;
	char	*tok;
	int		i;

	tokens = malloc(sizeof(char *) * 1024);
	if (!tokens)
		return (NULL);
	i = 0;
	tok = strtok(line, " \t");
	while (tok)
	{
		tokens[i] = ft_strdup(tok);
		i++;
		tok = strtok(NULL, " \t");
	}
	tokens[i] = NULL;
	return (tokens);
}

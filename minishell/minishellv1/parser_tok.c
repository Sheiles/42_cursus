/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tok.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:47:47 by tcamacho          #+#    #+#             */
/*   Updated: 2025/08/08 21:13:12 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*init_parsing(char *line, char ***tokens)
{
	*tokens = tokenize_line(line);
	if (!*tokens)
		return (NULL);
	return (NULL);
}

static void	process_command(t_cmd **head, t_cmd **curr, char **tokens, int *j)
{
	t_cmd	*cmd;

	cmd = init_cmd();
	fill_cmd_from_tokens(cmd, tokens, j);
	if (!*head)
		*head = cmd;
	else
		(*curr)->next = cmd;
	*curr = cmd;
	if (tokens[*j])
		(*j)++;
}

t_cmd	*parse_input(char *line)
{
	char	**tokens;
	t_cmd	*head;
	t_cmd	*curr;
	int		j;

	head = init_parsing(line, &tokens);
	if (!tokens)
		return (NULL);
	curr = NULL;
	j = 0;
	while (tokens[j])
		process_command(&head, &curr, tokens, &j);
	free_array(tokens);
	return (head);
}

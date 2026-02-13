/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tok.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:47:47 by tcamacho          #+#    #+#             */
/*   Updated: 2025/08/08 22:24:30 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

static void	push_tok(char **t, int *n, const char *s)
{
	char	*dup;

	dup = ft_strdup(s);
	if (dup)
	{
		t[*n] = dup;
		(*n)++;
	}
}

static int	take_operator(const char *s, int *i, char **t, int *n)
{
	char	tmp[2];

	tmp[0] = 0;
	tmp[1] = 0;
	if (s[*i] == '<' && s[*i + 1] == '<')
	{
		push_tok(t, n, "<<");
		*i += 2;
		return (1);
	}
	if (s[*i] == '>' && s[*i + 1] == '>')
	{
		push_tok(t, n, ">>");
		*i += 2;
		return (1);
	}
	if (s[*i] == '|' || s[*i] == '<' || s[*i] == '>')
	{
		tmp[0] = s[*i];
		tmp[1] = '\0';
		push_tok(t, n, tmp);
		(*i)++;
		return (1);
	}
	return (0);
}

static int	take_word(const char *s, int *i, char **t, int *n)
{
	int		start;
	int		len;
	char	*w;

	start = *i;
	while (s[*i] && !strchr(" \t|<>", s[*i]))
		(*i)++;
	len = *i - start;
	w = (char *)malloc(len + 1);
	if (!w)
		return (0);
	memcpy(w, s + start, len);
	w[len] = '\0';
	t[*n] = w;
	(*n)++;
	return (1);
}

char	**tokenize_line(char *s)
{
	char	**t;
	int		i;
	int		n;

	if (!s)
		return (NULL);
	t = (char **)malloc(sizeof(char *) * 512);
	if (!t)
		return (NULL);
	i = 0;
	n = 0;
	while (s[i])
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (!s[i])
			break ;
		if (!take_operator(s, &i, t, &n))
			if (!take_word(s, &i, t, &n))
				break ;
	}
	t[n] = NULL;
	return (t);
}

t_cmd	*parse_input(char *line)
{
	char	**tokens;
	t_cmd	*head;
	t_cmd	*curr;
	int		j;

	tokens = tokenize_line(line);
	if (!tokens)
		return (NULL);
	head = NULL;
	curr = NULL;
	j = 0;
	while (tokens[j])
		process_command(&head, &curr, tokens, &j);
	free_array(tokens);
	return (head);
}

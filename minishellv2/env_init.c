/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 15:50:27 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/08 22:20:14 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*new_env_node(const char *k, const char *v)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = strndup(k, strlen(k));
	node->value = strdup(v);
	node->next = NULL;
	return (node);
}

static void	add_env_node(t_env **head, t_env **last, char *key, char *value)
{
	if (!*head)
		*head = new_env_node(key, value);
	else
		(*last)->next = new_env_node(key, value);
	if (!*last)
		*last = *head;
	else
		*last = (*last)->next;
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*last;
	int		i;
	char	*sep;

	head = NULL;
	last = NULL;
	i = 0;
	while (envp[i])
	{
		sep = strchr(envp[i], '=');
		if (sep)
		{
			*sep = '\0';
			add_env_node(&head, &last, envp[i], sep + 1);
			*sep = '=';
		}
		i++;
	}
	return (head);
}

void	init_shell(char **envp)
{
	g_shell.env = init_env(envp);
	g_shell.exit_status = 0;
	g_shell.heredoc_sigint = 0;
}

void	free_shell(void)
{
	free_env(g_shell.env);
	g_shell.env = NULL;
}

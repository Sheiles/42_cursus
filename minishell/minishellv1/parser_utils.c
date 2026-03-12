











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

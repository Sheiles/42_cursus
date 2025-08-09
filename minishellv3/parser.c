#include "minishell.h"

static t_cmd	*init_cmd(void)
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->args = malloc(sizeof(char *) * 128);
	cmd->redirs = NULL;
	cmd->next = NULL;
	return cmd;
}

static void	handle_token(t_cmd *cmd, char **tokens, int *j, int *k)
{
	if (!strcmp(tokens[*j], "<"))
		cmd->redirs = add_redir(cmd->redirs, tokens[++(*j)], 0);
	else if (!strcmp(tokens[*j], ">"))
		cmd->redirs = add_redir(cmd->redirs, tokens[++(*j)], 1);
	else if (!strcmp(tokens[*j], ">>"))
		cmd->redirs = add_redir(cmd->redirs, tokens[++(*j)], 2);
	else if (!strcmp(tokens[*j], "<<"))
		cmd->redirs = add_redir(cmd->redirs, tokens[++(*j)], 3);
	else
		cmd->args[(*k)++] = clean_token(tokens[*j]);
}

t_cmd	*parse_input(char *line)
{
	t_cmd *head = NULL;
	t_cmd *curr = NULL;
	char **tokens = malloc(sizeof(char *) * 1024);
	int i = 0;
	char *tok = strtok(line, " \t");

	while (tok)
		tokens[i++] = ft_strdup(tok), tok = strtok(NULL, " \t");
	tokens[i] = NULL;

	int j = 0;
	while (tokens[j])
	{
		t_cmd *cmd = init_cmd();
		int k = 0;
		while (tokens[j] && strcmp(tokens[j], "|"))
			handle_token(cmd, tokens, &j, &k), j++;
		cmd->args[k] = NULL;
		if (!head)
			head = cmd;
		else
			curr->next = cmd;
		curr = cmd;
		if (tokens[j])
			j++;
	}
	free_array(tokens);
	return head;
}

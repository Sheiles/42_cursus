/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 14:51:01 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/08 22:19:29 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	char			*file;
	int				type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	t_env	*env;
	int		exit_status;
	int		heredoc_sigint;
}	t_shell;

extern t_shell	g_shell;

/* shell */
void	init_shell(char **envp);
void	free_shell(void);

/* parser */
t_cmd	*parse_input(char *line);
void	free_cmds(t_cmd *cmds);
t_cmd	*init_cmd(void);
char	*clean_token(char *token);
t_redir	*add_redir(t_redir *list, char *file, int type);
void	process_command(t_cmd **head, t_cmd **curr, char **tokens, int *j);

/* tokenizer */
char	**tokenize_line(char *line);

/* parser utils (si utilisé hors de parser.c) */
void	fill_cmd_from_tokens(t_cmd *cmd, char **tokens, int *j);

/* executor */
void	execute(t_cmd *cmds);

/* redir */
int		handle_redirections(t_redir *redir, int *stdin_fd, int *stdout_fd);

/* heredoc */
int		handle_heredoc(char *delimiter);

/* expansion */
char	*expand_variables(char *str);

/* builtins */
int		is_builtin(char *cmd);
int		exec_builtin(t_cmd *cmd);
int		builtin_echo(char **argv);
int		builtin_cd(char **argv);
int		builtin_pwd(void);
int		builtin_env(void);
int		builtin_export(char **argv);
int		builtin_unset(char **argv);
int		builtin_exit(char **argv);

/* env utils */
t_env	*init_env(char **envp);
void	free_env(t_env *env);
char	*get_env_value(char *key);
void	set_env_value(char *key, char *value);
void	unset_env_key(char *key);
char	**env_to_array(void);

/* utils */
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, char *s2);
void	free_array(char **arr);
char	*strip_quotes(char *s);

#endif

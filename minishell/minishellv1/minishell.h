











#ifndef MINISHELL_H
# define MINISHELL_H
# define ft_isalnum isalnum

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
# include <ctype.h>


extern volatile sig_atomic_t g_sig;

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

t_shell	*ms_ctx(t_shell *set);
# define g_shell (*ms_ctx(NULL))


void	init_shell(char **envp);
void	free_shell(void);


t_cmd	*parse_input(char *line);
void	free_cmds(t_cmd *cmds);


void	execute(t_cmd *cmds);


int		handle_redirections(t_redir *redir, int *stdin_fd, int *stdout_fd);


int		handle_heredoc(char *delimiter);


char	*expand_variables(char *str);


int		is_builtin(char *cmd);
int		exec_builtin(t_cmd *cmd);


t_env	*init_env(char **envp);
void	free_env(t_env *env);
char	*get_env_value(char *key);
void	set_env_value(char *key, char *value);
void	unset_env_key(char *key);
char	**env_to_array(void);


char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, char *s2);
void	free_array(char **arr);
char	*strip_quotes(char *s);


void    setup_signals_interactive(void);
void    setup_signals_child(void);
void    setup_signals_heredoc(void);

#endif

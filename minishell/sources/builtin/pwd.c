











#include "minishell.h"

void	ft_pwd(t_mini *ms, char **cmd, char **envp)
{
	size_t	i;

	if (!cmd[1])
	{
		i = 0;
		while (envp && ft_strncmp (envp[i], "PWD=", 4))
			i++;
		if (envp && envp[i])
			ft_printf ("%s\n", envp[i] + 4);
	}
	else
	{
		ft_putstr_fd ("-" PROMPT_MSG ": pwd: " INVALID_USAGE "\n", 2);
		ms -> error = 42;
	}
}

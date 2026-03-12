











#include "minishell.h"

t_shell	*ms_ctx(t_shell *set)
{
	static t_shell *ctx;

	if (set != NULL)
		ctx = set;
	return (ctx);
}

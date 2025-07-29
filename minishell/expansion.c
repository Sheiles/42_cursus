#include "minishell.h"

static int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static int	expand_var(const char *str, int i, char *res, int *j)
{
	char var[256];
	int k = 0;

	if (str[i] == '?')
	{
		*j += sprintf(res + *j, "%d", g_shell.exit_status);
		return i + 1;
	}
	while (str[i] && is_valid_var_char(str[i]) && k < 255)
		var[k++] = str[i++];
	var[k] = '\0';
	char *val = get_env_value(var);
	if (val)
		*j += sprintf(res + *j, "%s", val);
	return i;
}

char	*expand_variables(char *str)
{
	char	*res = malloc(4096);
	int		i = 0, j = 0;

	while (str[i])
	{
		if (str[i] == '$')
			i = expand_var(str, i + 1, res, &j);
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return res;
}

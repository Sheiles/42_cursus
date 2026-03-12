











#include "minishell.h"

static int	is_valid_var_char(char c)
{
	if (ft_isalnum(c))
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

static int	expand_var(const char *str, int i, char *res, int *j)
{
	char	var[256];
	int		k;
	char	*val;

	k = 0;
	if (str[i] == '?')
	{
		*j += sprintf(res + *j, "%d", g_shell.exit_status);
		return (i + 1);
	}
	while (str[i] && is_valid_var_char(str[i]) && k < 255)
	{
		var[k] = str[i];
		k++;
		i++;
	}
	var[k] = '\0';
	val = get_env_value(var);
	if (val)
		*j += sprintf(res + *j, "%s", val);
	return (i);
}

char	*expand_variables(char *str)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(4096);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
			i = expand_var(str, i + 1, res, &j);
		else
		{
			res[j] = str[i];
			j++;
			i++;
		}
	}
	res[j] = '\0';
	return (res);
}

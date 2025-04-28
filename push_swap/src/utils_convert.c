#include "../includes/push_swap.h"

int	ft_atoi(const char *str)
{
	long	res = 0;
	int		sign = 1;
	int		i = 0;

	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		if (res * sign > INT_MAX || res * sign < INT_MIN)
			exit_error(NULL, NULL);
		i++;
	}
	return ((int)(res * sign));
}

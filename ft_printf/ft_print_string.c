











#include "ft_printf.h"

int	ft_print_string(char *str)
{
	int	count;

	count = 0;
	if (!str)
	{
		count += write(1, "(null)", 6);
		return (count);
	}
	while (*str)
		count += write(1, str++, 1);
	return (count);
}

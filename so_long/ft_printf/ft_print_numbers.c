











#include "ft_printf.h"

int	ft_print_numbers(void)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < 10)
	{
		count += write(1, &i, 1);
		i++;
	}
	return (count);
}

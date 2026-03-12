











#include "ft_printf.h"

int	ft_print_char(char c)
{
	return (write(1, &c, 1));
}

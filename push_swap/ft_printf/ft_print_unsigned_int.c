











#include "ft_printf.h"

int	ft_print_unsigned_int(unsigned int n)
{
	int	len;

	len = 0;
	if (n >= 10)
	{
		len += ft_print_unsigned_int(n / 10);
		len += ft_print_char(n % 10 + '0');
	}
	else
	{
		len += ft_print_char(n + '0');
	}
	return (len);
}

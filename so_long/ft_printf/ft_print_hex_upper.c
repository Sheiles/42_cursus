











#include "ft_printf.h"

int	ft_print_hex_upper(unsigned long n)
{
	char	*hex;
	int		count;

	count = 0;
	hex = "0123456789ABCDEF";
	if (n >= 16)
		count += ft_print_hex_upper(n / 16);
	count += write(1, &hex[n % 16], 1);
	return (count);
}

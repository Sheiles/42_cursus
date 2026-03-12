











#include "ft_printf.h"

int	ft_print_hex_lower(unsigned long n)
{
	char	*hex;
	int		count;

	count = 0;
	hex = "0123456789abcdef";
	if (n >= 16)
		count = ft_print_hex_lower(n / 16);
	write(1, &hex[n % 16], 1);
	return (count + 1);
}













#include "ft_printf.h"

int	ft_print_signed_int(int n)

{
	int	len;

	len = 0;
	if (n == -2147483648)
		return (ft_print_string("-2147483648"));
	if (n < 0)
	{
		len += ft_print_char('-');
		n = -n;
	}
	if (n >= 10)
		len += ft_print_signed_int(n / 10);
	len += ft_print_char((n % 10) + '0');
	return (len);
}

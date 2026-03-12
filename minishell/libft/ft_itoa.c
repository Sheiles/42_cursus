











#include "libft.h"


static int	ft_nbrlen(int n)
{
	int	digits;

	digits = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		digits++;
	while (n)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}


static void	ft_convert(char *s, int n, int digits)
{
	unsigned int	u_n;

	if (n == 0)
		s[0] = '0';
	if (n < 0)
	{
		s[0] = '-';
		u_n = -n;
	}
	else
		u_n = n;
	while (u_n)
	{
		s[digits] = u_n % 10 + '0';
		u_n /= 10;
		digits--;
	}
}

char	*ft_itoa(int n)
{
	char	*s;
	int		digits;

	digits = ft_nbrlen(n);
	s = ft_calloc((digits + 1), sizeof(char));
	if (!s)
		return (NULL);
	ft_convert(s, n, digits - 1);
	return (s);
}

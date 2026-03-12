











#include "libft.h"

int	ft_isalpha(int c)
{
	return ((((unsigned) c | 0b100000) - 97 <= 25) << 10);
}

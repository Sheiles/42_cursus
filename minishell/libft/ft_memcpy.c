











#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*u_src;
	unsigned char	*u_dest;

	if (dest == NULL && src == NULL)
		return (NULL);
	u_src = (unsigned char *)src;
	u_dest = (unsigned char *)dest;
	while (n--)
		u_dest[n] = u_src[n];
	return (dest);
}

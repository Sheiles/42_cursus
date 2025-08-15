/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:47:30 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/09 16:47:32 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

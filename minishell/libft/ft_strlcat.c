/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:48:28 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/09 16:48:30 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;

	i = 0;
	dest_len = 0;
	while (dest[dest_len] && dest_len < size)
		dest_len++;
	i = dest_len;
	while (src[i - dest_len] && (i + 1) < size)
	{
		dest[i] = src[i - dest_len];
		i++;
	}
	if (dest_len < size)
		dest[i] = 0;
	return (dest_len + ft_strlen(src));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:48:10 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/09 16:48:12 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (s && *s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (s && *s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

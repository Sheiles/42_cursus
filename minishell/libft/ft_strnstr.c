/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:48:51 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/09 16:48:53 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*big_cpy;
	size_t	little_len;
	size_t	i;

	big_cpy = (char *)big;
	little_len = ft_strlen(little);
	i = 0;
	if (!*little)
		return (big_cpy);
	while (big[i] && i < len)
	{
		if (!ft_strncmp(&big[i], little, little_len) && (i + little_len <= len))
			return (&big_cpy[i]);
		i++;
	}
	return (NULL);
}

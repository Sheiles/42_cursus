/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:52:23 by sheiles           #+#    #+#             */
/*   Updated: 2024/10/30 15:22:20 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_occurrence;
	char	character;

	last_occurrence = NULL;
	character = (char)c;
	while (*s)
	{
		if (*s == character)
		{
			last_occurrence = (char *)s;
		}
		s++;
	}
	if (character == '\0')
	{
		return ((char *)s);
	}
	return (last_occurrence);
}

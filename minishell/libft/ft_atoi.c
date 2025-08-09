/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:45:28 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/09 16:45:34 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		n;
	char	signal;

	if (!nptr)
		return (0);
	n = 0;
	signal = 1;
	while (nptr && *nptr >= 9 && *nptr <= 32 && *nptr != '\e')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			signal *= -signal;
		nptr++;
	}
	while (ft_isdigit(*nptr))
		n = n * 10 + (*nptr++ - 48);
	return (n * signal);
}

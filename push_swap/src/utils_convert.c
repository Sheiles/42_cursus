/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_convert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:35:41 by sheiles           #+#    #+#             */
/*   Updated: 2025/05/01 00:49:19 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	ft_atoi(const char *str)
{
	long	res;
	int		sign;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	if (!str[i])
		exit_error(NULL, NULL);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			exit_error(NULL, NULL);
		res = res * 10 + (str[i++] - '0');
		if ((res * sign) > INT_MAX || (res * sign) < INT_MIN)
			exit_error(NULL, NULL);
	}
	return ((int)(res * sign));
}

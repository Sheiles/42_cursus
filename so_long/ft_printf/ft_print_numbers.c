/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:01:51 by sheiles           #+#    #+#             */
/*   Updated: 2024/11/06 14:01:28 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_numbers(void)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < 10)
	{
		count += write(1, &i, 1);
		i++;
	}
	return (count);
}

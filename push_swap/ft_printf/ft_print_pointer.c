/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:01:44 by sheiles           #+#    #+#             */
/*   Updated: 2024/11/21 12:26:26 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_pointer(void *ptr)
{
	unsigned long	address;
	int				len;

	if (!ptr)
		return (write(1, "(nil)", 5));
	address = (unsigned long)ptr;
	len = write(1, "0x", 2);
	len += ft_print_hex_lower(address);
	return (len);
}

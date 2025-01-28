/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:35:22 by sheiles           #+#    #+#             */
/*   Updated: 2024/11/22 12:35:41 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_printf_checker(char s, va_list *args, int *len)
{
	if (s == 's')
		*len += ft_print_string(va_arg(*args, char *));
	else if (s == 'd' || s == 'i')
		*len += ft_print_signed_int(va_arg(*args, int));
	else if (s == 'u')
		*len += ft_print_unsigned_int(va_arg(*args, unsigned int));
	else if (s == 'x')
		*len += ft_print_hex_lower(va_arg(*args, unsigned int));
	else if (s == 'X')
		*len += ft_print_hex_upper(va_arg(*args, unsigned int));
	else if (s == 'p')
		*len += ft_print_pointer(va_arg(*args, void *));
	else if (s == 'c')
		*len += ft_print_char(va_arg(*args, int));
	else if (s == '%')
		*len += ft_print_char('%');
}

int	ft_printf(const char *string, ...)
{
	va_list	args;
	int		i;
	int		length;

	i = 0;
	length = 0;
	va_start(args, string);
	while (string[i] != '\0')
	{
		if (string[i] == '%')
		{
			i++;
			ft_printf_checker(string[i], &args, &length);
		}
		else
		{
			length += ft_print_char(string[i]);
		}
		i++;
	}
	va_end(args);
	return (length);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:17:02 by sheiles           #+#    #+#             */
/*   Updated: 2024/11/21 12:29:54 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);

int	ft_print_char(char c);
int	ft_print_string(char *str);
int	ft_print_signed_int(int n);
int	ft_print_unsigned_int(unsigned int n);
int	ft_print_hex_lower(unsigned long n);
int	ft_print_hex_upper(unsigned long n);
int	ft_print_pointer(void *ptr);

#endif
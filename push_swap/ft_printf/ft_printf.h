











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
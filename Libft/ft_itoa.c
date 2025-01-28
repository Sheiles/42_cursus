/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:04:28 by sheiles           #+#    #+#             */
/*   Updated: 2024/10/30 11:03:59 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

// Calculer la longueur de la chaîne nécessaire pour le nombre
static int	ft_numlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

// Convertir un entier en chaîne de caractères
char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	long	nbr;

	len = ft_numlen(n);
	nbr = n;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nbr < 0)
		nbr = -nbr;
	while (len > 0)
	{
		len--;
		str[len] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

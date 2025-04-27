/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trier_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:15:59 by sheiles           #+#    #+#             */
/*   Updated: 2025/04/27 20:36:20 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	obtenir_max_bits(t_list **pile)
{
	t_list	*tete;
	int		max;
	int		max_bits;

	tete = *pile;
	max = tete->index;
	max_bits = 0;
	while (tete)
	{
		if (tete->index > max)
			max = tete->index;
		tete = tete->suivant;
	}
	while ((max >> max_bits) != 0)
		max_bits++;
	return (max_bits);
}

void	trier_base(t_list **pile_a, t_list **pile_b)
{
	t_list *tete_a;
	int i;
	int j;
	int taille;
	int max_bits;

	i = 0;
	tete_a = *pile_a;
	taille = ft_taille_liste(tete_a);
	max_bits = obtenir_max_bits(pile_a);
	while (i < max_bits)
	{
		j = 0;
		while (j++ < taille)
		{
			tete_a = *pile_a;
			if (((tete_a->index >> i) & 1) == 1)
				ra(pile_a);
			else
				pb(pile_a, pile_b);
		}
		while (ft_taille_liste(*pile_b) != 0)
			pa(pile_a, pile_b);
		i++;
	}
}
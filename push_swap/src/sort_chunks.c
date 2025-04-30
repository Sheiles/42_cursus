/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_chunks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:35:35 by sheiles           #+#    #+#             */
/*   Updated: 2025/05/01 00:35:36 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	find_max_index(t_stack *stack)
{
	int	max;

	max = stack->index;
	while (stack)
	{
		if (stack->index > max)
			max = stack->index;
		stack = stack->next;
	}
	return (max);
}

static void	push_back_to_a(t_stack **a, t_stack **b)
{
	int	max;

	while (*b)
	{
		max = find_max_index(*b);
		while ((*b)->index != max)
		{
			if (get_position(*b, max) <= stack_size(*b) / 2)
				rb(b);
			else
				rrb(b);
		}
		pa(a, b);
	}
}

static void	push_chunks(t_stack **a, t_stack **b, int chunk_size)
{
	int	i;

	i = 0;
	while (*a)
	{
		if ((*a)->index <= i)
		{
			pb(a, b);
			i++;
		}
		else if ((*a)->index <= i + chunk_size)
		{
			pb(a, b);
			rb(b);
			i++;
		}
		else
			ra(a);
	}
}

void	sort_chunks(t_stack **a, t_stack **b)
{
	int	chunk_size;

	if (stack_size(*a) <= 100)
		chunk_size = 20;
	else
		chunk_size = 45;
	push_chunks(a, b, chunk_size);
	push_back_to_a(a, b);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:55:52 by sheiles           #+#    #+#             */
/*   Updated: 2025/02/11 14:23:06 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_node **stack)
{
	if (!*stack || !(*stack)->next)
		return;
	t_node *first = *stack;
	t_node *second = first->next;
	first->next = second->next;
	second->next = first;
	*stack = second;
	printf("sa\n");
}

void	rotate(t_node **stack)
{
	if (!*stack || !(*stack)->next)
		return;
	t_node *first = *stack;
	t_node *last = *stack;
	while (last->next)
		last = last->next;
	*stack = first->next;
	first->next = NULL;
	last->next = first;
	printf("ra\n");
}

void	reverse_rotate(t_node **stack)
{
	if (!*stack || !(*stack)->next)
		return;
	t_node *prev = NULL;
	t_node *last = *stack;
	while (last->next)
	{
		prev = last;
		last = last->next;
	}
	prev->next = NULL;
	last->next = *stack;
	*stack = last;
	printf("rra\n");
}

void	push_to(t_node **src, t_node **dest, char stack_name)
{
	if (!*src)
		return;
	t_node *top = pop(src);
	top->next = *dest;
	*dest = top;
	printf("p%c\n", stack_name);
}

int	is_sorted(t_node *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

void	radix_sort(t_node **a, t_node **b, int size)
{
	int max_bits;
	int max_num;
	t_node *temp;

	if (is_sorted(*a))
		return;
	max_bits = 0;
	max_num = 0;
	temp = *a;
	while (temp)
	{
		if (temp->value > max_num)
			max_num = temp->value;
		temp = temp->next;
	}
	while ((max_num >> max_bits) != 0)
		max_bits++;
	int i = 0;
	while (i < max_bits)
	{
		int count = size;
		while (count--)
		{
			if (((*a)->value >> i) & 1)
				rotate(a);
			else
				push_to(a, b, 'b');
		}
		while (*b)
			push_to(b, a, 'a');
		i++;
	}
	print_stack(*a, 'A');
}

int	main(int argc, char **argv)
{
	t_node *a;
	t_node *b;
	int		size;

	if (argc < 2)
		return (1);
	a = NULL;
	b = NULL;
	size = argc - 1;
	int i = size;
	while (i > 0)
	{
		a = push(a, atoi(argv[i]));
		i--;
	}
	print_stack(a, 'A');
	if (size > 3)
		radix_sort(&a, &b, size);
	return (0);
}


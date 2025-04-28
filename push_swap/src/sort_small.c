#include "../includes/push_swap.h"

static int	find_min(t_stack *stack)
{
	int	min;

	min = stack->index;
	while (stack)
	{
		if (stack->index < min)
			min = stack->index;
		stack = stack->next;
	}
	return (min);
}

static void	sort_three(t_stack **a)
{
	int	top;
	int	mid;
	int	bottom;

	top = (*a)->index;
	mid = (*a)->next->index;
	bottom = (*a)->next->next->index;
	if (top > mid && mid < bottom && top < bottom)
		sa(a);
	else if (top > mid && mid > bottom && top > bottom)
	{
		sa(a);
		rra(a);
	}
	else if (top > mid && mid < bottom && top > bottom)
		ra(a);
	else if (top < mid && mid > bottom && top < bottom)
	{
		sa(a);
		ra(a);
	}
	else if (top < mid && mid > bottom && top > bottom)
		rra(a);
}

void	sort_small(t_stack **a, t_stack **b)
{
	int	size;

	size = stack_size(*a);
	if (size == 2)
	{
		if ((*a)->index > (*a)->next->index)
			sa(a);
	}
	else if (size == 3)
		sort_three(a);
	else if (size > 3)
	{
		while (stack_size(*a) > 3)
		{
			if ((*a)->index == find_min(*a))
				pb(a, b);
			else
				ra(a);
		}
		sort_three(a);
		while (*b)
			pa(a, b);
	}
}

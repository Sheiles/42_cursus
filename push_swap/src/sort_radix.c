#include "../includes/push_swap.h"

static void	radix_pass(t_stack **a, t_stack **b, int i, int size)
{
	int	j;
	t_stack	*tmp;

	j = 0;
	while (j < size)
	{
		tmp = *a;
		if (((tmp->index >> i) & 1) == 1)
			ra(a);
		else
			pb(a, b);
		j++;
	}
	while (*b)
		pa(a, b);
}

void	radix_sort(t_stack **a, t_stack **b)
{
	int	max_bits;
	int	size;
	int	i;

	size = stack_size(*a);
	max_bits = 0;
	while ((size - 1) >> max_bits)
		max_bits++;
	i = 0;
	while (i < max_bits)
	{
		radix_pass(a, b, i, size);
		i++;
	}
}


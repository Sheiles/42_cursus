











#include "../includes/push_swap.h"

static void	sort_tab(int *tab, int size)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (tab[j] > tab[j + 1])
			{
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static int	*stack_to_tab(t_stack *stack, int size)
{
	int	*tab;
	int	i;

	i = 0;
	tab = malloc(sizeof(int) * size);
	if (!tab)
		return (NULL);
	while (stack)
	{
		tab[i++] = stack->value;
		stack = stack->next;
	}
	return (tab);
}

static void	assign_indices_loop(t_stack *stack, int *tab, int size)
{
	t_stack	*tmp;
	int		i;

	tmp = stack;
	while (tmp)
	{
		i = 0;
		while (i < size)
		{
			if (tmp->value == tab[i])
			{
				tmp->index = i;
				break ;
			}
			i++;
		}
		tmp = tmp->next;
	}
}

void	assign_index(t_stack *stack)
{
	int	*tab;
	int	size;

	size = stack_size(stack);
	tab = stack_to_tab(stack, size);
	if (!tab)
		exit_error(&stack, NULL);
	sort_tab(tab, size);
	assign_indices_loop(stack, tab, size);
	free(tab);
}

#include "../includes/push_swap.h"
#include <unistd.h>

void	exit_error(t_stack **a, t_stack **b)
{
	if (a)
		free_stack(a);
	if (b)
		free_stack(b);
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

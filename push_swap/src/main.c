#include "../includes/push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (argc < 2)
		return (0);
	a = parse_args(argc, argv);
	b = NULL;
	assign_index(a);
	if (!is_sorted(a))
	{
		if (stack_size(a) <= 5)
			sort_small(&a, &b);
		else
			radix_sort(&a, &b);
	}
	free_stack(&a);
	return (0);
}

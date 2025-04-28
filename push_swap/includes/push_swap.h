#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

// Structures
typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

// Stack initialisation
t_stack	*parse_args(int argc, char **argv);
void	assign_index(t_stack *stack);

// Stack operations
void	sa(t_stack **a);
void	sb(t_stack **b);
void	ss(t_stack **a, t_stack **b);
void	pa(t_stack **a, t_stack **b);
void	pb(t_stack **a, t_stack **b);
void	ra(t_stack **a);
void	rb(t_stack **b);
void	rr(t_stack **a, t_stack **b);
void	rra(t_stack **a);
void	rrb(t_stack **b);
void	rrr(t_stack **a, t_stack **b);

// Sorting
void	sort_small(t_stack **a, t_stack **b);
void	radix_sort(t_stack **a, t_stack **b);

// Utilities
int		stack_size(t_stack *stack);
int		is_sorted(t_stack *stack);
int		ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
void	free_split(char **split);

// Error management
void	exit_error(t_stack **a, t_stack **b);
void	free_stack(t_stack **stack);

#endif

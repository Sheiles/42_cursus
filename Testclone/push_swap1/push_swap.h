#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	int				value;
	struct s_node	*next;
}					t_node;

typedef struct s_stack
{
	t_node			*top;
	int				size;
}					t_stack;

t_stack				*init_stack(void);
t_node				*push(t_node *stack, int value);
t_node				*pop(t_node **stack);
void				swap(t_node **stack);
void				rotate(t_node **stack);
void				reverse_rotate(t_node **stack);
void				push_to_stack(t_stack *src, t_stack *dest);
void				sort_stack(t_stack *stack);
void				free_stack(t_stack *stack);
void				push_to(t_node **src, t_node **dest, char stack_name);
void				print_stack(t_node *stack, char name);
int					is_sorted(t_node *stack);
void       radix_sort(t_node **a,t_node **b, int size);

#endif
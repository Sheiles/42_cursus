/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:35:13 by sheiles           #+#    #+#             */
/*   Updated: 2025/05/01 00:39:42 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	is_number(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static void	append_node(t_stack **stack, int value)
{
	t_stack	*new;
	t_stack	*temp;

	new = malloc(sizeof(t_stack));
	if (!new)
		exit_error(stack, NULL);
	new->value = value;
	new->index = -1;
	new->next = NULL;
	if (!*stack)
		*stack = new;
	else
	{
		temp = *stack;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

static void	split_and_fill(t_stack **a, char *arg)
{
	char	**nums;
	int		i;
	long	nb;

	nums = ft_split(arg, ' ');
	if (!nums)
		exit_error(a, NULL);
	i = 0;
	while (nums[i])
	{
		if (!is_number(nums[i]))
			exit_error(a, NULL);
		nb = ft_atoi(nums[i]);
		if (nb > INT_MAX || nb < INT_MIN)
			exit_error(a, NULL);
		append_node(a, (int)nb);
		i++;
	}
	free_split(nums);
}

t_stack	*parse_args(int argc, char **argv)
{
	t_stack		*a;
	int			i;

	a = NULL;
	i = 1;
	while (i < argc)
	{
		split_and_fill(&a, argv[i]);
		i++;
	}
	return (a);
}

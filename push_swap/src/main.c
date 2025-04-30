/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:35:19 by sheiles           #+#    #+#             */
/*   Updated: 2025/05/01 00:35:20 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			sort_chunks(&a, &b);
	}
	free_stack(&a);
	return (0);
}

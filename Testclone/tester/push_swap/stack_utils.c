/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:23:08 by sheiles           #+#    #+#             */
/*   Updated: 2025/02/25 10:01:19 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node *push(t_node *stack, int value)
{
    t_node *new_node = malloc(sizeof(t_node));
    if (!new_node)
        return NULL;
    new_node->value = value;
    new_node->next = stack;
    return new_node;
}

t_node *pop(t_node **stack)
{
    if (!*stack)
        return NULL;
    t_node *top = *stack;
    *stack = (*stack)->next;
    return top;
}

void sort_stack(t_node **stack)
{
    if (!*stack || !(*stack)->next)
        return;
    if ((*stack)->value > (*stack)->next->value)
        swap(stack);
}

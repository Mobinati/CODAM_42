/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtousian <mtousian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 13:05:30 by mtousian          #+#    #+#             */
/*   Updated: 2026/06/09 18:52:08 by mtousian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"
#include <stdio.h>

static void	write_op(char *op)
{
	while (*op)
		write(1, op++, 1);
	write(1, "\n", 1);
}

t_stack	*last_node(t_stack *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

void	add_back(t_stack **stack, t_stack *new)
{
	t_stack	*last;

	if (!new)
		return ;
	if (!*stack)
	{
		*stack = new;
		return ;
	}
	last = last_node(*stack);
	last->next = new;
	new->prev = last;
}

int	is_sorted(t_stack *stack)
{
	if (!stack)
		return (1);
	while (stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

int	stack_size(t_stack *stack)
{
	int	count;

	count = 0;
	while (stack)
	{
		count++;
		stack = stack->next;
	}
	return (count);
}

void	free_stack(t_stack **stack)
{
	t_stack	*next;

	while (stack && *stack)
	{
		next = (*stack)->next;
		free(*stack);
		*stack = next;
	}
}

void	error_exit(t_stack **a, t_stack **b)
{
	free_stack(a);
	free_stack(b);
	write(2, "Error\n", 6);
	exit(1);
}

static void	swap_stack(t_stack **stack)
{
	t_stack	*first;
	t_stack	*second;
	t_stack	*third;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = *stack;
	second = first->next;
	third = second->next;
	second->next = first;
	second->prev = NULL;
	first->prev = second;
	first->next = third;
	if (third)
		third->prev = first;
	*stack = second;
}

void	sa(t_stack **a)
{
	swap_stack(a);
	write_op("sa");
}

void	sb(t_stack **b)
{
	swap_stack(b);
	write_op("sb");
}

void	ss(t_stack **a, t_stack **b)
{
	swap_stack(a);
	swap_stack(b);
	write_op("ss");
}

static void	push_stack(t_stack **src, t_stack **dst)
{
	t_stack	*node;

	if (!src || !*src)
		return ;
	node = *src;
	*src = node->next;
	if (*src)
		(*src)->prev = NULL;
	node->prev = NULL;
	node->next = *dst;
	if (*dst)
		(*dst)->prev = node;
	*dst = node;
}

void	pa(t_stack **a, t_stack **b)
{
	push_stack(b, a);
	write_op("pa");
}

void	pb(t_stack **a, t_stack **b)
{
	push_stack(a, b);
	write_op("pb");
}

static void	rotate_stack(t_stack **stack)
{
	t_stack	*first;
	t_stack	*last;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	first = *stack;
	last = last_node(*stack);
	*stack = first->next;
	(*stack)->prev = NULL;
	last->next = first;
	first->prev = last;
	first->next = NULL;
}

void	ra(t_stack **a)
{
	rotate_stack(a);
	write_op("ra");
}

void	rb(t_stack **b)
{
	rotate_stack(b);
	write_op("rb");
}

void	rr(t_stack **a, t_stack **b)
{
	rotate_stack(a);
	rotate_stack(b);
	write_op("rr");
}

static void	reverse_stack(t_stack **stack)
{
	t_stack	*last;
	t_stack	*before_last;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	last = last_node(*stack);
	before_last = last->prev;
	before_last->next = NULL;
	last->prev = NULL;
	last->next = *stack;
	(*stack)->prev = last;
	*stack = last;
}

void	rra(t_stack **a)
{
	reverse_stack(a);
	write_op("rra");
}

void	rrb(t_stack **b)
{
	reverse_stack(b);
	write_op("rrb");
}

void	rrr(t_stack **a, t_stack **b)
{
	reverse_stack(a);
	reverse_stack(b);
	write_op("rrr");
}

void print_stack(t_stack *stack)
{
    while (stack)
    {
        printf("%ld\n", stack->value);
        stack = stack->next;
    }
}
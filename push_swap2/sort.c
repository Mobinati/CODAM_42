/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtousian <mtousian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 18:50:00 by mtousian          #+#    #+#             */
/*   Updated: 2026/06/09 18:50:00 by mtousian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	assign_indexes(t_stack *stack)
{
	t_stack	*current;
	t_stack	*compare;
	long	index;

	current = stack;
	while (current)
	{
		index = 0;
		compare = stack;
		while (compare)
		{
			if (compare->value < current->value)
				index++;
			compare = compare->next;
		}
		current->index = index;
		current = current->next;
	}
}

static int	min_position(t_stack *stack)
{
	int		pos;
	int		min_pos;
	long	min_index;

	pos = 0;
	min_pos = 0;
	min_index = stack->index;
	while (stack)
	{
		if (stack->index < min_index)
		{
			min_index = stack->index;
			min_pos = pos;
		}
		pos++;
		stack = stack->next;
	}
	return (min_pos);
}

static void	push_min_to_b(t_stack **a, t_stack **b)
{
	int	pos;
	int	size;

	pos = min_position(*a);
	size = stack_size(*a);
	if (pos <= size / 2)
		while (pos-- > 0)
			ra(a);
	else
		while (pos++ < size)
			rra(a);
	pb(a, b);
}

static void	sort_three(t_stack **a)
{
	long	first;
	long	second;
	long	third;

	if (is_sorted(*a))
		return ;
	first = (*a)->index;
	second = (*a)->next->index;
	third = (*a)->next->next->index;
	if (first > second && second < third && first < third)
		sa(a);
	else if (first > second && second > third)
	{
		sa(a);
		rra(a);
	}
	else if (first > second && second < third && first > third)
		ra(a);
	else if (first < second && second > third && first < third)
	{
		sa(a);
		ra(a);
	}
	else if (first < second && second > third && first > third)
		rra(a);
}

static void	sort_small(t_stack **a, t_stack **b, int size)
{
	if (size == 2)
	{
		if ((*a)->value > (*a)->next->value)
			sa(a);
		return ;
	}
	while (stack_size(*a) > 3)
		push_min_to_b(a, b);
	sort_three(a);
	while (*b)
		pa(a, b);
}

static void	sort_radix(t_stack **a, t_stack **b)
{
	int	size;
	int	max_bits;
	int	bit;
	int	i;

	size = stack_size(*a);
	max_bits = 0;
	while ((size - 1) >> max_bits)
		max_bits++;
	bit = 0;
	while (bit < max_bits)
	{
		i = 0;
		while (i++ < size)
		{
			if (((*a)->index >> bit) & 1)
				ra(a);
			else
				pb(a, b);
		}
		while (*b)
			pa(a, b);
		bit++;
	}
}

void	sort_stack(t_stack **a, t_stack **b)
{
	int	size;

	size = stack_size(*a);
	if (size <= 1 || is_sorted(*a))
		return ;
	if (size <= 5)
		sort_small(a, b, size);
	else
		sort_radix(a, b);
}

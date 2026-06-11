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

static double	disorder_ratio(t_stack *stack, int size)
{
	int	inversions;

	inversions = 0;
	while (stack && stack->next)
	{
		if (stack->index > stack->next->index)
			inversions++;
		stack = stack->next;
	}
	return ((double)inversions / (double)size);
}

static int	index_position(t_stack *stack, long index)
{
	int	pos;

	pos = 0;
	while (stack)
	{
		if (stack->index == index)
			return (pos);
		pos++;
		stack = stack->next;
	}
	return (-1);
}

static int	min_index(t_stack *stack)
{
	long	min;

	min = stack->index;
	while (stack)
	{
		if (stack->index < min)
			min = stack->index;
		stack = stack->next;
	}
	return ((int)min);
}

static int	max_index(t_stack *stack)
{
	long	max;

	max = stack->index;
	while (stack)
	{
		if (stack->index > max)
			max = stack->index;
		stack = stack->next;
	}
	return ((int)max);
}

static void	rotate_index_to_top(t_stack **stack, long index, char name)
{
	int	pos;
	int	size;

	pos = index_position(*stack, index);
	size = stack_size(*stack);
	if (pos <= size / 2)
	{
		while (pos-- > 0)
		{
			if (name == 'a')
				ra(stack);
			else
				rb(stack);
		}
	}
	else
	{
		while (pos++ < size)
		{
			if (name == 'a')
				rra(stack);
			else
				rrb(stack);
		}
	}
}

void	sort_selection(t_stack **a, t_stack **b)
{
	while (*a)
	{
		rotate_index_to_top(a, min_index(*a), 'a');
		pb(a, b);
	}
	while (*b)
		pa(a, b);
}

static int	sort_window(int size)
{
	if (size <= 100)
		return (15);
	return (30);
}

static void	push_window_to_b(t_stack **a, t_stack **b, int size)
{
	int	pushed;
	int	window;

	pushed = 0;
	window = sort_window(size);
	while (*a)
	{
		if ((*a)->index <= pushed)
		{
			pb(a, b);
			pushed++;
			if (*a && (*a)->index > pushed + window)
				rr(a, b);
			else
				rb(b);
		}
		else if ((*a)->index <= pushed + window)
		{
			pb(a, b);
			pushed++;
		}
		else
			ra(a);
	}
}

static void	rebuild_a_from_b(t_stack **a, t_stack **b)
{
	while (*b)
	{
		rotate_index_to_top(b, max_index(*b), 'b');
		pa(a, b);
	}
}

void	sort_chunks(t_stack **a, t_stack **b)
{
	int	size;

	size = stack_size(*a);
	push_window_to_b(a, b, size);
	rebuild_a_from_b(a, b);
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

void	sort_adaptive(t_stack **a, t_stack **b)
{
	int		size;
	double	disorder;

	size = stack_size(*a);
	if (size <= 1 || is_sorted(*a))
		return ;
	if (size <= 5)
	{
		sort_small(a, b, size);
		return ;
	}
	disorder = disorder_ratio(*a, size);
	if (disorder < 0.2 || size <= 50)
		sort_selection(a, b);
	else if (size <= 500)
		sort_chunks(a, b);
	else
		sort_radix(a, b);
}

void	sort_stack(t_stack **a, t_stack **b)
{
	sort_adaptive(a, b);
}

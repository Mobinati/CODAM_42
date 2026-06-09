/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtousian <mtousian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 13:05:30 by mtousian          #+#    #+#             */
/*   Updated: 2026/06/09 16:23:17 by mtousian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/*input: pointer for first node. output: pointer to last node*/
t_stack *last_node(t_stack	*stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

/* (stack points to a) a = *stack => &a = **stack 
input: adress to stack pointer, pointer to the appending node
no output
*/
void	add_back(t_stack **stack, t_stack *new)
{
	t_stack	*last;

	if (!*stack)
	{
		*stack = new;
		return;
	}
	last = last_node(*stack);
	last->next = new;
	new->prev = last;
}

/*input: poniter to first node; output: none*/


void	print_stack(t_stack	*stack)
{
	while (stack)
	{
		printf("%ld\n", stack->value);
		stack = stack->next;
	}
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


int	stack_size(t_stack	*stack)
{
	int	count;

	count = 0;
	while(stack)
	{
		count++;
		stack = stack->next;
	}
	return (count);
}

/* (swap a): Swap the first two elements at the top of stack a.
Do nothing if there is only one or no elements.*/
void	sa(t_stack	**a)
{
	t_stack	*first;
	t_stack	*second;
	t_stack	*third;

	if (!a || !*a || !(*a)->next)
		return ;
	
	first = *a;
	second = first->next;
	third = second->next;

	second->next = first;
	first->prev = second;
	
	first->next = third;

	if (third)
		third->prev = first;
	
	second->prev = NULL;

	*a = second;
}

/* (swap b): Swap the first two elements at the top of stack b*/
void	sb(t_stack	**b)
{
	t_stack	*first;
	t_stack	*second;
	t_stack	*third;

	if (!b || !*b || !(*b)->next)
		return ;
	
	first = *b;
	second = first->next;
	third = second->next;

	second->next = first;
	first->prev = second;
	
	first->next = third;

	if (third)
		third->prev = first;
	
	second->prev = NULL;

	*b = second;
}

/*sa and sb at the same time*/
void	ss(t_stack **a, t_stack	**b)
{
	sa(a);
	sb(b);
}

/*(push a): Take the first element at the top of b and put it at the top of a.
Do nothing if b is empty.*/
void	pa(t_stack	**a, t_stack	**b)
{
	t_stack	*node;
	if (!b || !*b)
		return ;

	node = *b;
	*b = node->next;
	
	if(*b)
		(*b)->prev = NULL;
	
	/*isolating node from b stack to be attached to a stack*/
	node->prev = NULL;
	
	node->next = *a;
	if (*a)
		(*a)->prev = node;
	
	*a = node;
}

/*(push b): Take the first element at the top of a and put it at the top of b.*/
void	pb(t_stack	**a, t_stack	**b)
{
	t_stack	*node;

	if (!a || !*a)
		return ;

	node = *a;
	*a = node->next;
	
	if(*a)
		(*a)->prev = NULL;
	
	/*isolating node from b stack to be attached to a stack*/
	node->prev = NULL;
	
	node->next = *b;
	if (*b)
		(*b)->prev = node;
	
	*b = node;
}

/*ra (rotate a): Shift up all elements of stack a by one.
The first element becomes the last one.*/
void	ra(t_stack	**a)
{
	t_stack	*first;
	t_stack	*last;

	if (!a || !*a || !(*a)->next)
		return ;
	
	first = *a;
	last = *a;
	
	while(last->next)
		last = last->next;

	*a = first->next;
	(*a)->prev = NULL;

	last->next = first;
	first->prev = last;
	first->next = NULL;
}

/*rb (rotate b): Shift up all elements of stack b by one.*/
void	rb(t_stack	**b)
{
	t_stack	*first;
	t_stack	*last;

	if (!b || !*b || !(*b)->next)
		return ;
	
	first = *b;
	last = *b;
	
	while(last->next)
		last = last->next;

	*b = first->next;
	(*b)->prev = NULL;

	last->next = first;
	first->prev = last;
	first->next = NULL;
}

/*rr = ra and rb at thw same time*/
void	rr(t_stack	**a, t_stack	**b)
{
	ra(a);
	rb(b);
}

/*(reverse rotate a): Shift down all elements of stack a by one.
The last element becomes the first one.*/
void	rra(t_stack	**a)
{
	t_stack	*last;
	t_stack	*last_second;

	if (!a || !*a || !(*a)->next)
		return ;
	
	last = *a;
	
	while(last->next)
		last = last->next;

	last_second = last->prev;
	last_second->next = NULL;

	last->next = *a;
	(*a)->prev = last;
	last->prev = NULL;
	
	*a = last;
}

/*(reverse rotate b): Shift down all elements of stack a by one.*/
void	rrb(t_stack	**b)
{
	t_stack	*last;
	t_stack	*last_second;

	if (!b || !*b || !(*b)->next)
		return ;
	
	last = *b;
	
	while(last->next)
		last = last->next;

	last_second = last->prev;
	last_second->next = NULL;

	last->next = *b;
	(*b)->prev = last;
	last->prev = NULL;
	
	*b = last;
}

/*rrr= rra and rrb at the same time*/
void	rrr(t_stack	**a, t_stack	**b)
{
	rra(a);
	rrb(b);
}
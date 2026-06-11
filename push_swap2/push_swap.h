/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtousian <mtousian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 20:45:52 by mtousian          #+#    #+#             */
/*   Updated: 2026/06/09 18:47:28 by mtousian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
	long	value;
	long	index;
	struct	s_stack	*next;
	struct	s_stack	*prev;
}	t_stack;

/*Mobina: we have a function; (last_node(...). gets a pointer to a stack node,
returns a pointer to a node (t_stack *)). which means:
“Function receives beginning of linked list and returns the last node.”
for add_back: “Function receives stack and node, then attaches node to end.”
t_stack ** : Address of pointer to node. Used when function must modify original pointer.
t_stack *: Address of node. (pointer to node)
t_stack: actual node.
*/

t_stack	*new_node(long	value);
t_stack	*last_node(t_stack	*stack);
void	add_back(t_stack	**stack, t_stack	*new);
void	print_stack(t_stack *stack);
int		is_sorted(t_stack *stack);
int		stack_size(t_stack	*stack);
void	free_stack(t_stack **stack);
int		parse_args(int argc, char **argv, t_stack **a);
void	assign_indexes(t_stack *stack);
void	sort_stack(t_stack **a, t_stack **b);
void	error_exit(t_stack **a, t_stack **b);
void	sa(t_stack	**a);
void	sb(t_stack	**b);
void	ss(t_stack **a, t_stack	**b);
void	pa(t_stack	**a, t_stack	**b);
void	pb(t_stack	**a, t_stack	**b);
void	ra(t_stack	**a);
void	rb(t_stack	**b);
void	rr(t_stack	**a, t_stack	**b);
void	rra(t_stack	**a);
void	rrb(t_stack	**b);
void	rrr(t_stack	**a, t_stack	**b);

#endif

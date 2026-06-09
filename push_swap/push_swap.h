/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtousian <mtousian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 20:45:52 by mtousian          #+#    #+#             */
/*   Updated: 2026/05/15 21:57:37 by mtousian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdlib.h>
#include <stdio.h>

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
void	print_stack(t_stack	*stack);

#endif
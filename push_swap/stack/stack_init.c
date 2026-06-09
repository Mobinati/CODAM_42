/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtousian <mtousian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:42:56 by mtousian          #+#    #+#             */
/*   Updated: 2026/05/15 21:58:02 by mtousian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

t_stack	*new_node(long value)
{
	t_stack	*node;
	
	node = malloc(sizeof(t_stack));
	if (!node)
		return (NULL);
	node->value = value;
	node->index = 0;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
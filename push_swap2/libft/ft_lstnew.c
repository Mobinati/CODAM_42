/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtousian <mtousian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 20:57:15 by mtousian          #+#    #+#             */
/*   Updated: 2026/04/26 21:33:38 by mtousian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nude;

	nude = (t_list *)malloc(sizeof (t_list));
	if (!nude)
		return (NULL);
	nude -> content = content;
	nude -> next = NULL;
	return (nude);
}

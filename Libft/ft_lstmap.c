/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtousian <mtousian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 20:56:37 by mtousian          #+#    #+#             */
/*   Updated: 2026/04/27 16:24:14 by mtousian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*current;
	void	*content;

	if (!lst || !f)
		return (NULL);
	head = NULL;
	while (lst)
	{
		if (lst != NULL)
		{
			content = f(lst->content);
			current = ft_lstnew(content);
			if (!current)
			{
				ft_lstclear(&head, del);
				return (NULL);
			}
			ft_lstadd_back(&head, current);
		}
		lst = lst->next;
	}
	return (head);
}

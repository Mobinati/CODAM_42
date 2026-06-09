/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtousian <mtousian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 20:59:13 by mtousian          #+#    #+#             */
/*   Updated: 2026/04/26 21:33:41 by mtousian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*source;

	i = 0;
	source = (char *)s;
	while (i < n)
	{
		if (source[i] == (char)c)
			return ((char *)&source[i]);
		i++;
	}
	return (NULL);
}

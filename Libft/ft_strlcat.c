/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtousian <mtousian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 18:13:20 by mtousian          #+#    #+#             */
/*   Updated: 2026/04/26 21:41:43 by mtousian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < size && dst[i])
		i++;
	while (src[j] && (i + j + 1) < size)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < size)
		dst[i + j] = '\0';
	while (src[j])
		j++;
	return (i + j);
}

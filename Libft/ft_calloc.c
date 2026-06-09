/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtousian <mtousian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 21:46:25 by mtousian          #+#    #+#             */
/*   Updated: 2026/04/27 16:11:51 by mtousian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;

	if (nmemb != 0 && size > SIZE_MAX / nmemb)
		return (NULL);
	result = (void *)malloc(nmemb * size);
	if (!result)
		return (NULL);
	ft_bzero(result, nmemb * size);
	return (result);
}

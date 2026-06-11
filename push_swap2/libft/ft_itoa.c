/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtousian <mtousian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 20:49:38 by mtousian          #+#    #+#             */
/*   Updated: 2026/04/26 21:47:50 by mtousian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_len(int n)
{
	size_t	len;

	if (n > 0)
		len = 0;
	else
		len = 1;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	long	nb;
	char	*str;

	len = count_len(n);
	nb = n;
	if (n < 0)
		nb *= -1;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	*(str + len--) = '\0';
	while (nb > 0)
	{
		*(str + len--) = nb % 10 + '0';
		nb /= 10;
	}
	if (len == 0 && str[1] == '\0')
		*(str + len) = '0';
	else if (len == 0 && str[1])
		*(str + len) = '-';
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtousian <mtousian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 20:17:23 by mtousian          #+#    #+#             */
/*   Updated: 2026/04/26 21:34:28 by mtousian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*last;
	char	x;

	i = 0;
	last = NULL;
	x = (char)c;
	while (s[i])
	{
		if (s[i] == x)
			last = (char *)&s[i];
		i++;
	}
	if (x == '\0')
		return ((char *)&s[i]);
	return (last);
}

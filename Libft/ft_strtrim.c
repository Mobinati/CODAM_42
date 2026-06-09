/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtousian <mtousian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 20:36:42 by mtousian          #+#    #+#             */
/*   Updated: 2026/04/26 21:34:30 by mtousian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	begin;
	size_t	end;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	begin = 0;
	end = (ft_strlen(s1) - 1);
	while (s1[begin] && ft_strchr(set, s1[begin]))
		begin++;
	while (s1[begin] && ft_strchr(set, s1[end]))
		end--;
	str = ft_substr(s1, begin, ((end - begin) + 1));
	return (str);
}

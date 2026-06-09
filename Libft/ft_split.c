/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtousian <mtousian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 20:34:14 by mtousian          #+#    #+#             */
/*   Updated: 2026/04/27 20:56:03 by mtousian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	word_count(const char *str, char c)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static unsigned int	word_len(char const *s, char c)
{
	unsigned int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**free_all(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		j;

	res = malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!s || !res)
		return (0);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			res[j] = ft_substr(s, i, word_len(&s[i], c));
			if (!res[j])
				return (free_all(res, j));
			j++;
			i = i + word_len(&s[i], c);
		}
		else
			i++;
	}
	res[j] = 0;
	return (res);
}

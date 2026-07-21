/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobina <mobina@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 00:00:00 by mobina            #+#    #+#             */
/*   Updated: 2026/07/21 00:00:00 by mobina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *string)
{
	size_t	length;

	length = 0;
	if (!string)
		return (0);
	while (string[length])
		length++;
	return (length);
}

char	*gnl_strchr(const char *string, int character)
{
	if (!string)
		return (NULL);
	while (*string)
	{
		if (*string == (char)character)
			return ((char *)string);
		string++;
	}
	if ((char)character == '\0')
		return ((char *)string);
	return (NULL);
}

char	*gnl_strjoin(char *left, const char *right)
{
	char	*joined;
	size_t	left_length;
	size_t	right_length;
	size_t	index;

	left_length = gnl_strlen(left);
	right_length = gnl_strlen(right);
	joined = malloc(left_length + right_length + 1);
	if (!joined)
	{
		free(left);
		return (NULL);
	}
	index = 0;
	while (index < left_length)
	{
		joined[index] = left[index];
		index++;
	}
	while (index < left_length + right_length)
	{
		joined[index] = right[index - left_length];
		index++;
	}
	joined[index] = '\0';
	free(left);
	return (joined);
}

char	*gnl_substr(const char *string, size_t start, size_t length)
{
	char	*substring;
	size_t	index;

	if (!string || start > gnl_strlen(string))
		return (NULL);
	if (length > gnl_strlen(string + start))
		length = gnl_strlen(string + start);
	substring = malloc(length + 1);
	if (!substring)
		return (NULL);
	index = 0;
	while (index < length)
	{
		substring[index] = string[start + index];
		index++;
	}
	substring[index] = '\0';
	return (substring);
}

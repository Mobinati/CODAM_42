/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobina <mobina@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 00:00:00 by mobina            #+#    #+#             */
/*   Updated: 2026/07/21 00:00:00 by mobina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_to_stash(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (free(stash), NULL);
	bytes_read = 1;
	while (!gnl_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = gnl_strjoin(stash, buffer);
		if (!stash)
		{
			free(buffer);
			return (free(stash), NULL);
		}
	}
	free(buffer);
	return (stash);
}

static char	*extract_line(char **stash)
{
	char	*newline;
	char	*line;
	char	*remaining;

	newline = gnl_strchr(*stash, '\n');
	if (!newline)
	{
		line = *stash;
		*stash = NULL;
		return (line);
	}
	line = gnl_substr(*stash, 0, (size_t)(newline - *stash) + 1);
	if (!line)
		return (free(*stash), *stash = NULL, NULL);
	remaining = gnl_substr(newline + 1, 0, gnl_strlen(newline + 1));
	if (!remaining)
		return (free(line), free(*stash), *stash = NULL, NULL);
	free(*stash);
	*stash = remaining;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (free(stash), stash = NULL, NULL);
	stash = read_to_stash(fd, stash);
	if (!stash || !*stash)
		return (free(stash), stash = NULL, NULL);
	return (extract_line(&stash));
}

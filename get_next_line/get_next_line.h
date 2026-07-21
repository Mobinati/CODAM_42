/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobina <mobina@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/21 00:00:00 by mobina            #+#    #+#             */
/*   Updated: 2026/07/21 00:00:00 by mobina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
size_t	gnl_strlen(const char *string);
char	*gnl_strchr(const char *string, int character);
char	*gnl_strjoin(char *left, const char *right);
char	*gnl_substr(const char *string, size_t start, size_t length);

#endif

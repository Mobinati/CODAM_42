/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobina <mobina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 00:00:00 by mobina            #+#    #+#             */
/*   Updated: 2026/07/13 00:00:00 by mobina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_print_char(char character)
{
	int	written;

	written = write(1, &character, 1);
	return (written);
}

int	ft_print_string(const char *string)
{
	int	count;

	if (string == NULL)
		string = "(null)";
	count = 0;
	while (string[count] != '\0')
	{
		if (ft_print_char(string[count]) < 0)
			return (PRINT_ERROR);
		count++;
	}
	return (count);
}

int	ft_print_number(unsigned long number, const char *base)
{
	unsigned long	base_length;
	int				count;
	int				printed;

	base_length = 0;
	while (base[base_length] != '\0')
		base_length++;
	count = 0;
	if (number >= base_length)
	{
		printed = ft_print_number(number / base_length, base);
		if (printed < 0)
			return (printed);
		count += printed;
	}
	printed = ft_print_char(base[number % base_length]);
	if (printed < 0)
		return (printed);
	return (count + printed);
}

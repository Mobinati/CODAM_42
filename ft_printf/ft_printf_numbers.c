/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_numbers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobina <mobina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 00:00:00 by mobina            #+#    #+#             */
/*   Updated: 2026/07/13 00:00:00 by mobina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_integer(int number)
{
	long	value;
	int		count;
	int		printed;

	value = number;
	count = 0;
	if (value < 0)
	{
		printed = ft_print_char('-');
		if (printed < 0)
			return (printed);
		count = 1;
		value = -value;
	}
	printed = ft_print_number((unsigned long)value, DECIMAL);
	if (printed < 0)
		return (printed);
	return (count + printed);
}

int	ft_print_pointer(void *pointer)
{
	int	printed;

	if (pointer == NULL)
		return (ft_print_string("(nil)"));
	printed = ft_print_string("0x");
	if (printed < 0)
		return (printed);
	printed = ft_print_number((unsigned long)pointer, HEX_LOW);
	if (printed < 0)
		return (printed);
	return (2 + printed);
}

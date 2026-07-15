/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobina <mobina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 00:00:00 by mobina            #+#    #+#             */
/*   Updated: 2026/07/13 00:00:00 by mobina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_convert(char type, va_list *args)
{
	if (type == 'c')
		return (ft_print_char(va_arg(*args, int)));
	if (type == 's')
		return (ft_print_string(va_arg(*args, char *)));
	if (type == 'p')
		return (ft_print_pointer(va_arg(*args, void *)));
	if (type == 'd' || type == 'i')
		return (ft_print_integer(va_arg(*args, int)));
	if (type == 'u')
		return (ft_print_number(va_arg(*args, unsigned int), DECIMAL));
	if (type == 'x')
		return (ft_print_number(va_arg(*args, unsigned int), HEX_LOW));
	if (type == 'X')
		return (ft_print_number(va_arg(*args, unsigned int), HEX_UP));
	if (type == '%')
		return (ft_print_char('%'));
	return (PRINT_ERROR);
}

static int	ft_print_format(const char *format, va_list *args)
{
	int	count;
	int	len;

	count = 0;
	while (*format != '\0')
	{
		if (*format == '%' && format[1] != '\0')
			len = ft_convert(*(++format), args);
		else if (*format == '%')
			return (PRINT_ERROR);
		else
			len = ft_print_char(*format);
		if (len < 0)
			return (len);
		count += len;
		format++;
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	arguments;
	int		count;

	if (format == NULL)
		return (PRINT_ERROR);
	va_start(arguments, format);
	count = ft_print_format(format, &arguments);
	va_end(arguments);
	return (count);
}

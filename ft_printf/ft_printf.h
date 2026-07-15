/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobina <mobina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 00:00:00 by mobina            #+#    #+#             */
/*   Updated: 2026/07/13 00:00:00 by mobina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>

# define DECIMAL "0123456789"
# define HEX_LOW "0123456789abcdef"
# define HEX_UP "0123456789ABCDEF"
# define PRINT_ERROR -1

int	ft_printf(const char *format, ...);
int	ft_print_char(char character);
int	ft_print_string(const char *string);
int	ft_print_number(unsigned long number, const char *base);
int	ft_print_integer(int number);
int	ft_print_pointer(void *pointer);

#endif

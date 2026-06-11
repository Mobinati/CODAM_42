/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtousian <mtousian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 18:50:00 by mtousian          #+#    #+#             */
/*   Updated: 2026/06/09 18:50:00 by mtousian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

static int	has_value(t_stack *stack, long value)
{
	while (stack)
	{
		if (stack->value == value)
			return (1);
		stack = stack->next;
	}
	return (0);
}

static int	parse_number(char *str, int *i, long *value)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	if (str[*i] < '0' || str[*i] > '9')
		return (0);
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		result = result * 10 + (str[*i] - '0');
		if ((sign == 1 && result > INT_MAX)
			|| (sign == -1 && -result < INT_MIN))
			return (0);
		(*i)++;
	}
	*value = result * sign;
	return (1);
}

static int	add_value(t_stack **a, long value)
{
	t_stack	*node;

	if (has_value(*a, value))
		return (0);
	node = new_node(value);
	if (!node)
		return (0);
	add_back(a, node);
	return (1);
}

static int	parse_one_arg(char *arg, t_stack **a)
{
	int		i;
	int		found;
	long	value;

	i = 0;
	found = 0;
	while (arg[i])
	{
		while (is_space(arg[i]))
			i++;
		if (!arg[i])
			break ;
		if (!parse_number(arg, &i, &value))
			return (0);
		if (arg[i] && !is_space(arg[i]))
			return (0);
		if (!add_value(a, value))
			return (0);
		found = 1;
	}
	return (found);
}

int	parse_args(int argc, char **argv, t_stack **a)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!argv[i] || !parse_one_arg(argv[i], a))
			return (0);
		i++;
	}
	return (*a != NULL);
}

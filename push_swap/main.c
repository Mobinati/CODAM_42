/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtousian <mtousian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 21:36:51 by mtousian          #+#    #+#             */
/*   Updated: 2026/05/15 22:00:56 by mtousian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int	argc, char	**argv)
{
	t_stack	*a;
	int		i;
	a = NULL;
	i = 1;
	while (i < argc)
	{
		add_back(&a, new_node(atoi(argv[i])));
		i++;
	}
	print_stack(a);
}
/*mobina: check this site and its methodology:
 https://medium.com/@ayogun/push-swap-c1f5d2d41e97*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:19:42 by secros            #+#    #+#             */
/*   Updated: 2025/03/27 12:56:51 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include "bt_malloc.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
	{
		write (2, "Error\nWrong arguement\n[nb_philo], [t_die], \
[t_eat], [t_sleep], ([nb_to_eat])", 77);
		return (1);
	}
	while (--ac)
	{
		if (!all_digit(av[ac]))
		{
			write (2, "Error\nParam can only contain numeric value", 43);
			return (1);
		}
	}
	if (assign_param(&data.param, av))
	{
		write (2, "Error\nNumber must be positive and size of (unsigned int)"\
			, 57);
		return (1);
	}
	if (start(&data) != 0)
	{
		write (2, "Error\nSomething went wrong\n", 28);
		do_dishes(get_sink(NULL));
		return (1);
	}
}

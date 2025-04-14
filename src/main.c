/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:19:42 by secros            #+#    #+#             */
/*   Updated: 2025/04/14 10:07:42 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	print_error(enum e_error type)
{
	if (type == AC)
		write (2, "Error\nWrong argument\n[nb_philo], [t_die], \
[t_eat], [t_sleep], ([nb_to_eat])", 77);
	if (type == DIGIT)
		write (2, "Error\nParam can only contain numeric value", 43);
	if (type == VALUE)
		write (2, "Error\nNumbers must be positive and size of (unsigned int) \
also philo can't exceed 10000", 88);
	if (type == START)
	{
		write (2, "Error\nSomething went wrong\n", 28);
		do_dishes(get_sink(NULL));
	}
	return (type);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (print_error(AC));
	while (--ac)
		if (!all_digit(av[ac]))
			return (print_error(DIGIT));
	if (assign_param(&data.param, av))
		return (print_error(VALUE));
	if (start(&data) != 0)
		return (print_error(START));
	return (0);
}

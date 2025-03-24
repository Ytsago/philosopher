/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:19:42 by secros            #+#    #+#             */
/*   Updated: 2025/03/24 16:22:26 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include "bt_malloc.h"
#include <stdio.h>

/**
 * @brief Assign AV to each param using ui_atoi
 * 
 * @param param t_param struct
 * @param av User input
 * @return int --> Error is set to 1 in case of overflow or negative
 */
int	assign_param(t_param *param, char **av)
{
	char	error;

	error = 0;
	param->nb_philo = quick_atoi(av[1], &error);
	param->t_die = quick_atoi(av[2], &error);
	param->t_eat = quick_atoi(av[3], &error);
	param->t_sleep = quick_atoi(av[4], &error);
	if (av[5])
		param->nb_to_eat = quick_atoi(av[5], &error);
	else
		param->nb_to_eat = 0;
	return (error);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = args;
	printf("Hello from philo %d\n", philo->philo);
	return (NULL);
}

// int	creat_philo(t_philo **)

int	start(t_data *data)
{
	pthread_t	*th;
	size_t		nb_th;

	nb_th = 0;
	data->philo = new_plate((sizeof(t_philo) * data->param.nb_philo), get_sink(NULL));
	th = new_plate(sizeof(pthread_t) * data->param.nb_philo, get_sink(NULL));
	while (nb_th < data->param.nb_philo)
	{
		data->philo[nb_th].philo = nb_th;
		if(pthread_create(&th[nb_th], NULL, &routine, &data->philo[nb_th]) != 0)
			return (1);
		nb_th++;
	}
	nb_th = 0;
	while (nb_th < data->param.nb_philo)
	{
		pthread_join(th[nb_th], NULL);
		nb_th++;
	}
	do_dishes(get_sink(NULL));
	return (0);
}

/**
 * @brief 
 * 
 * @param ac 
 * @param av nb_philo, t_die, t_eat, t_sleep, (nb_to_eat) 
 * @return int 
 */
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
	start(&data);
}

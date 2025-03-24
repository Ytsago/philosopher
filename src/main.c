/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:19:42 by secros            #+#    #+#             */
/*   Updated: 2025/03/24 17:00:51 by secros           ###   ########.fr       */
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
	pthread_mutex_lock(&philo->lock->start);
	pthread_mutex_unlock(&philo->lock->start);
	pthread_mutex_lock(&philo->lock->printing);
	printf("Hello from philo %d\n", philo->philo);
	pthread_mutex_unlock(&philo->lock->printing);
	return (NULL);
}

void	philo_init(t_data *data)
{
	size_t	nb;

	nb = data->param.nb_philo;
	while (nb--)
	{
		data->philo[nb].lock = &data->lock;
		data->philo[nb].param = &data->param;
	}
}

int	alloc_init(t_data *data)
{
	data->philo = new_plate((sizeof(t_philo) * data->param.nb_philo), get_sink(NULL));
	if (!data->philo)
		return (1);
	if (pthread_mutex_init(&data->lock.start, NULL) != 0)
		return (1);
	fill_dishwasher(&data->lock.start, (void (*)(void *))pthread_mutex_destroy, get_sink(NULL));
	if (pthread_mutex_init(&data->lock.printing, NULL) != 0)
		return (1);
	fill_dishwasher(&data->lock.printing, (void (*)(void *))pthread_mutex_destroy, get_sink(NULL));
	return (0);
}

int	start(t_data *data)
{
	pthread_t	*th;
	size_t		nb_th;

	nb_th = 0;
	if (alloc_init(data))
		return (1);
	th = new_plate(sizeof(pthread_t) * data->param.nb_philo, get_sink(NULL));
	philo_init(data);
	pthread_mutex_lock(&data->lock.start);
	while (nb_th < data->param.nb_philo)
	{
		data->philo[nb_th].philo = nb_th;
		if(pthread_create(&th[nb_th], NULL, &routine, &data->philo[nb_th]) != 0)
			return (1);
		nb_th++;
	}
	nb_th = 0;
	pthread_mutex_unlock(&data->lock.start);
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
	if (start(&data))
	{
		write (2, "Error\nSomething went wrong\n", 28);
		do_dishes(get_sink(NULL));
		return (1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:41:07 by secros            #+#    #+#             */
/*   Updated: 2025/03/27 12:48:53 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include "bt_malloc.h"

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
		param->nb_to_eat = -1;
	return (error);
}

void	philo_init(t_data *data)
{
	size_t	nb;
	size_t	i;

	nb = data->param.nb_philo;
	i = 0;
	while (i < nb)
	{
		data->philo[i].lock = &data->lock;
		data->philo[i].param = &data->param;
		data->philo[i].r_fork = &data->philo[(i + 1) % nb].l_fork;
		i++;
	}
}

int	alloc_init(t_data *data)
{
	data->philo = new_plate((sizeof(t_philo) * data->param.nb_philo), \
	get_sink(NULL));
	if (!data->philo)
		return (1);
	if (pthread_mutex_init(&data->lock.start, NULL) != 0)
		return (1);
	fill_dishwasher(&data->lock.start, (void (*)(void *))pthread_mutex_destroy, \
	get_sink(NULL));
	if (pthread_mutex_init(&data->lock.printing, NULL) != 0)
		return (1);
	fill_dishwasher(&data->lock.printing, (void (*)(void *)) \
	pthread_mutex_destroy, get_sink(NULL));
	return (0);
}
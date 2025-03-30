/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:52:32 by secros            #+#    #+#             */
/*   Updated: 2025/03/30 12:30:23 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <stdio.h>
#include "bt_malloc.h"

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

int	start(t_data *data)
{
	pthread_t	*th;
	size_t		error;

	if (alloc_init(data))
		return (1);
	th = new_plate(sizeof(pthread_t) * data->param.nb_philo, get_sink(NULL));
	if (!th)
		return (1);
	philo_init(data);
	pthread_mutex_lock(&data->lock.start);
	error = launch_thread(data, th);
	if (error)
		destroy_thread(data, th, error);
	pthread_mutex_unlock(&data->lock.start);
	if (!fill_dishwasher(data->philo, free, get_sink(NULL)))
		return (1);
	destroy_thread(data, th, 0);
	return (0);
}

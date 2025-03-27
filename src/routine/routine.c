/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:52:32 by secros            #+#    #+#             */
/*   Updated: 2025/03/27 12:56:41 by secros           ###   ########.fr       */
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
	size_t		nb_th;

	nb_th = 0;
	if (alloc_init(data))
		return (1);
	th = new_plate(sizeof(pthread_t) * data->param.nb_philo, get_sink(NULL));
	philo_init(data);
	pthread_mutex_lock(&data->lock.start);
	while (nb_th < data->param.nb_philo)
	{
		data->philo[nb_th].philo = nb_th + 1;
		if (pthread_create(&th[nb_th], NULL, &routine, \
		&data->philo[nb_th]) != 0)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:52:32 by secros            #+#    #+#             */
/*   Updated: 2025/03/30 18:53:19 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*wait_return(void)
{
	usleep(1000);
	return (NULL);
}

void	*routine(void *args)
{
	t_philo			*philo;

	philo = args;
	pthread_mutex_lock(&philo->lock->start);
	pthread_mutex_unlock(&philo->lock->start);
	gettimeofday(&philo->last_meal, NULL);
	while (1)
	{
		if (is_a_philo_dead(philo))
			return(wait_return);
		thinking(philo);
		if (try_to_eat(philo))
			return(wait_return);
		if (sleeping(philo) != 0)
			return(wait_return);
	}
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
	if (philo_init(data))
		return (1);
	pthread_mutex_lock(&data->lock.start);
	error = launch_thread(data, th);
	if (error != 0)
	{
		data->param.dead = 1;
		pthread_mutex_unlock(&data->lock.start);
		destroy_thread(data, th, error);
		return (1);
	}
	gettimeofday(&data->param.start, NULL);
	pthread_mutex_unlock(&data->lock.start);
	if (!fill_dishwasher(data->philo, free, get_sink(NULL)))
		return (1);
	usleep(10000000);
	destroy_thread(data, th, 0);
	return (0);
}

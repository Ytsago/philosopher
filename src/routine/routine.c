/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:52:32 by secros            #+#    #+#             */
/*   Updated: 2025/04/09 16:20:44 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*routine(void *args)
{
	t_philo			*philo;
	char			error;

	philo = args;
	pthread_mutex_lock(&philo->lock->start);
	pthread_mutex_unlock(&philo->lock->start);
	while (1)
	{
		if (is_a_philo_dead(philo))
			return (wait_return);
		printing(philo, THINK);
		error = try_to_eat(philo);
		if (error == 1)
			return (wait_return);
		if (error == 2)
		{
			pthread_mutex_lock(&philo->lock->is_alive);
			philo->param->dead = 1;
			pthread_mutex_unlock(&philo->lock->is_alive);
		}
		sleeping(philo);
	}
	return (NULL);
}

int	start_init(t_data *data, pthread_t **th)
{
	if (alloc_init(data))
		return (1);
	if (philo_init(data))
		return (1);
	*th = new_plate(sizeof(pthread_t) * data->param.nb_philo, get_sink(NULL));
	if (!*th)
		return (1);
	return (0);
}

void	assign_start_time(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->param.nb_philo)
	{
		data->philo[i].last_meal = data->param.start;
		i++;
	}
	return ;
}

int	start(t_data *data)
{
	pthread_t	*th;
	size_t		error;

	if (start_init(data, &th))
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
	assign_start_time(data);
	pthread_mutex_unlock(&data->lock.start);
	monitoring(data);
	if (!fill_dishwasher(data->philo, free, get_sink(NULL)))
		return (1);
	destroy_thread(data, th, 0);
	return (0);
}

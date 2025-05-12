/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:52:32 by secros            #+#    #+#             */
/*   Updated: 2025/05/12 13:38:49 by secros           ###   ########.fr       */
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
	if (philo->philo % 2 == 0)
		smart_sleep(philo, 4);
	while (!is_a_philo_dead(philo))
	{
		error = try_to_eat(philo);
		if (error == 1)
			return (NULL);
		if (error == 2)
		{
			pthread_mutex_lock(&philo->lock->is_alive);
			philo->param->dead = 1;
			pthread_mutex_unlock(&philo->lock->is_alive);
		}
		if (sleeping(philo))
			return (NULL);
		if (thinking(philo))
			return (NULL);
	}
	return (philo);
}

int	start_init(t_data *data, pthread_t **th)
{
	if (alloc_init(data))
	{
		free(data->philo);
		return (1);
	}
	if (philo_init(data))
	{
		free(data->philo);
		return (1);
	}
	if (!fill_dishwasher(data->philo, free, get_sink(NULL)))
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
	t_bool		time_error;

	if (data->param.nb_philo == 0)
		return (0);
	if (start_init(data, &th))
		return (1);
	pthread_mutex_lock(&data->lock.start);
	error = launch_thread(data, th);
	time_error = gettimeofday(&data->param.start, NULL);
	if (error != 0 || time_error)
	{
		data->param.dead = 1;
		pthread_mutex_unlock(&data->lock.start);
		destroy_thread(data, th, error);
		return (1);
	}
	assign_start_time(data);
	pthread_mutex_unlock(&data->lock.start);
	monitoring(data);
	destroy_thread(data, th, 0);
	return (0);
}
